#include "selftest.h"

int main( int argc, char **argv )
{
	NTS_CALL_TC( compdeps_cmplxt_i32 );
	NTS_REPORT( compdeps_cmplxt_i32 );

	NTS_CALL_TC( compdeps_cmplxt_u32 );
	NTS_REPORT( compdeps_cmplxt_u32 );

	NTS_CALL_TC( queue_single );
	NTS_REPORT( queue_single );

	NTS_CALL_TC( lfqueue_single );
	NTS_REPORT( lfqueue_single );

	NTS_CALL_TC( lfqueue_sp_sc );
	NTS_REPORT( lfqueue_sp_sc );

	return 0;
}