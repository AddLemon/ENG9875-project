#ifndef _PROCESS_FCFS_H_
#define _PROCESS_FCFS_H_

#include "process_public.h"

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_FCFS(void);

/**
 * load processes from newList to waitList and sort the waitList from early aTime to late
*/
void load_FCFS();

void run_FCFS();

#endif