#ifndef _PROCESS_HPF_H_
#define _PROCESS_HPF_H_

#include "process_public.h"

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_HPF(void);

/**
 * load a new process to waitList and sort the waitList from high priority to low
 * 
 * input a new process to waitList and sort the list, 
 * the beginning of the list with greater priority and the end of the list with lower priority
*/
void load_HPF();

void run_HPF();

#endif