#ifndef NDRTE_ARCH_ENDIAN_H
#define NDRTE_ARCH_ENDIAN_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"

static NDRTE_STRONG_INLINE uint16_t ndrte_endian_const_conv16( uint64_t u16 )
{
	return (uint16_t)(
		((u16 & 0x00ffU) << 8) |
		((u16 & 0xff00U) >> 8)
	);
}

static NDRTE_STRONG_INLINE uint32_t ndrte_endian_const_conv32( uint64_t u32 )
{
	return (uint32_t)(
		((u32 & 0x000000ffUL) << 24) |
		((u32 & 0x0000ff00UL) << 8) |
		((u32 & 0x00ff0000UL) >> 8) |
		((u32 & 0xff000000UL) >> 24)
	);
}

static NDRTE_STRONG_INLINE uint64_t ndrte_endian_const_conv64( uint64_t u64 )
{
	return (uint64_t)( ((u64 & 0x00000000000000ffULL) << 56) |
		((u64 & 0x000000000000ff00ULL) << 40) |
		((u64 & 0x0000000000ff0000ULL) << 24) |
		((u64 & 0x00000000ff000000ULL) <<  8) |
		((u64 & 0x000000ff00000000ULL) >>  8) |
		((u64 & 0x0000ff0000000000ULL) >> 24) |
		((u64 & 0x00ff000000000000ULL) >> 40) |
		((u64 & 0xff00000000000000ULL) >> 56)
	);
}

static NDRTE_STRONG_INLINE uint16_t ndrte_endian_conv16( uint16_t u16 )
{
	register uint16_t ret = u16;
	__asm__ __volatile__ ( "xchgb %b0, %h1"
							: "=Q" (ret)
							: "0" (ret) );
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_endian_conv32( uint32_t u32 )
{
	register uint32_t ret = u32;
	__asm__ __volatile__ ( "bswap %0"
							: "+r" (ret) );
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_endian_conv64( uint64_t u64 )
{
	register uint64_t ret = u64;
	__asm__ __volatile__ ( "bswap %0"
							: "+r" (ret) );
	return ret;
}

#define NDRTE_ENDIAN_INTERNAL_LE 0
#define NDRTE_ENDIAN_INTERNAL_BE 1
#define NDRTE_ENDIAN_INTERNAL_le NDRTE_ENDIAN_INTERNAL_LE
#define NDRTE_ENDIAN_INTERNAL_be NDRTE_ENDIAN_INTERNAL_BE

#define NDRTE_ENDIAN_INTERNAL_IFCONST_0( x, size ) ( x )
#define NDRTE_ENDIAN_INTERNAL_IFCONST_1( x, size ) ( ndrte_endian_const_conv ## size ( x ) )
#define NDRTE_ENDIAN_INTERNAL_IFCONST( x, size, endian ) NDRTE_ENDIAN_INTERNAL_IFCONST_ ## endian ( x, size )
#define NDRTE_ENDIAN_INTERNAL_IF_0( x, size ) ( x )
#define NDRTE_ENDIAN_INTERNAL_IF_1( x, size ) ( ndrte_endian_conv ## size ( x ) )
#define NDRTE_ENDIAN_INTERNAL_IF( x, size, endian ) NDRTE_ENDIAN_INTERNAL_IF_ ## endian ( x, size )

#define ndrte_endian_conv_generic( x, size, endian ) \
	ndrte_builtin_const( x ) ? NDRTE_ENDIAN_INTERNAL_IFCONST( x, size, endian ) : NDRTE_ENDIAN_INTERNAL_IF( x, size, endian )

#define ndrte_endian_conv( x, size, endian ) \
	ndrte_endian_conv_generic( x, size, NDRTE_ENDIAN_INTERNAL_ ## endian )

#endif