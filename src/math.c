#include "math.h"
#include "hstd.h"

sint32 power( int a, int b )
{
    sint32 ans = 1;
    while ( b ){
        if ( b & 1 )
            ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

uint32 rand()
{
    int a = T.ticks;
    return a;
}


uint32 abs( int a ){
    return ( a >= 0 )? a : -a;
}
