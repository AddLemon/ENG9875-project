#include "test.h"



/**
 * generate @process_number processes and define with different range of nTime and aTime 
 * 
 * input number of porcesses with aTime less than @aTime_short 
 * and number of processes with nTime less than @nTime_short or greater than @nTime_long
*/
void generate(int aTime_ratio, int nTime_ratio, int mode){
    int cnt_aTime = aTime_ratio;
    int cnt_nTime = nTime_ratio;
    char n = 'a';
    srand((unsigned)time(NULL)); //init the random number

    for(int i=0; i<process_number; i++){
        PCB* sp = (PCB*)malloc(sizeof(PCB));

        sp->name[0] = n++;
        sp->pid = i;
        sp->priority = 0;
        sp->rTime = 0;
        sp->next = NULL;

        if(mode == aTime_short_mode){
            if(cnt_aTime != 0){
                sp->aTime = rand() % aTime_short + 1;
                cnt_aTime--;
            }
            else{
                sp->aTime = rand() % (aTime_max - aTime_short) + aTime_short + 1;
            }
            sp->nTime = rand() % nTime_max + 1;
        }
        else if(mode == nTime_short_mode){
            if(cnt_nTime != 0){
                sp->nTime = rand() % nTime_short + 1;
                cnt_nTime--;
            }
            else{
                sp->nTime = rand() % (nTime_max - nTime_short) + nTime_short + 1;
            }
            sp->aTime = rand() % (aTime_max + 1);
        }
        else if(mode == nTime_long_mode){
            if(cnt_nTime != 0){
                sp->nTime = rand() % (nTime_max - nTime_long) + nTime_long;
                cnt_nTime--;
            }
            else{
                sp->nTime = rand() % (nTime_long - 1) + 1;
            }
            sp->aTime = rand() % (aTime_max + 1);
        }
        else if(mode == random_distribution){
            sp->aTime = rand() % (aTime_max + 1);
            sp->nTime = rand() % nTime_max + 1;
        }
        
        sort_newList(sp);
    }
}