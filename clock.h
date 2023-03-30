#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct _time{
    int time_now;
} CLOCK;

void clock_init();

int clock_now();

void clock_delay();


#endif