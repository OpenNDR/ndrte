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
	struct packet_type *orig_handler;

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

int ngpm1_skbhook_attach( uint16_t type, int (*ptr_hook_func)( NGPM1_SKBHOOK_ARGS ) )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL, *pt_prev = NULL;

	rcu_read_lock();
	if ( !!ngpm1_shdesc_lookup( type ) )
	{
		rcu_read_unlock();
		DRV_WARN( "Requested skbhook already exist\n" );
		goto rcu_out;
	}
	spin_lock( &shdesc_list_lock );
	rcu_read_unlock();

	/* Step 1: Allocate a sh_desc */
	shdesc = kzalloc( sizeof( struct ngpm1_shdesc_struct ), GFP_ATOMIC );
	if ( !shdesc )
	{
		DRV_ERR( "Failed to allocate skbhook descriptor \n" );
		goto locked_out;
	}

	/* Step 2: Add a dummy to resolve the pt_list */
	INIT_LIST_HEAD( &(shdesc->ptlist) );
	shdesc->type = type;
	shdesc->pt.type = type;
	shdesc->pt.func = ngpm1_skbhook_dummyrcv;
	INIT_LIST_HEAD( &(shdesc->pt.list) );

	dev_add_pack( &(shdesc->pt) );

	/* Step 3: Remove and temporary backup all pt_handlers except the dummy */
	while ( !!(pt_iter = ngpm1_ptype_entry_rcu( shdesc->type, &(shdesc->pt.list) )) )
	{
		dev_remove_pack( pt_iter );
		if ( pt_prev )
		{
			list_add_rcu( &(pt_prev->list), &(shdesc->ptlist) );
		}
		pt_prev = pt_iter;
	}

	/* Step 4: Store the original protocol handler */
	shdesc->orig_handler = pt_prev;

	/* Step 5: Remove the dummy */
	dev_remove_pack( &(shdesc->pt) );

	/* Step 6: Add the skbhook handler */
	shdesc->pt.func = ptr_hook_func;
	dev_add_pack( &(shdesc->pt) );

	/* Step 7: Restore backed up pt_handlers except the original protocol handler */
	while ( !!(pt_iter = ngpm1_ptype_entry( shdesc->type, &(shdesc->ptlist) )) )
	{
		list_del_rcu( &(pt_iter->list) );
		dev_add_pack( pt_iter );
	}

	/* Step 8: Register this shdesc to the shdesc_list */
	list_add_rcu( &(shdesc->list), &shdesc_list );

locked_out:
	spin_unlock( &shdesc_list_lock );
out:
	return !shdesc;
rcu_out:
	rcu_read_unlock();
	goto out;
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
		goto rcu_out;
	}
	spin_lock( &shdesc_list_lock );
	rcu_read_unlock();

	/* Step 1: Remove and temporary backup all pt_handlers except the skbhook */
	while ( !!(pt_iter = ngpm1_ptype_entry_rcu( shdesc->type, &(shdesc->pt.list) )) )
	{
		dev_remove_pack( pt_iter );
		list_add_rcu( &(pt_iter->list), &(shdesc->ptlist) );
	}

	/* Step 2: Remove the skbhook */
	dev_remove_pack( &(shdesc->pt) );

	/* Step 3: Restore the original protocol handler */
	dev_add_pack( shdesc->orig_handler );

	/* Step 4: Restore backed up pt_handlers except the skbhook */
	while ( !!(pt_iter = ngpm1_ptype_entry( shdesc->type, &(shdesc->ptlist) )) )
	{
		list_del_rcu( &(pt_iter->list) );
		dev_add_pack( pt_iter );
	}

	/* Step 8: Unregister this shdesc from the shdesc_list */
	list_del_rcu( &(shdesc->list) );
	spin_unlock( &shdesc_list_lock );

	synchronize_rcu();
	kfree( shdesc );
out:
	return !shdesc;
rcu_out:
	rcu_read_unlock();
	goto out;
}

int ngpm1_skbhook_pktpass( NGPM1_SKBHOOK_ARGS )
{
	ngpm1_shdesc_t shdesc = NULL;
	int ret = NET_RX_SUCCESS;

	rcu_read_lock();

	if ( !pt )
	{
		goto drop;
	}

	shdesc = container_of( pt, struct ngpm1_shdesc_struct, pt );

	if ( !shdesc->orig_handler )
	{
		goto drop;
	}

	ret = shdesc->orig_handler->func( skb, dev, shdesc->orig_handler, orig_dev );

out:
	rcu_read_unlock();
	return ret;

drop:
	kfree_skb( skb );
	ret = NET_RX_DROP;
	goto out;
}