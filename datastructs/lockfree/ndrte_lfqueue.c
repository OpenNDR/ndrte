#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ndrte_lfqueue.h"

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_get_enq_head( struct ndrte_lfq *lfq )
{
	return ndrte_atomic64_get( &(lfq->lfq_enq_head) );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_get_enq_tail( struct ndrte_lfq *lfq )
{
	return ndrte_atomic64_get( &(lfq->lfq_enq_tail) );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_get_deq_head( struct ndrte_lfq *lfq )
{
	return ndrte_atomic64_get( &(lfq->lfq_deq_head) );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_get_deq_tail( struct ndrte_lfq *lfq )
{
	return ndrte_atomic64_get( &(lfq->lfq_deq_tail) );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_calc_free( struct ndrte_lfq *lfq, uint64_t enq_tail, uint64_t deq_head )
{
	return ndrte_lfq_get_sz( lfq ) + deq_head - enq_tail - 1;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_calc_fill( struct ndrte_lfq *lfq, uint64_t deq_tail, uint64_t enq_head )
{
	return enq_head - deq_tail;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_calc_safe( struct ndrte_lfq *lfq, uint64_t sum_value )
{
	return sum_value % ndrte_lfq_get_sz( lfq );
}

uint64_t ndrte_lfq_free_count( struct ndrte_lfq *lfq )
{
	return ndrte_lfq_calc_free( lfq, ndrte_lfq_get_enq_tail( lfq ), ndrte_lfq_get_deq_head( lfq ) );
}

uint64_t ndrte_lfq_fill_count( struct ndrte_lfq *lfq )
{
	return ndrte_lfq_calc_fill( lfq, ndrte_lfq_get_deq_tail( lfq ), ndrte_lfq_get_enq_head( lfq ) );
}

int ndrte_lfq_init( struct ndrte_lfq *lfq, NDRTE_UNUSED const char *name, uint64_t lfq_sz )
{
	if ( !lfq )
	{
		return -EINVAL;
	}

	memset( lfq, 0, sizeof(*lfq) );

	lfq->data = malloc( lfq_sz * sizeof(void *) );
	if ( !lfq->data )
	{
		return -ENOMEM;
	}

	lfq->dst_nametag = NULL;
	lfq->lfq_sz = lfq_sz;

	return 0;
}

uint64_t ndrte_lfq_enq_generic( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode )
{
	uint64_t enq_tail, deq_head, local_enq_tail, enq_num, i;

	if ( obj_arr == NULL || num == 0 )
	{
		return 0;
	}

	while ( 1 )
	{
		enq_tail = ndrte_lfq_get_enq_tail( lfq );
		deq_head = ndrte_lfq_get_deq_head( lfq );
		enq_num = ndrte_lfq_calc_free( lfq, enq_tail, deq_head );

		if ( enq_num < num )
		{
			if ( enq_num == 0 || mode != NDRTE_DST_AVAIL )
			{
				return 0;
			}
		}
		else
		{
			enq_num = num;
		}

		local_enq_tail = ndrte_lfq_calc_safe( lfq, enq_tail + enq_num );

		if ( ndrte_atomic64_cmpxchg( &(lfq->lfq_enq_tail), enq_tail, local_enq_tail ) == enq_tail )
		{
			break;
		}
	}

	for ( i = 0; i < enq_num; i++ )
	{
		lfq->data[ndrte_lfq_calc_safe( lfq, enq_tail + i )] = obj_arr[i];
	}

	ndrte_wmb();

	while ( ndrte_atomic64_cmpxchg( &(lfq->lfq_enq_head), enq_tail, local_enq_tail ) != enq_tail )
	{
		ndrte_pause();
	}

	return enq_num;
}

uint64_t ndrte_lfq_deq_generic( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode )
{
	uint64_t deq_tail, enq_head, local_deq_tail, deq_num, i;

	if ( obj_arr == NULL || num == 0 )
	{
		return 0;
	}

	while ( 1 )
	{
		deq_tail = ndrte_lfq_get_deq_tail( lfq );
		enq_head = ndrte_lfq_get_enq_head( lfq );
		deq_num = ndrte_lfq_calc_fill( lfq, deq_tail, enq_head );

		if ( deq_num < num )
		{
			if ( deq_num == 0 || mode != NDRTE_DST_AVAIL )
			{
				return 0;
			}
		}
		else
		{
			deq_num = num;
		}

		local_deq_tail = ndrte_lfq_calc_safe( lfq, deq_tail + deq_num );

		if ( ndrte_atomic64_cmpxchg( &(lfq->lfq_deq_tail), deq_tail, local_deq_tail ) == deq_tail )
		{
			break;
		}
	}

	for ( i = 0; i < deq_num; i++ )
	{
		obj_arr[i] = lfq->data[ndrte_lfq_calc_safe( lfq, deq_tail + i )];
	}

	ndrte_wmb();

	while ( ndrte_atomic64_cmpxchg( &(lfq->lfq_deq_head), deq_tail, local_deq_tail ) != deq_tail )
	{
		ndrte_pause();
	}

	return deq_num;
}