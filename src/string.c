#include "hstd.h"
#include "string.h"

uint8* memcpy ( uint8* dest, const uint8* src, size_t count )
{
    const sint8* sp = ( const sint8* ) src;
    sint8* dp = ( sint8* ) dest;
    for ( ; count != 0; count-- )
    {
        *dp++ = *sp++;
    }
    return dest;
}
uint16* memcpyw ( uint16* dest, const uint16* src, size_t count )
{
    const sint16* sp = ( const sint16* ) src;
    sint16* dp = ( sint16* ) dest;
    for ( ; count != 0; count-- )
    {
        *dp++ = *sp++;
    }
    return dest;
}

uint8* memset ( uint8* dest, uint8 val, size_t count )
{
    uint8* temp = ( uint8* ) dest;
    for ( ; count != 0; count-- )
    {
        *temp++ = val;
    }
    return dest;
}

uint16* memsetw ( uint16* dest, uint16 val, size_t count )
{
    uint16* temp = ( uint16* ) dest;
    for ( ; count != 0; count-- )
    {
        *temp++ = val;
    }
    return dest;
}

size_t strlen ( const char* str )
{
    int retval;
    for ( retval = 0; *str != '\0'; str++ )
    {
        retval++;
    }
    return retval;
}
char *itoa ( int in )
{
    int negative = 0;
    int digits = 0;
    uint32 i = 1;
    if ( in < 0 )
    {
        in = in * -1;
        negative = 1;
    }
    while ( i <= in )
    {
        i *= 10;
        digits++;
    }
    int j;
    if ( negative )
	digits++;
    char *out = ( char * ) malloc ( digits + 1 );
    out[ digits ] = 0;
    for ( j = digits - 1; j >= 0; j-- )
    {
        out[ j ] = ( char ) ( in % 10 ) + 48;
        in /= 10;
    }
    if ( negative )
        out[ 0 ] = '-';
    return out;
}

char* htoa ( uint32 in )
{
    char* out = ( char* ) malloc ( 10 + 1 );
    out[ 0 ] = '0';
    out[ 1 ] = 'x';
    out[ 10 ] = '\0';
    int k = 9;
    while ( in > 0 )
    {
        if ( in % 16 < 10 )
        {
            out[ k ] = ( char ) ( in % 16 ) + 48;
        }
        else switch ( in % 16 )
            {
                case 10:
                    out[ k ] = 'A';
                    break;
                case 11:
                    out[ k ] = 'B';
                    break;
                case 12:
                    out[ k ] = 'C';
                    break;
                case 13:
                    out[ k ] = 'D';
                    break;
                case 14:
                    out[ k ] = 'E';
                    break;
                case 15:
                    out[ k ] = 'F';
                    break;
            }
        k--;
        in = in >> 4;
    }
    size_t i = 2;
    for ( ; i <= k; i++ )
    {
        out[ i ] = '0';
    }
    return out;
}

sint32 strcmp ( const char *a, const char *b )
{
	size_t alen = strlen( a );
	size_t blen = strlen( b );
	if ( alen != blen )
		return 0;
	size_t i = 0;
	for ( ; i < alen; i++ )
		if ( a[ i ] != b[ i ] )
			return 0;
	return 1;
}

sint32 atoi ( char *a )
{
	size_t i = 0;
	uint32 res = 0;
	for ( ; a[ i ] >= '0' && a[ i ] <= '9'; i++ )
	{
		res = res * 10 + a[ i ] - 48;
	}
	return res;
}

sint32 atoi_o ( char *a, size_t offset )
{
	size_t i = offset;
	uint32 res = 0;
	for ( ; a[ i ] >= '0' && a[ i ] <= '9'; i++ )
	{
		res = res * 10;
		res = res + a[ i ] - '0';
	}
	return res;
}

char *all_to_lower( const char *a )
{
    size_t len = strlen( a ), i = 0;
    char *b = ( char * ) malloc( len );
    memcpy( ( uint8 * ) b, ( uint8 * ) a, len);
    for( ; i < len; i++ )
        if( b[ i ] >= 'A' && b[ i ] <= 'Z')
            b[ i ] += ( 'a' - 'A' );
    return b;
}

char *all_to_upper( const char *a )
{
    size_t len = strlen( a ), i = 0;
    char *b = ( char * ) malloc( len );
    memcpy( ( uint8 * ) b, ( uint8 * ) a, len);
    for( ; i < len; i++ )
        if(b[ i ] >= 'a' && b[ i ] <= 'z')
            b[ i ] -= ( 'a' - 'A' );
    return b;
}

void *all_to_upperc( char *a )
{
    size_t len = strlen( a ), i = 0;
    for( ; i < len; i++ )
        if(a[ i ] >= 'a' && a[ i ] <= 'z')
            a[ i ] -= ( 'a' - 'A' );
}
