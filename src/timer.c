#include "HOS.h"

struct time T;
int tsp[6];
int h, m, s;

void timer_handler ( struct regs* r ) {
    dump_regs = *r;
    T.ticks++;
    if ( T.ticks % 1000 == 0 ) {
        T.uptime++;
        clock++;

        s = clock % 60;
        m = ( clock / 60 ) % 60;
        h = ( ( clock / 60 ) / 60 ) % 24;
        tsp[4] = s / 10;
        tsp[5] = s % 10;
        tsp[2] = m / 10;
        tsp[3] = m % 10;
        tsp[0] = h / 10;
        tsp[1] = h % 10;
        settextcolor ( 6, 0 );
        putxy ( 48 + tsp[0], 5, 2 );
        putxy ( 48 + tsp[1], 6, 2 );
        putxy ( ':', 7, 2 );
        putxy ( 48 + tsp[2], 8, 2 );
        putxy ( 48 + tsp[3], 9, 2 );
        putxy ( ':', 10, 2 );
        putxy ( 48 + tsp[4], 11, 2 );
        putxy ( 48 + tsp[5], 12, 2 );
        settextcolor ( forecolor, 0 );
    }
}

extern void set_timer_interval();

void timer_install() {
    irq_install_handler ( 0, timer_handler );
    T.uptime = 0;
    T.ticks = 0;
    clock = 0;
    set_timer_interval();
}

void delay ( uint32 miliseconds ) {
    uint32 esec;
    esec = T.ticks + miliseconds;
    while ( T.ticks < esec )
        return0();
}
