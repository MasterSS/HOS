#include "hstd.h"
#include "multiboot.h"

struct Node_list nod[1000];
int nodsiz;

void get_ram(multiboot_info_t* mbd, unsigned int magic){
    if ( CHECK_BIT(mbd->flags, 6) ){
        uint32 addr = mbd->mmap_addr, len = mbd->mmap_length;
        memory_map_t* mmap = mbd->mmap_addr;
        ndosiz = 0;
        while(mmap < addr + len){
            struct Node_list nd;
            if( mmap->type == 1 ){
                nod[nodsiz].s = mmap->base_addr_low;
                nod[nodsiz].t = mmap->base_addr_low + mmap->length_low;
                nodsiz++;
            }
            mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
        }
    }
}
