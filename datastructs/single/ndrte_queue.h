#ifndef NDRTE_QUEUE_H
#define NDRTE_QUEUE_H

#include "ndrte_dst_common.h"

struct ndrte_queue
{
	void *dst_nametag; //Reserved area for dst_nametag

	void **data;
	uint64_t queue_sz;

	uint64_t front;
	uint64_t rear;
} NDRTE_ALIGN( NDRTE_ARCH_CACHELINE );

int ndrte_queue_init( struct ndrte_queue *queue, NDRTE_UNUSED const char *name, uint64_t queue_sz );

uint64_t ndrte_queue_free_count( struct ndrte_queue *queue );
uint64_t ndrte_queue_fill_count( struct ndrte_queue *queue );

uint64_t ndrte_queue_enq_generic( struct ndrte_queue *queue, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode );
uint64_t ndrte_queue_deq_generic( struct ndrte_queue *queue, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode );

static NDRTE_STRONG_INLINE uint64_t ndrte_queue_get_sz( struct ndrte_queue *queue )
{
	return queue->queue_sz;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_queue_enq( struct ndrte_queue *queue, void **obj_arr, uint64_t num )
{
	return ndrte_queue_enq_generic( queue, obj_arr, num, NDRTE_DST_AVAIL );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_queue_enq_bulk( struct ndrte_queue *queue, void **obj_arr, uint64_t num )
{
	return ndrte_queue_enq_generic( queue, obj_arr, num, NDRTE_DST_BULK );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_queue_deq( struct ndrte_queue *queue, void **obj_arr, uint64_t num )
{
	return ndrte_queue_deq_generic( queue, obj_arr, num, NDRTE_DST_AVAIL );
}
static NDRTE_STRONG_INLINE uint64_t ndrte_queue_deq_bulk( struct ndrte_queue *queue, void **obj_arr, uint64_t num )
{
	return ndrte_queue_deq_generic( queue, obj_arr, num, NDRTE_DST_BULK );
}

#endif