#ifndef __HOS_H
#define __HOS_H

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned long long uint64;
typedef unsigned long long sint64;
struct {
	uint16 *textmemptr;
	uint16 attrib;
	uint16 csr_x ,csr_y;
}VGA;



/* MAIN.C */
extern uint8 *memcpy(uint8 *dest, const uint8 *src, int count);
extern uint16 *memcpyw(uint16 *dest, const uint16 *src, int count);
extern uint8 *memset(uint8 *dest, uint8 val, int count);
extern uint16 *memsetw(uint16 *dest, uint16 val, int count);
extern int strlen(const char *str);
extern uint8 inportb (uint16 _port);
extern void outportb (uint16 _port, uint8 _data);
/* SCRN.C */
extern void cls();
extern void putch(uint8 c);
extern void puts(char *str);
extern void settextcolor(uint8 forecolor, uint8 backcolor);
extern void init_video();



#endif
