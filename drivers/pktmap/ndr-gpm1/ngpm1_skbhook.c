#include <net/ip.h>

#include <linux/list.h>
#include <linux/rculist.h>
#include <linux/spinlock.h>
#include <linux/skbuff.h>
#include <linux/version.h>

#include "drv_common.h"
#include "ngpm1_skbhook.h"

struct ngpm1_shdesc_struct
{
	uint16_t type;

	struct packet_type pt;
	struct list_head ptlist;

	struct list_head list;
};

typedef struct ngpm1_shdesc_struct * ngpm1_shdesc_t;

static LIST_HEAD( shdesc_list );
static DEFINE_SPINLOCK( shdesc_list_lock );

static int ngpm1_skbhook_dummyrcv( NGPM1_SKBHOOK_ARGS )
{
	return NET_RX_DROP;
}

static inline ngpm1_shdesc_t ngpm1_shdesc_lookup( uint16_t type )
{
	ngpm1_shdesc_t shdesc = NULL;

	list_for_each_entry_rcu( shdesc, &shdesc_list, list )
	{
		if ( shdesc->type == type )
		{
			return shdesc;
		}
	}
	return NULL;
}

static inline struct packet_type * ngpm1_ptype_entry_rcu( uint16_t type, struct list_head *head )
{
	struct packet_type *ptype_entry = NULL;

	rcu_read_lock();
	list_for_each_entry_rcu( ptype_entry, head, list )
	{
		if ( ptype_entry->type != type )
		{
			continue;
		}
		rcu_read_unlock();
		return ptype_entry;
	}
	rcu_read_unlock();
	return NULL;
}

static inline struct packet_type * ngpm1_ptype_entry( uint16_t type, struct list_head *head )
{
	struct packet_type *ptype_entry = NULL;

	list_for_each_entry( ptype_entry, head, list )
	{
		if ( ptype_entry->type != type )
		{
			continue;
		}
		return ptype_entry;
	}
	return NULL;
}

static inline int ngpm1_skbhook_deliver_skb( struct sk_buff *skb, struct packet_type *pt, struct net_device *orig_dev )
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,14,0)
	refcount_dec( &(skb->users) );

	if ( unlikely(skb_orphan_frags_rx( skb, GFP_ATOMIC )) )
	{
		return -ENOMEM;
	}

	refcount_inc( &(skb->users) );
	return pt->func( skb, skb->dev, pt, orig_dev );

#elif LINUX_VERSION_CODE >= KERNEL_VERSION(4,13,0)
	refcount_dec( &(skb->users) );

	if ( unlikely(skb_orphan_frags( skb, GFP_ATOMIC )) )
	{
		return -ENOMEM;
	}

	refcount_inc( &(skb->users) );
	return pt->func( skb, skb->dev, pt, orig_dev );

#elif LINUX_VERSION_CODE >= KERNEL_VERSION( 3,6,0 )
	atomic_dec( &(skb->users) );

	if ( unlikely(skb_orphan_frags( skb, GFP_ATOMIC )) )
	{
		return -ENOMEM;
	}
	atomic_inc( &(skb->users) );
	return pt->func( skb, skb->dev, pt, orig_dev );

#else
	atomic_dec( &(skb->users) );

	atomic_inc( &(skb->users) );
	return pt->func( skb, skb->dev, pt, orig_dev );

#endif
}


int ngpm1_skbhook_attach( uint16_t type, int (*ptr_hook_func)( NGPM1_SKBHOOK_ARGS ) )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL;

	rcu_read_lock();
	if ( !!ngpm1_shdesc_lookup( type ) )
	{
		rcu_read_unlock();
		DRV_WARN( "Requested skbhook already exist\n" );
		goto out;
	}
	spin_lock( &shdesc_list_lock );
	rcu_read_unlock();

	shdesc = kzalloc( sizeof( struct ngpm1_shdesc_struct ), GFP_ATOMIC );
	if ( !shdesc )
	{
		DRV_ERR( "Failed to allocate skbhook descriptor \n" );
		goto locked_out;
	}

	INIT_LIST_HEAD( &(shdesc->ptlist) );
	shdesc->type = type;
	shdesc->pt.type = type;
	shdesc->pt.func = ngpm1_skbhook_dummyrcv;
	INIT_LIST_HEAD( &(shdesc->pt.list) );

	dev_add_pack( &(shdesc->pt) );

	while ( !!(pt_iter = ngpm1_ptype_entry_rcu( shdesc->type, &(shdesc->pt.list) )) )
	{
		dev_remove_pack( pt_iter );
		list_add_rcu( &(pt_iter->list), &(shdesc->ptlist) );
	}

	dev_remove_pack( &(shdesc->pt) );
	shdesc->pt.func = ptr_hook_func;

	list_add_rcu( &(shdesc->list), &shdesc_list );
	dev_add_pack( &(shdesc->pt) );
locked_out:
	spin_unlock( &shdesc_list_lock );
out:
	return !shdesc;
}

int ngpm1_skbhook_detach( uint16_t type )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL;

	rcu_read_lock();
	shdesc = ngpm1_shdesc_lookup( type );
	if ( !shdesc )
	{
		rcu_read_unlock();
		DRV_WARN( "Requested skbhook not exist\n" );
		goto out;
	}
	spin_lock( &shdesc_list_lock );
	rcu_read_unlock();

	while ( !!(pt_iter = ngpm1_ptype_entry( shdesc->type, &(shdesc->ptlist) )) )
	{
		list_del_rcu( &(pt_iter->list) );
		dev_add_pack( pt_iter );
	}

	dev_remove_pack( &(shdesc->pt) );
	list_del_rcu( &(shdesc->list) );
	spin_unlock( &shdesc_list_lock );

	synchronize_rcu();
	kfree( shdesc );
out:
	return !shdesc;
}

int ngpm1_skbhook_pktpass( uint16_t type, struct sk_buff *skb, struct net_device *orig_dev )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL;
	int ret = NET_RX_SUCCESS;

	rcu_read_lock_bh();
	shdesc = ngpm1_shdesc_lookup( type );
	if ( !shdesc )
	{
		goto drop;
	}

	list_for_each_entry_rcu( pt_iter, &(shdesc->ptlist), list )
	{
		if ( pt_iter->type == shdesc->type )
		{
			if ( !!ngpm1_skbhook_deliver_skb( skb, pt_iter, orig_dev ) )
			{
				goto drop;
			}
		}
	}

out:
	rcu_read_unlock_bh();
	return ret;

drop:
	kfree_skb( skb );
	ret = NET_RX_DROP;
	goto out;
}