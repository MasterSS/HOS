#include "hcmd.h"
#include "hstd.h"

uint32 t1,t2;

char *fparam ( const char *str, char *args, int strleng )
{
	int i = 0;
	int alen = strleng;
	char *b = ( char * ) malloc( 64 );
	int k = 0;
	for ( ; str[ i ] == ' ' || str[ i ] == '\t' ; i++ );
	for ( ; i < 64  && str[ i ] != ' ' && i < alen; i++, k++ ){
		b[ k ] = str[ i ];
        if ( str[i] == '\0' ){
            *args = '\0';
            return b;
        }
    }
	int j = 0;
	for (; str[ i ] == ' ' || str[ i ] == '\t';i++);
	for (; i < alen; i++, j++)
		args[ j ] = str[ i ];
	args[ j ] = 0;
	b[ i ] = 0;
	return b;
}

void calc ( const char *a )
{
	printf ("\n\t Calc> ");
	int i = 0;
	char *curnum = ( char * ) malloc ( 11 );
	for ( ; a[ i ] >= '0' && a[ i ] <= '9'; i++ )
		curnum[ i ] = a[ i ];
	curnum[ i ] = 0;
	int numa = atoi( curnum );
	for( ; a[ i ] == ' ' || a[ i ] == '\t'; i++ );
	char optor = a[ i ];
	i++;
	for( ; a[ i ] == ' ' || a[ i ] == '\t'; i++ );
	if ( a[ i ] < '0' || a[ i ] > '9' )
	{
	    printf ("Error: extra operator(s): ");
	    putch ( a[ i ] );
	    return;
	}
	int j = 0;
	for( ; (a[ i ] < '0' || a[ i ] > '9') && i < strlen( a ); i++ );
	for ( ; a[ i ] >= '0' && a[ i ] <= '9'; i++ )
	{
		curnum[ j ] = a[ i ];
		j++;
	}
	curnum[ j ] = 0;
	int numb = atoi( curnum );
	switch ( optor )
	{
	    case '+':
		printf ("%i", numa + numb);
		break;
	    case '-':
		printf ("%i", numa - numb);
		break;
	    case '*':
		printf ("%i", numa * numb);
		break;
	    case '/':
		printf ("%i", numa / numb);
		break;
	    case '^':
		printf ("%i", power( numa, numb ));
		break;
	    case '%':
		printf ("%i", numa % numb);
		break;
	    case '&':
		printf ("%i", numa & numb);
		break;
	    case '|':
		printf ("%i", numa | numb);
		break;
	    default:
		printf ("Error: Invalid Syntax");
		break;
	}
	free( ( uint32 ) curnum );
	return;
}


