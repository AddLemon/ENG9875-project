#include "algorithm.h"

void algorithm_FCFS()
{
    if(waitList->head == NULL){
        fprintf(stderr, "Failed to run, waitList is NULL\n");
    }
    else{
        runningList = waitList->head;
        waitList->head = waitList->head->next;
        runningList->next = NULL;
        runningList->state = 'r';
        while(runningList->nTime > runningList->rTime){
            runningList->rTime++;
            clock_delay();
        }
        if(runningList->nTime == runningList->rTime){
            runningList->state = 'f';
            if(exitList->head == NULL){
                exitList->head = runningList;
                exitList->tail = exitList->head;
            }
            else{
                exitList->tail->next = runningList;
                exitList->tail = exitList->tail->next;
            }
        }
        runningList = NULL;
    }
}

/**
 * run the first process in waitList
 * 
 * this process will be removed from waitList and added to runningList
*/
void algorithm_HPF()
{
    if(waitList->head == NULL){
        fprintf(stderr, "Failed to run, waitList is NULL\n");
    }
    else{
        runningList = waitList->head;
        waitList->head = waitList->head->next;

        runningList->state = 'r';
        if(runningList->nTime > runningList->rTime+1){
            runningList->rTime++;
            runningList->priority--;
            runningList->state = 'w';
            sort(runningList);
        }
        else if(runningList->nTime == runningList->rTime+1){
            runningList->state = 'f';
            if(exitList->head == NULL){
                exitList->head = runningList;
                exitList->tail = exitList->head;
            }
            else{
                exitList->tail->next = runningList;
                exitList->tail = exitList->tail->next;
            }
        }
        runningList = NULL;
    }
}