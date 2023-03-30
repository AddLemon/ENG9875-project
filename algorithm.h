#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <stdio.h>
#include <stdlib.h>
#include "process_FCFS.h"
#include "process_HPF.h"

void algorithm_FCFS();

/**
 * run the first process in waitList
 * 
 * this process will be removed from waitList and added to runningList
*/
void algorithm_HPF();


#endif