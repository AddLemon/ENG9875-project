#ifndef _TEST_H_
#define _TEST_H_

#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "algorithm.h"
#include "process_public.h"

#define aTime_short 5
#define aTime_max 30

#define nTime_short 5
#define nTime_long 15
#define nTime_max 20
#define process_number 50

#define aTime_short_mode 0
#define nTime_short_mode 1
#define nTime_long_mode 2
#define random_distribution 3

/**
 * generate @process_number processes and define with different range of nTime and aTime 
 * 
 * input number of porcesses with aTime less than @aTime_short 
 * and number of processes with nTime less than @nTime_short or greater than @nTime_long
*/
void generate(int aTime_ratio, int nTime_ratio, int mode);


#endif