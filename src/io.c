#include "sysio.h"
#include "hstd.h"

uint8 inportb ( uint16 _port )
{
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb ( uint16 _port, uint8 _data )
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
void outportw ( uint16 _port, uint16 _data )
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int printf(char* in, ...)
{
	int i = 0;
	uint32 *argi;
	argi = ( uint32 * ) &in;
	char *ou;
	for( ; in[ i ] != 0; i++ )
	{
		if( in[i] == '%' )
		{
			i++;
			if( in[ i ] == 'i' || in[ i ] == 'd' )
			{
				argi++;
				if( *argi == 0 )
					putch( '0' );
				else{
					ou = itoa( *argi );
					puts( ou );
					free( ( uint32 ) ou );
				}
			}else if( in[ i ] == 'h' ){
				argi++;
				ou = htoa( *argi );
				puts( ou );
				free( ( uint32 ) ou );
			}else if( in[i] == 's' ){
                argi++;
                puts( ( char * ) *argi );
			}
			else
			{
				i--;
				putch( in[i] );
			}
		}
		else
		{
			putch( in[i] );
		}
	}
	return 0;
}
