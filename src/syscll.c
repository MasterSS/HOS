#include "HOS.h"

extern void sys1();

void syscll_install () {
    idt_set_gate ( 48, ( unsigned ) sys1, 0x08, 0x8E );
}

void syscall_handler( struct regs* r ){
    if ( r->int_no == 48 )
        printf( "\n\t SYSCALL> Interrupt received", user );
    return;
}
