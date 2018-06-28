#ifdef NDRTE_COMPILER_COMMON_H

#define NDRTE_CMPLXT_PACK_ASSIGN_1( tvar, csize, arg, ... ) \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_2( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_1( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_3( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_2( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_4( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_3( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_5( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_4( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_6( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_5( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_7( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_6( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_8( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_7( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_9( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_8( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_10( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_9( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_11( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_10( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_12( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_11( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_13( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_12( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_14( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_13( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_15( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_14( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)
#define NDRTE_CMPLXT_PACK_ASSIGN_16( tvar, csize, arg, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN_15( tvar, csize, __VA_ARGS__ ); \
	tvar <<= csize; \
	tvar |= arg & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX)

#define NDRTE_CMPLXT_PACK_ASSIGN_( N, tvar, csize, arg, ... ) NDRTE_PP_CAT( NDRTE_CMPLXT_PACK_ASSIGN_, N ) ( tvar, csize, arg, __VA_ARGS__ )
#define NDRTE_CMPLXT_PACK_ASSIGN( tvar, csize, arg, ... ) NDRTE_CMPLXT_PACK_ASSIGN_( NDRTE_PP_NARG( arg, __VA_ARGS__ ), tvar, csize, arg, __VA_ARGS__ )

#define ndrte_cmplxt_pack_generic( tvar, csize, ... ) \
	NDRTE_CMPLXT_PACK_ASSIGN( tvar, csize, __VA_ARGS__ )

#define ndrte_cmplxt_pack_signed( tvar, csize, ... ) \
	{ \
		tvar = 0; \
		ndrte_cmplxt_pack_generic( tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_pack_unsigned( tvar, csize, ... ) \
	{ \
		tvar = 0; \
		ndrte_cmplxt_pack_generic( tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_pack_signed_safe( tvar, csize, ... ) \
	{ \
		tvar = 0; \
		NDRTE_CMPLXT_COMMON_TCHK( NDRTE_PP_CAT(NDRTE_PP_CAT( int, csize ), _t ), __VA_ARGS__ ); \
		ndrte_cmplxt_pack_generic( tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_pack_unsigned_safe( tvar, csize, ... ) \
	{ \
		tvar = 0; \
		NDRTE_CMPLXT_COMMON_TCHK( NDRTE_PP_CAT(NDRTE_PP_CAT( uint, csize ), _t ), __VA_ARGS__ ); \
		ndrte_cmplxt_pack_generic( tvar, csize, __VA_ARGS__ ); \
	}

#endif