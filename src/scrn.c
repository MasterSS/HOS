#include "HOS.h"
int fcls;

void scroll()
{
    uint16 blank, temp;

    blank = 0x20 | ( VGA.attrib << 8 );

    if(VGA.csr_y >= 25)
    {
        memcpy ( VGA.textmemptr + 6 * 80, VGA.textmemptr + 7 * 80, (25-7) * 80 * 2 );
        memsetw ( VGA.textmemptr + 24 * 80, blank, 80 );
        VGA.csr_y = 25 - 1;
    }
}


void cls()
{
    uint16 blank;
    int i;

    blank = ' ' | ( VGA.attrib << 8 );
	if( fcls )
	{
    	for( i = 0; i < 25; i++ )
        	memsetw ( VGA.textmemptr + i * 80, blank, 80 );
		VGA.csr_x = 0;
    	VGA.csr_y = 0;
		fcls = 0;
	}
	else
	{
		for( i = 5; i < 25; i++ )
        	memsetw ( VGA.textmemptr + i * 80, blank, 80 );
    	VGA.csr_x = 0;
    	VGA.csr_y = 5;
	}
	move_csr();
}
void putxy( uint8 c, uint16 x, uint16 y ){
    uint16 att = VGA.attrib << 8;
    VGA.textmemptr[y * 80 + x] = c | att;
}
void putch( uint8 c )
{
    uint16 att = VGA.attrib << 8;

    if( c == 0x08 )
    {
        if( VGA.csr_x != 0 )
		{
			VGA.csr_x--;
			VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] = ' ' | att;
		}
    }
    else if( c == 0x09 )
    {
        VGA.csr_x = ( VGA.csr_x + 8 ) & ~( 8 - 1 );
    }
    else if( c == '\r' )
    {
        VGA.csr_x = 0;
    }
    else if( c == '\n' )
    {
        VGA.csr_x = 0;
        VGA.csr_y++;
    }
    else if( c >= ' ' )
    {
        VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] = c | att;
        VGA.csr_x++;
		VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] = VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] << 8;
		VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] = VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] >> 8;
		VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] |= att;
    }

    if( VGA.csr_x >= 80 )
    {
        VGA.csr_x = 0;
        VGA.csr_y++;
    }

    scroll();
	move_csr();
}
void move_csr( void )
{
    unsigned temp;
    temp = VGA.csr_y * 80 + VGA.csr_x;
    outportb( 0x3D4, 14 );
    outportb( 0x3D5, temp >> 8 );
    outportb( 0x3D4, 15 );
    outportb( 0x3D5, temp );
}

void puts( char *text )
{
    int i;

    for ( i = 0; i < strlen( text ); i++ )
    {
        putch( text[i] );
    }
}

void putsxy( char *text, int x, int y )
{
    int i;

    for ( i = 0; i < strlen( text ); i++ )
    {
        putxy( text[i], x + i, y );
    }
}

void settextcolor( uint8 fore, uint8 back )
{
    VGA.attrib = ( back << 4 ) | ( fore & 0x0F );
}

void init_video()
{
	fcls = 1;
    VGA.textmemptr = ( uint16 * ) 0xB8000;
    VGA.attrib = 0x0F;
	VGA.csr_x = 0;
	VGA.csr_y = 0;
	outportb( 0x3D4, 0x0A );
	outportb( 0x3D5, 0x00 );
	cls();
}
