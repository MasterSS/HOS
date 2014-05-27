#include "HOS.h"

uint8 *memcpy(uint8 *dest, const uint8 *src, int count)
{
	const sint8 *sp = (const sint8 *)src;
    sint8 *dp = (sint8 *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}
uint16 *memcpyw(uint16 *dest, const uint16 *src, int count)
{
	const sint16 *sp = (const sint16 *)src;
    sint16 *dp = (sint16 *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

uint8 *memset(uint8 *dest, uint8 val, int count)
{
    uint8 *temp = (uint8 *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

uint16 *memsetw(uint16 *dest, uint16 val, int count)
{
    uint16 *temp = (uint16 *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

uint8 inportb (uint16 _port)
{
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16 _port, uint8 _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int calc(char *input)
{
    int a = 0;
    int b = 0;
    char optor;
    int i;
    for (i = 0; input[i] >= 48 && input[i] <= 57; i = i+1)
    {
        a = a * 10;
        a = a + input[i]-48;
    }
    optor = input[i];
    for (i = i + 1; input[i] >= 48 && input[i] <= 57; i = i+1)
    {
        b = b * 10;
        b = b + input[i]-48;
    }
    if (optor == '+')
        return a+b;
    if (optor == '-')
        return a-b;
    if (optor == '*')
        return a*b;
    if (optor == '/')
        return a/b;
}

void kmain(void)
{
	init_video();
	puts("Welcome to HOS v0.0.1");
}
