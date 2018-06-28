#ifdef NDRTE_COMPILER_COMMON_H

#define NDRTE_CMPLXT_SPLIT_ASSIGN_1( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize
#define NDRTE_CMPLXT_SPLIT_ASSIGN_2( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_1( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_3( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_2( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_4( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_3( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_5( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_4( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_6( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_5( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_7( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_6( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_8( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_7( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_9( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_8( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_10( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_9( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_11( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_10( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_12( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_11( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_13( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_12( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_14( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_13( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_15( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_14( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_16( tvar, csize, arg, ... ) \
	arg = tvar & NDRTE_PP_CAT( NDRTE_PP_CAT( UINT, csize ), _MAX); tvar >>= csize; \
	NDRTE_CMPLXT_SPLIT_ASSIGN_15( tvar, csize, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN_( N, tvar, csize, arg, ... ) NDRTE_PP_CAT( NDRTE_CMPLXT_SPLIT_ASSIGN_, N ) ( tvar, csize, arg, __VA_ARGS__ )
#define NDRTE_CMPLXT_SPLIT_ASSIGN( tvar, csize, arg, ... ) NDRTE_CMPLXT_SPLIT_ASSIGN_( NDRTE_PP_NARG( arg, __VA_ARGS__ ), tvar, csize, arg, __VA_ARGS__ )

#define ndrte_cmplxt_split_generic( tvar, csize, ... ) \
	NDRTE_CMPLXT_SPLIT_ASSIGN( tvar, csize, __VA_ARGS__ )

#define ndrte_cmplxt_split_signed( tvar, csize, ... ) \
	{ \
		ndrte_typeof( tvar ) __tvar = tvar; \
		ndrte_cmplxt_split_generic( __tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_split_unsigned( tvar, csize, ... ) \
	{ \
		ndrte_typeof( tvar ) __tvar = tvar; \
		ndrte_cmplxt_split_generic( __tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_split_signed_safe( tvar, csize, ... ) \
	{ \
		ndrte_typeof( tvar ) __tvar = tvar; \
		NDRTE_CMPLXT_COMMON_TCHK( NDRTE_PP_CAT(NDRTE_PP_CAT( int, csize ), _t ), __VA_ARGS__ ); \
		ndrte_cmplxt_split_generic( __tvar, csize, __VA_ARGS__ ); \
	}
#define ndrte_cmplxt_split_unsigned_safe( tvar, csize, ... ) \
	{ \
		ndrte_typeof( tvar ) __tvar = tvar; \
		NDRTE_CMPLXT_COMMON_TCHK( NDRTE_PP_CAT(NDRTE_PP_CAT( uint, csize ), _t ), __VA_ARGS__ ); \
		ndrte_cmplxt_split_generic(  __tvar, csize, __VA_ARGS__ ); \
	}

#endif