#ifndef NDRTE_DST_COMMON_H
#define NDRTE_DST_COMMON_H

#include <stdint.h>

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_barrier.h"

enum ndrte_dst_mode_enum
{
	NDRTE_DST_BULK,
	NDRTE_DST_AVAIL,
};
typedef enum ndrte_dst_mode_enum ndrte_dst_mode_t;

#endif