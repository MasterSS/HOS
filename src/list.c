#include "list.h"

int insert_list_const( struct list* l, int s, int t, struct Node_list nd){
    if ( l->size >= 100 * 1000 )
        return SIZE_LIMIT;
    struct Node_list *node;
    node = &nd;
    node->s = s;
    node->t = t;
    node->prev = l->end->prev;
    node->next = l->end;
    l->end->prev->next = node;
    l->end->prev = node;
    l->size++;
    return SUCCESS;
}

int insert_list( struct list* l, int s, int t ){
    if ( l->size >= 100 * 1000 )
        return SIZE_LIMIT;
    struct Node_list *node;
    node = malloc(sizeof(struct Node_list));
    node->s = s;
    node->t = t;
    node->prev = l->end->prev;
    node->next = l->end;
    l->end->prev->next = node;
    l->end->prev = node;
    l->size++;
    return SUCCESS;
}

int erase_list( struct list* l, int ind ){
    struct Node_list* node;
    node = l->start->next;
    int i = 0;
    while( i < ind ){
        if ( i > l->size )
            return OUT_OF_BOUNDS;
        node = node->next;
        i++;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free( (uint32)node );
    return SUCCESS;
}

struct list *make_list( int l, ... ){
    struct list* li;
    li = malloc(sizeof(struct list));
    li->size = 0;
    li->end->prev = li->start;
    li->start->next = li->end;
    va_list va;
    va_start( va, l );
    int i;
    for ( i = 0; i < l; i += 2 )
        insert_list( li, va_arg( va, int ), va_arg( va, int ) );
    va_end(va);
    return li;
}