void hcmd( const char *str, int strindex )
{
	if ( !strindex )
	{
		return;
	}
	str = all_to_lower( str );
	char *args = ( char * ) malloc( 64 );
	char *fname = fparam( str, args, strindex );

	if ( strcmp( fname, "ticks" ) )
		printf("\n\t HOS> Tick count is %i ticks", T.ticks);
	else if ( strcmp( fname, "help" ) ){
		if ( !strlen( args ) )
            printf("\n\t HOS> Valid commands:\n\t - uptime \n\t - ticks \n\t - calc \n\t - setcolor \n\t - help \n\t - cls \n\t - dump \n\t - hello\n\t - ascii \n\t - delay\n\t - rand\n\t - setclock\n\t - version\n\t - interrupt");
		else if ( strcmp( args, "hello" ) ){
		    printf("\n\t HOS> Just type hello");
        }
        else if ( strcmp( args, "setcolor" ) ){
		    printf("\n\t HOS> Usage: setcolor $Color");
        }
        else if ( strcmp( args, "setclock" ) ){
		    printf("\n\t HOS> Usage: setclock $Hours:$Minutes:$Seconds");
        }
	}
	else if ( strcmp( fname, "uptime" ) )
		printf("\n\t HOS> Uptime is %i seconds", T.uptime);
/*	else if (strcmp(fname, "dma"))
	{
		char *stow = fname+200000; // = malloc;
		DMA_Block blk;
		blk.page = 0;
		blk.offset = stow;
		blk.length = 0xFF;
		StartDMA (3, &blk, 4);
		printf ("\n\t DMA> ");
		puts(stow);
	}*/
	else if ( strcmp( fname, "alloc" ) )
	{
		int size = atoi( args );
		uint32 ptr = malloc( size );
		printf("\n\t Malloc> Your address: %h in hex and %i in dec size: %i And fnum: %i", ptr, ptr, size, fnumg());
	}
	else if ( strcmp( fname, "free" ) )
	{
		uint32 ptr = atoi( args );
		free ( ptr );
		printf("\n\t Malloc> Freed address: %h And fnum: %i", ptr, fnumg());
	}
	else if ( strcmp( fname, "cls" ) )
	{
		cls();
	}
	else if ( strcmp( fname, "setcolor" ) )
	{
		if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
		else{
		    settextcolor( forecolor = atoi( args ), 0 );
        }
	}
	else if ( strcmp( fname, "setclock" ) )
	{
		if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument: use help as argument to see what to do!");
		else if( strcmp( args, "help" ) )
		    printf("\n\t HOS> To use setclock you should enter the following argument H/M/S");
        else
        {
            int a, b, c;
            a = ( args[ 0 ] - 48 ) * 10 + ( args[ 1 ] - 48 );
            b = ( args[ 3 ] - 48 ) * 10 + ( args[ 4 ] - 48 );
            c = ( args[ 6 ] - 48 ) * 10 + ( args[ 7 ] - 48 );
            clock = a * 3600 + b * 60 + c;
        }

	}
	else if ( strcmp( fname, "delay" ) )
	{
		if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
		else
		{
		    delay( atoi( args ) );
            printf("\n\t HOS> Delay Done!");
        }
	}
	else if ( strcmp( fname, "calc" ) )
	{
        if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
        else{
            settextcolor( 7, 0 );
            calc( args );
            settextcolor( forecolor, 0 );
        }
	}
	else if ( strcmp( fname, "hello" ) )
	{
		printf("\n\t HOS> Hello, %s",user);
	}
	else if ( strcmp( fname, "rand" ) )
	{
		printf("\n\t HOS> New random number = %i", rand() % 100);
	}
	else if ( strcmp( fname, "version" ) )
	{
        int per = 0;
        printf("\n\t HOS> version check : %i%", per);
        for( ; per < 101; per++ )
        {
            putch( '\b' );
            putch( '\b' );
            if( per > 9 )
                putch( '\b' );
            printf("%i%", per);
            delay( 10 );
        }
		printf("\n\t HOS> HOS v0.0.6");
	}
	else if ( strcmp( fname, "dump" ) )
	{
		if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
		else if( strcmp( args, "regs" ) ){
            __asm__ __volatile__("movl $60,%%eax;" "movl %%cr3,%%eax;" "movl %%eax,%0;" : "=a" ( t1 ) );
            __asm__ __volatile__("movl $60,%%eax;" "movl %%cr0,%%eax;" "movl %%eax,%0;" : "=a" ( t2 ) );
            printf("\n\t HOS> eax=%h ebx=%h ecx=%h edx=%h \n\t HOS> esp=%h ebp=%h edi=%h esi=%h \n\t HOS> es=%h ds=%h fs=%h gs=%h \n\t HOS> cs=%h ss=%h eflags=%h\n\t HOS> cr0=%h cr3=%h",dump_regs.eax,dump_regs.ebx,dump_regs.ecx,dump_regs.edx,dump_regs.esp,dump_regs.ebp,dump_regs.edi,dump_regs.esi,dump_regs.es,dump_regs.ds,dump_regs.fs,dump_regs.gs,dump_regs.cs,dump_regs.ss,dump_regs.eflags,t2,t1);
		}else
		    printf("\n\t HOS> ERROR: Argument not recognized ");
	}
	else if( strcmp( fname, "ascii" ) )
	{
        if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
        else
            printf("\n\t HOS> %i is the ascii code for %s", args[ 0 ], args);
	}
    else if( strcmp( fname, "interrupt" ) )
    {
        if ( !strlen( args ) )
		    printf("\n\t HOS> ERROR: Expected argument");
        else
            interrupt( atoi( args ) );
	}
	else if( strcmp( fname, "ftable" ) )
    {
        show_ftable();
	}
	else
	{
		printf("\n\t HOS> ERROR: Command not found : \'");
		puts( fname );
		putch( '\'' );
	}
	free( ( uint32 ) fname );
	free( ( uint32 ) args );
	printf("\n\t %s> ", user);
	return;
}
