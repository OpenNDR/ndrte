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
#define ndrte_typeof( x ) __typeof__(x)

#define NDRTE_UOPTR( type ) \
	__volatile__ type *

#define ndrte_uoptr_set( var ) \
	((NDRTE_UOPTR( ndrte_typeof(var) ))&(var))

#define NDRTE_ACCESS_ONCE( var ) \
	(*ndrte_uoptr_set( var ))

#endif