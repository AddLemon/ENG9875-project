#include "process_FCFS.h"

// extern PCB *runningList, *sp;
// extern List *waitList, *newList, *exitList;

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_FCFS(void)
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
 * load processes from newList to waitList and sort the waitList from early aTime to late
*/
void load_FCFS()
{
    PCB* currentP = newList->head;
    PCB* nextP = NULL;

    // if(newList->head == NULL){
    //     fprintf(stderr, "Fail to load, newList is NULL\n");
    // }
    while(currentP != NULL){
        nextP = currentP->next;
        if(currentP->aTime == clock_now()){
            if(waitList->head==NULL){
                waitList->head = currentP;
                waitList->tail = currentP;
            }
            else{
                waitList->tail->next = currentP;
                waitList->tail = currentP;               
            }
        }
        else if(currentP->aTime > clock_now()){
            break;
        }
        newList->head = newList->head->next;
        currentP->next = NULL;
        currentP = nextP;
    }
}

void run_FCFS()
{
    if(runningList == NULL){
        clock_delay();
        load_FCFS();

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
        load_FCFS();

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