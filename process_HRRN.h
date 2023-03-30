#ifndef _PROCESS_HRRN_H_
#define _PROCESS_HRRN_H_

#include "process_public.h"

typedef struct _hrr{
    PCB* lastP;
    PCB* currentP;
    double hrr;
    int already_waitTime;
} HRR;

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_HRRN(void);

/**
 * load processes from newList to waitList and calculate Highest Response Ratio 
 * of all the processes in waitList, then find out the process with Highest Response Ratio.  
 * If with the same HRR, early arrived one first
*/
void load_HRRN();

void run_HRRN();

void free_HRRN();

#endif