#include "process_SJF.h"

// extern PCB *runningList, *sp;
// extern List *waitList, *newList, *exitList;

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_SJF(void)
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
 * load processes from newList to waitList and sort the waitList from short needed time (nTime) to long
*/
void load_SJF()
{
    PCB* sp;
    while((newList->head != NULL) && (clock_now() == newList->head->aTime)){
        sp = newList->head;
        newList->head = newList->head->next;
        sp->next = NULL;
        if(waitList->head == NULL){
            waitList->head = waitList->tail = sp;
        }
        /* traverse the waitList to add sp to make sure waitList is sorted  */
        else{
            int check = 0;
            PCB* currentP = waitList->head;
            PCB* nextP = currentP;

            if(sp->nTime < currentP->nTime){
                sp->next = waitList->head;
                waitList->head = sp;
                check = 1;
            }
            else{
                while(nextP != NULL){
                    if(sp->nTime < nextP->nTime){
                        currentP->next = sp;
                        sp->next = nextP;
                        check = 1;
                        break;
                    }
                    currentP = nextP;
                    nextP = nextP->next;
                }
            }
            if(check == 0){
                waitList->tail->next = sp;
                waitList->tail = sp;
            }
        }
    }
}

void run_SJF()
{
    if(runningList == NULL){
        clock_delay();
        load_SJF();

        /* remove the first process from waitList, then add the process to runningList */
        if(waitList->head != NULL){
            runningList = waitList->head;
            waitList->head = waitList->head->next;
            runningList->next = NULL;
            runningList->state = 'r';
            runningList->rspTime = clock_now();
        }
    }
    else{
        runningList->rTime++;
        clock_delay();
        load_SJF();

        /* check if the process in runningList finished */
        if(runningList->rTime == runningList->nTime){
            runningList->state = 'f';
            runningList->fTime = clock_now();
            if(exitList->head == NULL){
                exitList->head = runningList;
                exitList->tail = exitList->head;
            }
            else{
                exitList->tail->next = runningList;
                exitList->tail = exitList->tail->next;
            }
            runningList = NULL;

            /* remove the first process from waitList, then add the process to runningList */
            if(waitList->head != NULL){
                runningList = waitList->head;
                waitList->head = waitList->head->next;
                runningList->next = NULL;
                runningList->state = 'r';
                runningList->rspTime = clock_now();
            }
        }
    }
}