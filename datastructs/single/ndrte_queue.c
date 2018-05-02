#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ndrte_queue.h"

static NDRTE_STRONG_INLINE uint64_t ndrte_queue_calc_safe( struct ndrte_queue *queue, uint64_t sum_value )
{
	return sum_value % ndrte_queue_get_sz( queue );
}

uint64_t ndrte_queue_free_count( struct ndrte_queue *queue )
{
	return ndrte_queue_get_sz( queue ) + queue->front - queue->rear - 1;
}

uint64_t ndrte_queue_fill_count( struct ndrte_queue *queue )
{
	return queue->rear - queue->front;
}

int ndrte_queue_init( struct ndrte_queue *queue, NDRTE_UNUSED const char *name, uint64_t queue_sz )
{
	if ( !queue )
	{
		return -EINVAL;
	}

	memset( queue, 0, sizeof(*queue) );

	queue->data = malloc( queue_sz * sizeof(void *) );
	if ( !queue->data )
	{
		return -ENOMEM;
	}

	queue->dst_nametag = NULL;
	queue->queue_sz = queue_sz;

	return 0;
}

uint64_t ndrte_queue_enq_generic( struct ndrte_queue *queue, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode )
{
	uint64_t rear_curr, rear_next, enq_num, i;

	if ( obj_arr == NULL || num == 0 )
	{
		return 0;
	}

	rear_curr = queue->rear;
	enq_num = ndrte_queue_free_count( queue );

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

	rear_next = ndrte_queue_calc_safe( queue, rear_curr + enq_num );

	for ( i = 0; i < enq_num; i++ )
	{
		queue->data[ndrte_queue_calc_safe( queue, rear_curr + i )] = obj_arr[i];
	}

	ndrte_wmb();

	queue->rear = rear_next;
	return enq_num;
}

uint64_t ndrte_queue_deq_generic( struct ndrte_queue *queue, void **obj_arr, uint64_t num, ndrte_dst_mode_t mode )
{
	uint64_t front_curr, front_next, deq_num, i;

	if ( obj_arr == NULL || num == 0 )
	{
		return 0;
	}

	front_curr = queue->front;
	deq_num = ndrte_queue_fill_count( queue );

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

	front_next = ndrte_queue_calc_safe( queue, front_curr + deq_num );

	for ( i = 0; i < deq_num; i++ )
	{
		obj_arr[i] = queue->data[ndrte_queue_calc_safe( queue, front_curr + i )];
	}

	ndrte_wmb();

	queue->front = front_next;
	return deq_num;
}