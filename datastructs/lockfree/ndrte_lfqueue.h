#ifndef NDRTE_LFQUEUE_H
#define NDRTE_LFQUEUE_H

#include "ndrte_arch_atomic.h"
#include "ndrte_dst_common.h"

struct ndrte_lfq
{
	void *dst_nametag; //Reserved area for dst_nametag

	void **data;
	uint64_t lfq_sz;

	ndrte_atomic64_t lfq_enq_head;
	ndrte_atomic64_t lfq_enq_tail;
	ndrte_atomic64_t lfq_deq_head;
	ndrte_atomic64_t lfq_deq_tail;
} NDRTE_ALIGN( NDRTE_ARCH_CACHELINE );

int ndrte_lfq_init( struct ndrte_lfq *lfq, NDRTE_UNUSED const char *name, uint64_t lfq_sz );

uint64_t ndrte_lfq_free_count( struct ndrte_lfq *lfq );
uint64_t ndrte_lfq_fill_count( struct ndrte_lfq *lfq );

uint64_t ndrte_lfq_enq_generic( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode );
uint64_t ndrte_lfq_deq_generic( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode );

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_get_sz( struct ndrte_lfq *lfq )
{
	return lfq->lfq_sz;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_enq( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num )
{
	return ndrte_lfq_enq_generic( lfq, obj_arr, num, NDRTE_DST_AVAIL );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_enq_bulk( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num )
{
	return ndrte_lfq_enq_generic( lfq, obj_arr, num, NDRTE_DST_BULK );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_deq( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num )
{
	return ndrte_lfq_deq_generic( lfq, obj_arr, num, NDRTE_DST_AVAIL );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_lfq_deq_bulk( struct ndrte_lfq *lfq, void **obj_arr, uint64_t num )
{
	return ndrte_lfq_deq_generic( lfq, obj_arr, num, NDRTE_DST_BULK );
}

#endif