#ifndef _PROCESS_H
#define _PROCESS_H

#include "hstd.h"
#include "limits.h"
#include "sysio.h"
#include "string.h"

struct process
{
    uint16 pid;
    char* name;
    uint8 flags;
    uint32* membeg, *memend;
};

struct jque
{
    process* front, *end;
    size_t size;
    struct Node
    {
        process* prev;
        process val;
        process* next;
    };
};

void push ( jque q, process a );
void pop ( jque q );
process front ( jque q );
size_t size( jque q );

#endif
