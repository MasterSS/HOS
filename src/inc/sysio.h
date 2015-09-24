#ifndef _SYSIO_H
#define _SYSIO_H

#include "hstd.h"

struct {
    uint16* textmemptr;
    uint16 attrib;
    uint16 csr_x , csr_y;
} VGA;

uint16 forecolor, backcolor;

char* cmdscroll[50], cmdnum, cmdcurr;

/* USER I/O */

int printf ( char* in, ... );
void putxy ( uint8 c, uint16 x, uint16 y );
void putsxy ( char* text, int x, int y );
void putch ( uint8 c );
void puts ( char* str );
void cls();
int scanf ( char* in, ... );
void settextcolor ( uint8 forecolor, uint8 backcolor );

/* PORT I/O */

uint8 inportb ( uint16 _port );
void outportb ( uint16 _port, uint8 _data );
void outportw ( uint16 _port, uint16 _data );

#endif
