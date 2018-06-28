#include "ndrte_compiler_common.h"

#include "selftest_compdeps_cmplxt.h"

NTS_DEFINE_TC( compdeps_cmplxt_i32 )
{
	union
	{
		uint32_t var;
		struct
		{
			int16_t v16_0, v16_1;
		};
		struct
		{
			int8_t v8_0, v8_1, v8_2, v8_3;
		};
	} test;

	int16_t t16_0, t16_1;
	int8_t t8_0, t8_1, t8_2, t8_3;

	ndrte_cmplxt_pack_signed( test.var, 8, -1, -2, -3, -4 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_3 == -4, NTS_LVLSILENT );

	ndrte_cmplxt_split_signed( test.var, 8, t8_0, t8_1, t8_2, t8_3 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_3 == -4, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_3 == -4, NTS_LVLSILENT );

	ndrte_cmplxt_pack_signed( test.var, 16, -10, -20 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_1 == -20, NTS_LVLSILENT );

	ndrte_cmplxt_split_signed( test.var, 16, t16_0, t16_1 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_1 == -20, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t16_1 == -20, NTS_LVLSILENT );

	ndrte_cmplxt_pack_signed_safe( test.var, 8, (int8_t)-1, (int8_t)-2, (int8_t)-3, (int8_t)-4 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_3 == -4, NTS_LVLSILENT );

	ndrte_cmplxt_split_signed_safe( test.var, 8, t8_0, t8_1, t8_2, t8_3 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v8_3 == -4, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_0 == -1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_1 == -2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_2 == -3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t8_3 == -4, NTS_LVLSILENT );

	ndrte_cmplxt_pack_signed_safe( test.var, 16, (int16_t)-10, (int16_t)-20 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_1 == -20, NTS_LVLSILENT );

	ndrte_cmplxt_split_signed_safe( test.var, 16, t16_0, t16_1 );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, test.v16_1 == -20, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t16_0 == -10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_i32, t16_1 == -20, NTS_LVLSILENT );
}

NTS_DEFINE_TC( compdeps_cmplxt_u32 )
{
	union
	{
		uint32_t var;
		struct
		{
			uint16_t v16_0, v16_1;
		};
		struct
		{
			uint8_t v8_0, v8_1, v8_2, v8_3;
		};
	} test;

	uint16_t t16_0, t16_1;
	uint8_t t8_0, t8_1, t8_2, t8_3;

	ndrte_cmplxt_pack_unsigned( test.var, 8, 1, 2, 3, 4 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_3 == 4, NTS_LVLSILENT );

	ndrte_cmplxt_split_unsigned( test.var, 8, t8_0, t8_1, t8_2, t8_3 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_3 == 4, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_3 == 4, NTS_LVLSILENT );

	ndrte_cmplxt_pack_unsigned( test.var, 16, 10, 20 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_1 == 20, NTS_LVLSILENT );

	ndrte_cmplxt_split_unsigned( test.var, 16, t16_0, t16_1 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_1 == 20, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t16_1 == 20, NTS_LVLSILENT );

	ndrte_cmplxt_pack_unsigned_safe( test.var, 8, (uint8_t)1, (uint8_t)2, (uint8_t)3, (uint8_t)4 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_3 == 4, NTS_LVLSILENT );

	ndrte_cmplxt_split_unsigned_safe( test.var, 8, t8_0, t8_1, t8_2, t8_3 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v8_3 == 4, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_0 == 1, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_1 == 2, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_2 == 3, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t8_3 == 4, NTS_LVLSILENT );

	ndrte_cmplxt_pack_unsigned_safe( test.var, 16, (uint16_t)10, (uint16_t)20 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_1 == 20, NTS_LVLSILENT );

	ndrte_cmplxt_split_unsigned_safe( test.var, 16, t16_0, t16_1 );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, test.v16_1 == 20, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t16_0 == 10, NTS_LVLSILENT );
	NTS_CHECK_LVL( compdeps_cmplxt_u32, t16_1 == 20, NTS_LVLSILENT );
}