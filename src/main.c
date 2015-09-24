#include "HOS.h"

extern uint32 end;
extern uint32 mp;
extern uint32* pd;
char hcmd_b;

void return0() {
    return;
}

int interrupt ( uint8 interruptValue ) {
    if ( interruptValue < 48 )
        return -1;
    uint8* assembly = ( uint8* ) malloc ( 5 * sizeof ( uint8 ) );
    assembly[0] = 0xCD;
    assembly[1] = interruptValue;
    assembly[2] = 0xC2;
    assembly[3] = 0x00;
    assembly[4] = 0x00;
    __asm__ __volatile__ ( "call %0" : "=a" ( assembly ) );
    free ( assembly );
    return 0;
}

void all_install() {
    gdt_install();
    idt_install();
    timer_install();
    kb_install();
    syscll_install();
    irq_install();
    pmode();
}

void kmain ( void ) {
    init_video();
    __asm__ __volatile__ ( "sti" );
    settextcolor ( forecolor = 6, backcolor = 0 );
    printf ( "\n\n                    ----> WELCOME TO HOS (v0.0.6) <----      Devs:SS and ADH \n" );
    int i = 1;
    //for devs
    putxy ( 186, 60, 2 );
    putxy ( 186, 76, 2 );
    putxy ( 201, 60, 1 );
    putxy ( 200, 60, 3 );
    putxy ( 187, 76, 1 );
    putxy ( 188, 76, 3 );
    for ( ; i < 16; i++ ) {
        putxy ( 205, 60 + i, 1 );
        putxy ( 205, 60 + i, 3 );
    }


    // for clock
    char tr[ 8 ];
    tr[0] = tr[1] = tr[3] = tr[4] = tr[6] = tr[7] = '0';
    tr[2] = tr[5] = ':';
    putsxy ( tr, 5, 2 );
    putxy ( 186, 4, 2 );
    putxy ( 186, 13, 2 );
    putxy ( 201, 4, 1 );
    putxy ( 200, 4, 3 );
    putxy ( 187, 13, 1 );
    putxy ( 188, 13, 3 );
    putxy ( ' ', 14, 2 );
    putxy ( ' ', 15, 2 );
    putxy ( ' ', 16, 2 );
    for ( i = 1; i < 9; i++ ) {
        putxy ( 205, 4 + i, 1 );
        putxy ( 205, 4 + i, 3 );
    }
    //for logo
    putxy ( 186, 19, 2 );
    putxy ( 186, 55, 2 );
    putxy ( 201, 19, 1 );
    putxy ( 200, 19, 3 );
    putxy ( 187, 55, 1 );
    putxy ( 188, 55, 3 );
    for ( i = 1; i < 36; i++ ) {
        putxy ( 205, 19 + i, 1 );
        putxy ( 205, 19 + i, 3 );
    }
    printf ( "\n\n  ____________________________________________________________________________\n\n" );
    settextcolor ( forecolor = 5, backcolor );
    printf ( "\n\t HOS> Please enter Your username: " );
    scanf ( "%s", &user );
    all_to_upperc ( user );
    printf ( "\n\t %s> ", user );
    cmdcurr = -1;
    cmdnum = 0;
    aindex = 0;
/*
    struct Node_list nd;
    insert_list_const( li, 10, 20, nd );
    struct Node_list *node = li->start;
    while ( node != li->end ){
        node = node->next;
        printf ( "\n\t HOS> %d is s and %d is t ", node->s, node->t );
    }*/
    extern int ndosiz;
    extern struct Node_list ndo[1000];
    for ( i = 0; i < ndosiz; i++ )
        printf("\n\t HOS> ndo NODE %d : %h ---> %h", i, ndo[i].s, ndo[i].t);
    for (;;) {
        if ( hcmd_b == 1 ) {
            hcmd ( a, aindex );
            hcmd_b = 0;
            aindex = 0;
        }
        delay ( 1 );
    }
}
