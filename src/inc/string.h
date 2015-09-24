#ifndef _STRING_H
#define _STRING_H

#include "hstd.h"

uint8* memcpy ( uint8* dest, const uint8* src, size_t count );
uint16* memcpyw ( uint16* dest, const uint16* src, size_t count );
uint8* memset ( uint8* dest, uint8 val, size_t count );
uint16* memsetw ( uint16* dest, uint16 val, size_t count );
size_t strlen ( const char* str );
char *itoa ( int in );
char* htoa ( uint32 in );
sint32 atoi ( char* a );
sint32 atoi_o ( char *a, size_t offset );
sint32 strcmp ( const char* a, const char* b );
void *all_to_upperc( char *a );
char *all_to_upper( const char *a );
char *all_to_lower( const char *a );

#endif
