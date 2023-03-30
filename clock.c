#include "clock.h"

CLOCK* clock;

void clock_init()
{
    clock = (CLOCK*)malloc(sizeof(CLOCK));
    clock->time_now = -1;
}

int clock_now()
{
    //printf("Time is %d right now\n", clock->time_now);
    return clock->time_now;
}

void clock_delay()
{
    //sleep(1);
    clock->time_now++;
}