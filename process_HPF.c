#include "process_HPF.h"

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_HPF()
{
    int num, i;
    PCB* sp;
    printf("Please enter the number of process(s) you want to creat:");
    scanf("%d", &num);
    for(i=0; i<num; i++){
        printf("\nThis is No.%d process:", i);
        sp = create_process();
        
        sort_newList(sp);
    }
}

/**
 * load a new process to waitList and sort the waitList from high priority to low
 * 
 * input a new process to waitList and sort the list, 
 * the beginning of the list with greater priority and the end of the list with lower priority
*/
void load_HPF()
{
    PCB* sp = newList->head; //TODO 遍历newlist *****************************
    int check = 0;
    PCB* currentP, *nextP;
    
    //check if is the first time to make list or sp with higher priority than head
    if(waitList->head==NULL || \
    sp->priority>waitList->head->priority){  
        sp->next = waitList->head;
        waitList->head = sp;
        check++;
        if(waitList->head->next == NULL){
            waitList->tail = waitList->head;
        }
    }
    currentP = waitList->head;
    nextP = waitList->head->next;
    //if is not the first to make list, traverse to conpare the priority
    while(nextP != NULL){
        if(sp->priority<=currentP->priority && \
        sp->priority>nextP->priority){
            currentP->next = sp;
            sp->next = nextP;
            check++;
            break;
        }
        currentP = currentP->next;
        nextP = currentP->next;
    }
    //if sp`s priority is lower than every processes in waitList, add to the end
    if(check == 0){
        waitList->tail->next = sp;
        waitList->tail = sp;
    }
}

/**
 * run the first process in waitList
 * 
 * this process will be removed from waitList and added to runningList
*/
void run_HPF()
{
    load_HPF();
    
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
            sort_newList(runningList);
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

    clock_delay();
}