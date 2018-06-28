#ifndef NDRTE_COMPILER_COMMON_H
#define NDRTE_COMPILER_COMMON_H

#ifndef __KERNEL__
#include <stdint.h>
#else
#include <linux/types.h>
#endif

#define NDRTE_UNUSED __attribute__((unused))
#define NDRTE_STRONG_INLINE inline __attribute__((always_inline))
#define NDRTE_ALIGN( value ) __attribute__((aligned(value)))
#define NDRTE_PACKED() __atrribute__((packed))

#define ndrte_builtin_const( x ) __builtin_constant_p( x )
#define ndrte_likely( x ) __builtin_expect( (x), 1 )
#define ndrte_unlikely( x ) __builtin_expect( (x), 0 )
#define ndrte_typeof( x ) __typeof__( x )

#define NDRTE_UOPTR( type ) \
	__volatile__ type *

#define ndrte_uoptr_set( var ) \
	((NDRTE_UOPTR( ndrte_typeof(var) ))&(var))

#define NDRTE_ACCESS_ONCE( var ) \
	(*ndrte_uoptr_set( var ))

#define ndrte_base_of( struct_ptr, member_ptr, member ) \
	({struct_ptr = (ndrte_typeof( struct_ptr ))((void *)member_ptr) - (void *)&(((ndrte_typeof( struct_ptr ))0)->member); struct_ptr;})

#define ndrte_container_of( obj_ptr, struct_type, member ) \
	({struct_type *__ret_ptr; ndrte_base_of( __ret_ptr, obj_ptr, member ); __ret_ptr})

#define ndrte_typechk( type, x ) \
	{ ndrte_typeof( x ) *__checker_0 = (type *)0; }

#define NDRTE_PP_RSEQ_N() \
	16, 15, 14, 13, \
	12, 11, 10, 9, \
	8, 7, 6, 5, \
	4, 3, 2, 1, 0
#define NDRTE_PP_ARG_N( \
	_1, _2, _3, _4, \
	_5, _6, _7, _8, \
	_9, _10, _11, _12, \
	_13, _14, _15, _16, N, ... \
) N
#define NDRTE_PP_NARG_( ... ) \
	NDRTE_PP_ARG_N( __VA_ARGS__ )
#define NDRTE_PP_NARG( ... ) \
	NDRTE_PP_NARG_( __VA_ARGS__, NDRTE_PP_RSEQ_N() )

#define NDRTE_PP_CAT( x, y ) \
	NDRTE_PP_CAT_DEPTH1( x, y )
#define NDRTE_PP_CAT_DEPTH1( x, y ) \
	NDRTE_PP_CAT_DEPTH2( x, y )
#define NDRTE_PP_CAT_DEPTH2( x, y ) x ## y

#include "ndrte_compiler_cmplxt_define.h"
#include "ndrte_compiler_cmplxt_pack.h"
#include "ndrte_compiler_cmplxt_split.h"

#endif