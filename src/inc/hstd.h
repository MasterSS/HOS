#include "math.h"
#include "algorithm.h"
#include "string.h"
#include "list.h"
#include <limits.h>
#include <float.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdnoreturn.h>

#ifndef _HSTD_H
#define _HSTD_H

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

typedef unsigned char uint8;
typedef unsigned char uchar;
typedef signed char schar;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;

struct regs {
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;
} dump_regs;

struct time {
    uint32 uptime;
    uint32 ticks;
};

struct time T;
uint32 clock;

char user[20];

char a[50];
int aindex;
int arse;

struct list *mem_list;

int interrupt ( uint8 interruptValue );

#endif
