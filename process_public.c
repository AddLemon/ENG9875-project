#include "process_public.h"

int ALGORITHM;
int PID = 0;
PCB *runningList, *sp;
List *waitList, *newList, *exitList;

void init()
{
    waitList = (struct _processList*)malloc(sizeof(struct _processList));
    newList = (struct _processList*)malloc(sizeof(struct _processList));
    exitList = (struct _processList*)malloc(sizeof(struct _processList));
    waitList->head = waitList->tail = NULL;
    newList->head = newList->tail = NULL;
    exitList->head = exitList->tail = NULL;
    runningList = NULL;
    clock_init();
}

/**
 * create a new process then initialize it and return its pointer
 * 
 * return a struct _pcb pointer to this new process
*/
PCB* create_process()
{
    sp = (PCB*)malloc(sizeof(PCB));
    printf("\n\tThe pid of this process is %d", PID);
    printf("\n\tThe name of the process is: ");
    scanf("%s", sp->name);
    if(ALGORITHM){
        printf("\n\tThe priority of the process is: ");
        scanf("%d", &sp->priority);
    }
    else sp->priority = 0;
    printf("\n\tThe arriving time of the process is: ");
    scanf("%d", &sp->aTime);
    printf("\n\tThe cost time of the process is: ");
    scanf("%d", &sp->nTime);
    sp->pid = PID;
    sp->state = 'w';
    sp->rTime = 0;
    sp->fTime = 0;
    sp->rspTime = 0;
    sp->next = NULL;
    PID++;

    return sp;
}

/**
 * input a new process to newList and sort the newList according to arriving time
*/
void sort_newList(PCB *sp)
{
    PCB* currentP, *nextP;
    int check = 0;

    if(newList->head==NULL || sp->aTime<newList->head->aTime){
        sp->next = newList->head;
        newList->head = sp;
        check = 1;
        if(newList->tail == NULL){
            newList->tail = sp;
        }
    }
    else{
        currentP = newList->head;
        nextP = currentP->next;
        while(nextP != NULL){
            if(sp->aTime>=currentP->aTime && sp->aTime<nextP->aTime){
                currentP->next = sp;
                sp->next = nextP;
                check = 1;
                break;
            }
            currentP = currentP->next;
            nextP = currentP->next;
        }
    }
    if(check == 0){
        newList->tail->next = sp;
        newList->tail = sp;
    }
}


/**
 * kill a process which is not finished
 * 
 * the process sp will be killed from waitList or runningList, and memory space will be free
*/
void kill(PCB* sp)
{
    if(sp->state == 'w'){
        PCB* i;
        for(i=waitList->head; i!=NULL; i=i->next){
            if(i->next == sp){
                i->next = sp->next;
                free(sp);
            }
        }
    }
    else if(sp->state == 'r'){
        free(sp);
    }
}

/**
 * kill all the processes in waitList and runningList
*/
void killall()
{
    PCB* i, *j;
    i = waitList->head;
    while(i != NULL){
        j = i->next;
        free(i);
        i = j;
    }
    free(waitList);
    free(runningList);
}

/**
 * modify a process`s PCB
*/
void modify(PCB* sp);

/**
 * show the total number of processes in waitList
 * 
 * @returns the number of processes in waitList
*/
int pNumber()
{
    int cnt = 0;
    PCB* i;
    for(i=waitList->head; i!=NULL; i=i->next){
        cnt++;
    }
    return cnt;
}

/**
 * display all the PCBs in waitList or runningList
*/
void display()
{
    PCB* i;
    if(runningList != NULL){
        printf("     runningList:\n");
        printf("\t|name|\t\t|pid|\t|priority|\t|arrivingTime|\t|needTime|\t|alreadyRunTime|\n");
        i = runningList;
        printf("\t%s\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", i->name, i->pid, i->priority, i->aTime, i->nTime, i->rTime);
    }
    if(waitList->head != NULL){
        printf("     waitList:\n");
        printf("\t|name|\t\t|pid|\t|priority|\t|arrivingTime|\t|needTime|\t|alreadyRunTime|\n");
        for(i=waitList->head; i!=NULL; i=i->next){
            printf("\t%s\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", i->name, i->pid, i->priority, i->aTime, i->nTime, i->rTime);
        }
    }
    if(newList->head != NULL){
        printf("     newList:\n");
        printf("\t|name|\t\t|pid|\t|priority|\t|arrivingTime|\t|needTime|\t|alreadyRunTime|\n");
        for(i=newList->head; i!=NULL; i=i->next){
            printf("\t%s\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", i->name, i->pid, i->priority, i->aTime, i->nTime, i->rTime);
        }
    }
    if(exitList->head != NULL){
        printf("     exitList:\n");
        printf("\t|name|\t\t|pid|\t|priority|\t|arrivingTime|\t|needTime|\t|finishTime|\n");
        for(i=exitList->head; i!=NULL; i=i->next){
            printf("\t%s\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", i->name, i->pid, i->priority, i->aTime, i->nTime, i->fTime);
        }
    }
}