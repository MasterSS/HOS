#ifndef _HCMD_H
#define _HCMD_H

#include "HOS.h"

char *fparam ( const char *str, char *args, int strleng );
void hcmd( const char *str, int strindex );
void calc ( const char *a );
void show_ftable();

#endif
