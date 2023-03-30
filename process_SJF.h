#ifndef _PROCESS_SJF_H_
#define _PROCESS_SJF_H_

#include "process_public.h"

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_SJF(void);

/**
 * load processes from newList to waitList and sort the waitList from early aTime to late
*/
void load_SJF();

void run_SJF();

#endif