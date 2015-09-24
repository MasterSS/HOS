#include "algorithm.h"
#include "hstd.h"

void sh_left ( uint32 *ptr, uint32 len )
{
	int i = 0;
	for ( ; i < len - 1; i++ )
		ptr[ i ] = ptr[ i + 1 ];
	ptr[ len - 1 ] = 0;
}

void sh_right ( uint32 *ptr, uint32 len )
{
	int i = len;
	for ( ; i > 0; i-- )
		ptr[ i ] = ptr[ i - 1 ];
	ptr[ 0 ] = 0;
}
