#include "process_HRRN.h"

HRR* hrrP;

/**
 * creat a new process, then add to waitList and sort
*/
void user_add_HRRN(void)
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
 * load processes from newList to waitList and calculate Highest Response Ratio 
 * of all the processes in waitList, then find out the process with Highest Response Ratio.  
 * If with the same HRR, early arrived one first
*/
void load_HRRN()
{
    PCB* currentP = newList->head;
    PCB* currentWP = waitList->head;
    PCB* lastWP = NULL;
    int already_waitTime, now_finishTime = 0;
    double hrr, hrr_max = 0;
    hrrP = (HRR*)malloc(sizeof(HRR));

    // if(newList->head == NULL){
    //     fprintf(stderr, "Fail to load, newList is NULL\n");
    // }
    int a = clock_now();
    /* traverse newList to load arrived processes to waitList */
    while(currentP != NULL){  
        if(currentP->aTime == clock_now()){
            if(waitList->head == NULL){
                waitList->head = waitList->tail = currentP;
                currentWP = waitList->head;
            }
            else{
                waitList->tail->next = currentP;
                waitList->tail = waitList->tail->next;
            }
        }
        else if(currentP->aTime > clock_now()){
            break;
        }
        newList->head = newList->head->next;
        currentP = newList->head;
        waitList->tail->next = NULL;
    }

    /* find out the process with Highest Response Ratio in waitList */
    if(runningList != NULL){
        now_finishTime = runningList->nTime - runningList->rTime;
    }
    while(currentWP != NULL){   
        already_waitTime = clock_now() - currentWP->aTime;
        hrr = (now_finishTime + already_waitTime) / currentWP->nTime + 1; //TODO 检查输出是否为double
        
        if(hrr > hrr_max){
            hrrP->lastP = lastWP;
            hrrP->currentP = currentWP;
            hrrP->hrr = hrr;
            hrrP->already_waitTime = already_waitTime;

            hrr_max = hrr;
        }
        //with same hrr, smaller aTime first
        else if((hrr == hrr_max) && (already_waitTime > hrrP->already_waitTime)){
            hrrP->lastP = lastWP;
            hrrP->currentP = currentWP;
            hrrP->hrr = hrr;
            hrrP->already_waitTime = already_waitTime;

            hrr_max = hrr;
        }
        
        lastWP = currentWP;
        currentWP = currentWP->next;
    }

}

void run_HRRN()
{
    if(runningList == NULL){
        clock_delay();
        load_HRRN();

        if(waitList->head != NULL){
            /* remove a new HRR process from waitList */
            if(hrrP->currentP == waitList->head){
                waitList->head = waitList->head->next;
                hrrP->currentP->next = NULL;
            }
            else if(hrrP->currentP == waitList->tail){
                waitList->tail = hrrP->lastP;
                waitList->tail->next = NULL;
            }
            else{
                hrrP->lastP->next = hrrP->currentP->next;
                hrrP->currentP->next = NULL;
            }

            /* then add new process to runningList */
            hrrP->currentP->state = 'r';
            runningList = hrrP->currentP;
            runningList->rspTime = clock_now();
        }
    }
    else{
        runningList->rTime++;
        clock_delay();
        load_HRRN();

        /* check if the process in runningList finished */
        if(runningList->rTime == runningList->nTime){
            runningList->state = 'f';
            runningList->fTime = clock_now();
            if(exitList->head == NULL){
                exitList->head = exitList->tail = runningList;
            }
            else{
                exitList->tail->next = runningList;
                exitList->tail = exitList->tail->next;
            }
            runningList = NULL;
            if(waitList->head != NULL){
                /* remove a new HRR process from waitList */
                if(hrrP->currentP == waitList->head){
                    waitList->head = waitList->head->next;
                    hrrP->currentP->next = NULL;
                }
                else if(hrrP->currentP == waitList->tail){
                    waitList->tail = hrrP->lastP;
                    waitList->tail->next = NULL;
                }
                else{
                    hrrP->lastP->next = hrrP->currentP->next;
                    hrrP->currentP->next = NULL;
                }

                /* then add new process to runningList */
                hrrP->currentP->state = 'r';
                runningList = hrrP->currentP;
                runningList->rspTime = clock_now();
            }
        }
    }
}


void free_HRRN()
{
    free(hrrP);
}