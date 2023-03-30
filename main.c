#include "algorithm.h"
#include "process_FCFS.h"
#include "process_HPF.h"
#include "process_HRRN.h"
#include "process_STCF.h"
#include "process_SJF.h"
#include "test.h"


void set_algorithm()
{
    printf("Please enter the algorithm you want to use \
        (FCFS=%d, SJF=%d, HRRN=%d, RR=%d, HPF=%d", FCFS, SJF, HRRN, RR, HPF);
    scanf("%d", &ALGORITHM);
    switch(ALGORITHM){
        case FCFS: user_add_FCFS();
        //case SJF: user_add_SJF();
        //case HRRN: user_add_HRRN();
        //case RR: user_add_RR();
        case HPF: user_add_HPF();
    }
}

double avg_turnaroundTime()
{
    int sum = 0, num = 0;
    PCB* sp = exitList->head;
    while(sp != NULL){
        sum += sp->fTime - sp->aTime;
        num++;
        sp = sp->next;
    }
    return (double)sum/num;
}

double avg_responseTime()
{
    int sum = 0, num = 0;
    PCB* sp = exitList->head;
    while(sp != NULL){
        sum += sp->rspTime - sp->aTime;
        num++;
        sp = sp->next;
    }
    return (double)sum/num;
}


void random_weightedTurnaroundTime(FILE* fd)
{
    int turnTime = 0;
    double weightedTTime = 0;
    PCB* sp = exitList->head;
    while(sp != NULL){
        turnTime = sp->fTime - sp->aTime;
        fprintf(fd, "%d ", turnTime);
        sp = sp->next;
    }
    fprintf(fd, "\n");
    sp = exitList->head;
    while(sp != NULL){
        turnTime = sp->fTime - sp->aTime;
        weightedTTime = (double)turnTime/sp->nTime;
        fprintf(fd, "%f ", weightedTTime);
        sp = sp->next;
    }
    fprintf(fd, "\n");
    sp = exitList->head;
    while(sp != NULL){
        fprintf(fd, "%d ", sp->nTime);
        sp = sp->next;
    }
}

/** manual input */
// int main()
// {
//     init();
//     user_add_FCFS();
//     display();
//     while(1){
//         run_FCFS();
//         printf("at time %d:\n", clock_now());
//         printf("\n");
//         display();
//         printf("\n");
        
//         if(newList->head==NULL && waitList->head==NULL && runningList==NULL){
//             break;
//         }
//     }
// }

/** automatic imput */
int main()
{
    FILE* fd1 = fopen("STCF_turnaroundTime.txt", "aw");
    FILE* fd2 = fopen("STCF_responseTime.txt", "aw");
    FILE* fd3 = fopen("STCF_each_turnaroundTime.txt", "aw");
    fseek(fd1, 0, SEEK_END);
    fseek(fd2, 0, SEEK_END);
    fseek(fd3, 0, SEEK_END);

    if(fd1==NULL || fd2==NULL || fd3==NULL){
        printf("Error opening file!\n");
        return 1;
    }

    for(int a=0; a<=process_number; a++)
    {
        init();
        display();
        generate(a, a, random_distribution);
        display();

        printf("\nStart to run...\n\n");
        while(1){
            run_STCF();
            printf("at time %d:\n", clock_now());
            printf("\n");
            display();
            printf("\n");
            
            if(newList->head==NULL && waitList->head==NULL && runningList==NULL){
                break;
            }
        }

        double turnTime = avg_turnaroundTime();
        double respTime = avg_responseTime();
        fprintf(fd1, "%f ", turnTime);
        fprintf(fd2, "%f ", respTime);
    }

    /** calculate and record turnaround and weighted turnaround time of each process */
    init();
    display();
    generate(0, 0, random_distribution);
    display();

    printf("\nStart to run...\n\n");
    while(1){
        run_STCF();
        printf("at time %d:\n", clock_now());
        printf("\n");
        display();
        printf("\n");
        
        if(newList->head==NULL && waitList->head==NULL && runningList==NULL){
            break;
        }
    }

    random_weightedTurnaroundTime(fd3);

    
    
    fprintf(fd1, "\n");
    fprintf(fd2, "\n");

    fclose(fd1);
    fclose(fd2);
    fclose(fd3);
    
    killall();
    return 0;
}