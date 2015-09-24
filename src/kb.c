#include "HOS.h"

unsigned char kbdus[128] =
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',	/* Backspace */
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0, /* 29 - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */ '\'', '`',
    0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdus_sh[128] =
{
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',	/* Backspace */
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0, /* 29 - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */ '\"', '~',
    0, /* Left shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
    'M', '<', '>', '?',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char a[50];
char b;
int shifted = 0;
char flag = 0;
char scanf_flag = 0;
extern char hcmd_b;
int cursor;

void keyboard_handler ( struct regs* r )
{
    uint8 scancode;
    scancode = inportb ( 0x60 );
    if ( scanf_flag == 0 )
    {
        if ( flag == 0 )
        {
            if ( scancode & 0x80 )
            {

            }
            else if ( shifted == 1 && scancode != 42 && scancode != 54 )
            {
                shifted = 0;
                if ( kbdus_sh[scancode] == '\b' )
                {
                    if ( aindex > 0 )
                    {
                        aindex--;
                        a[aindex] = '\0';
                        putch ( '\b' );
                    }
                    return;
                }
                else if ( kbdus[scancode] == '\n' )
                {
                    a[aindex-1] = '\0';
                    if ( aindex == 0 )
                    {
                        return;
                    }
                    hcmd_b = 1;
                    if ( strcmp ( cmdscroll[0], a ) )
                    {
                        return;
                    }
                    int lmk = 49;
                    if ( cmdscroll[lmk] != 0 )
                    {
                        free ( cmdscroll[lmk] );
                    }
                    for ( ; lmk > 0; lmk-- )
                    {
                        cmdscroll[lmk] = cmdscroll[lmk - 1];
                    }
                    cmdscroll[0] = malloc ( aindex );
                    int ol = 0;
                    for ( ; ol < aindex; ol++ )
                    {
                        cmdscroll[0][ol] = a[ol];
                    }
                    cmdscroll[0][aindex] = '\0';
                    cmdnum++;
                    return;
                }
                else if ( kbdus_sh[scancode] != 0 )
                {
                    b = kbdus_sh[scancode];
                    a[aindex] = kbdus_sh[scancode];
                    putch ( a[aindex] );
                    aindex++;
                    a[aindex] = '\0';
                }
            }
            else
            {
                if ( kbdus[scancode] == '\b' )
                {
                    if ( aindex > 0 )
                    {
                        aindex--;
                        a[aindex] = '\0';
                        putch ( '\b' );
                    }
                    return;
                }
                if ( kbdus[scancode] == '\n' )
                {
                    a[aindex] = '\0';
                    if ( aindex == 0 )
                    {
                        return;
                    }
                    hcmd_b = 1;
                    if ( strcmp ( cmdscroll[0], a ) )
                    {
                        return;
                    }
                    int lmk = 49;
                    if ( cmdscroll[lmk] != 0 )
                    {
                        free ( cmdscroll[lmk] );
                    }
                    for ( ; lmk > 0; lmk-- )
                    {
                        cmdscroll[lmk] = cmdscroll[lmk - 1];
                    }
                    cmdscroll[0] = 0;
                    cmdscroll[0] = malloc ( aindex + 1 );
                    int ol = 0;
                    for ( ; ol < aindex; ol++ )
                    {
                        cmdscroll[0][ol] = a[ol];
                    }
                    cmdscroll[0][aindex] = '\0';
                    cmdnum++;
                    return;
                }
                if ( kbdus[scancode] != 0 )
                {
                    b = kbdus[scancode];
                    a[aindex] = kbdus[scancode];
                    putch ( a[aindex] );
                    aindex++;
                    a[aindex] = '\0';
                }
                else if ( scancode == 42 || scancode == 54 )
                {
                    shifted = 1;
                }
                else if ( scancode == 72 )
                {
                    if ( aindex == 0 )
                    {
                        cursor = 0;
                    }
                    else if ( cursor < cmdnum - 1 )
                    {
                        cursor++;
                    }
                    while ( aindex > 0 )
                    {
                        aindex--;
                        a[aindex] = '\0';
                        putch ( '\b' );
                    }
                    int ol = 0;
                    for ( ; ol < strlen ( cmdscroll[cursor] ); ol++ )
                    {
                        a[ol] = cmdscroll[cursor][ol];
                    }
                    aindex = strlen ( cmdscroll[cursor] );
                    a[aindex] = '\0';
                    puts ( a );
                }
                else if ( scancode == 80 )
                {
                    if ( aindex == 0 )
                    {
                        cursor = 0;
                    }
                    else if ( cursor > 0 )
                    {
                        cursor--;
                    }
                    while ( aindex > 0 )
                    {
                        aindex--;
                        a[aindex] = '\0';
                        putch ( '\b' );
                    }
                    int ol = 0;
                    for ( ; ol < strlen ( cmdscroll[cursor] ); ol++ )
                    {
                        a[ol] = cmdscroll[cursor][ol];
                    }
                    aindex = strlen ( cmdscroll[cursor] );
                    a[aindex] = '\0';
                    puts ( a );
                }
            }
        }
        else
        {
            flag = 0;
        }
    }
    else
    {

        if ( scancode & 0x80 )
        {

        }
        else if ( shifted == 1 && scancode != 42 && scancode != 54 )
        {
            shifted = 0;
            if ( kbdus_sh[scancode] == '\b' )
            {
                if ( aindex > 0 )
                {
                    aindex--;
                    a[aindex] = '\0';
                    putch ( '\b' );
                }
                return;
            }
            else if ( kbdus_sh[scancode] == '\n' )
            {
                a[aindex] = '\0';
                if ( aindex == 0 )
                {
                    return;
                }
                scanf_flag = 0;
                return;
            }
            else if ( kbdus_sh[scancode] != 0 )
            {
                b = kbdus_sh[scancode];
                a[aindex] = kbdus_sh[scancode];
                putch ( a[aindex] );
                aindex++;
                a[aindex] = '\0';
            }
        }
        else
        {
            if ( kbdus[scancode] == '\b' )
            {
                if ( aindex > 0 )
                {
                    aindex--;
                    a[aindex] = '\0';
                    putch ( '\b' );
                }
                return;
            }
            if ( kbdus[scancode] == '\n' )
            {
                a[aindex] = '\0';
                if ( aindex == 0 )
                {
                    return;
                }
                scanf_flag = 0;
                return;
            }
            if ( kbdus[scancode] != 0 )
            {
                b = kbdus[scancode];
                a[aindex] = kbdus[scancode];
                putch ( a[aindex] );
                aindex++;
                a[aindex] = '\0';
            }
            else if ( scancode == 42 || scancode == 54 )
            {
                shifted = 1;
            }
        }





    }
}

void kb_install()
{
    irq_install_handler ( 1, keyboard_handler );
    b = -1;
    cursor = -1;
    aindex = 0;
}
char getch()
{
    while ( b == -1 )
    {
        return0();
    }
    putch ( b );
    char c = b;
    b = -1;
    return c;
}
void waitkey()
{
    flag = 1;
    printf ( "\n\t ?> Press a key to continue..." );
    while ( flag == 1 )
    {
        return0();
    }
    return;
}

int scanf ( char* in, ... )
{
    int i = 0, j = 0;
    uint32* argi, *tr;
    char* ou;
    argi = &in;
    int len = strlen ( in );
    for ( ; i < len; i++ )
    {
        if ( in[i] == '%' )
        {
            i++;
            if ( in[i] == 'i' )
            {
                argi++;
                scanf_flag = 1;
                while ( scanf_flag == 1 )
                {
                    return0();
                }
                tr = *argi;
                *tr = atoi ( a );
                aindex = 0;
            }
            if ( in[i] == 's' )
            {
                argi++;
                scanf_flag = 1;
                while ( scanf_flag == 1 )
                {
                    return0();
                }
                ou = *argi;
                for ( j = 0; j < strlen ( a ); j++ )
                {
                    ou[j] = a[j];
                }
                aindex = 0;
            }
        }
    }
    aindex = 0;
    return 0;

}
