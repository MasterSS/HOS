#include "HOS.h"

void scroll()
{
    uint16 blank, temp;

    blank = 0x20 | (VGA.attrib << 8);

    if(VGA.csr_y >= 25)
    {
        temp = VGA.csr_y - 25 + 1;
        memcpyw (VGA.textmemptr, VGA.textmemptr + temp * 80, (25 - temp) * 80 * 2);

        memsetw (VGA.textmemptr + (25 - temp) * 80, blank, 80);
        VGA.csr_y = 25 - 1;
    }
}

void move_csr()
{
    uint8 temp;

    temp = VGA.csr_y * 80 + VGA.csr_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void cls()
{
    uint16 blank;
    int i;

    blank = ' ' | (VGA.attrib << 8);
    for(i = 0; i < 25; i++)
        memsetw (VGA.textmemptr + i * 80, blank, 80);

    VGA.csr_x = 0;
    VGA.csr_y = 0;
    move_csr();
}

void putch(uint8 c)
{
    uint16 att = VGA.attrib << 8;

    if(c == 0x08)
    {
        if(VGA.csr_x != 0) VGA.csr_x--;
    }
    else if(c == 0x09)
    {
        VGA.csr_x = (VGA.csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        VGA.csr_x = 0;
    }
    else if(c == '\n')
    {
        VGA.csr_x = 0;
        VGA.csr_y++;
    }
    else if(c >= ' ')
    {
        VGA.textmemptr[ VGA.csr_y * 80 + VGA.csr_x ] = c | att;
        VGA.csr_x++;
    }

    if(VGA.csr_x >= 80)
    {
        VGA.csr_x = 0;
        VGA.csr_y++;
    }

    scroll();
    move_csr();
}

void puts(char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch( text[i]);
    }
}

void settextcolor(uint8 forecolor, uint8 backcolor)
{
    VGA.attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video()
{
    VGA.textmemptr = (uint16 *)0xb8000;
    VGA.attrib = 0x0F;
	VGA.csr_x = 0;
	VGA.csr_y = 0;
	cls();
}
