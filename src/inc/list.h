#ifndef _LIST_H
#define _LIST_H

#include "hstd.h"

#define SUCCESS 0
#define OUT_OF_BOUNDS -100
#define SIZE_LIMIT -101

struct list{
    struct Node_list{
        struct Node_list *prev;
        int s, t;
        struct Node_list *next;
    };
    struct Node_list *start, *end;
    int size;
};

struct list *make_list( int l, ... );
int insert_list( struct list* l, int s, int t );
int erase_list( struct list* l, int ind );
int insert_list_const( struct list* l, int s, int t, struct Node_list nd);

#endif
