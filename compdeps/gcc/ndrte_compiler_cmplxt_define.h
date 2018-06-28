#ifdef NDRTE_COMPILER_COMMON_H

#define NDRTE_CMPLXT_COMMON_TCHK_1( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg )
#define NDRTE_CMPLXT_COMMON_TCHK_2( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_1( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_3( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_2( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_4( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_3( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_5( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_4( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_6( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_5( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_7( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_6( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_8( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_7( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_9( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_8( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_10( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_9( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_11( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_10( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_12( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_11( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_13( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_12( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_14( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_13( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_15( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_14( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_16( ctype, arg, ... ) \
	ndrte_typechk( ctype, arg ); \
	NDRTE_CMPLXT_COMMON_TCHK_15( ctype, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK_( N, ctype, arg, ... ) NDRTE_PP_CAT( NDRTE_CMPLXT_COMMON_TCHK_, N ) ( ctype, arg, __VA_ARGS__ )
#define NDRTE_CMPLXT_COMMON_TCHK( ctype, arg, ... ) NDRTE_CMPLXT_COMMON_TCHK_( NDRTE_PP_NARG( arg, __VA_ARGS__), ctype, arg, __VA_ARGS__ )

typedef int ndrte_int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int ndrte_uint64_t __attribute__((__mode__(__DI__))) ;

typedef int ndrte_int128_t __attribute__((__mode__(__TI__))) ;
typedef unsigned int ndrte_uint128_t __attribute__((__mode__(__TI__))) ;

#endif