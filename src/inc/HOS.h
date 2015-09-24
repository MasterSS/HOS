#ifndef __HOS_H
#define __HOS_H

#pragma once


#include "hstd.h"
#include "sysio.h"
#include "hcmd.h"

/* MAIN.CPP */
void kmain();
void all_install();
void return0();
int interrupt ( uint8 interruptValue );
/* START.ASM*/
void flush_cache();
void pmode();
/* SCRN.C */
void init_video();
void move_csr();
/* GDT.C */
void gdt_install();
/* IDT.C */
void idt_install();
void idt_set_gate ( unsigned char num, unsigned long base, unsigned short sel, unsigned char flags );
/* ISR.C */
void isrs_install();
/* IRQ.C */
void irq_install();
void irq_install_handler ( int irq, void ( *handler ) ( struct regs* r ) );
void irq_uninstall_handler ( int irq );
/* TIMER.C */
void delay ( uint32 sec );
void timer_install();
/* KB.C */
void kb_install();
char getch();
void waitkey();
/* PG.C */
uint32 end;
uint32 malloc ( int size );
void init_malloc();
void init_pmap();
void install_pg();
uint32 fnumg();
void show_ftable();
void free ( uint32 ptr );

#endif
