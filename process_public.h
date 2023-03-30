#ifndef _PROCESS_PUBLIC_H_
#define _PROCESS_PUBLIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "clock.h"

#define FCFS 1
#define SJF 2
#define HRRN 3
#define RR 4
#define HPF 5

typedef struct _pcb{
    char name[10];
    int pid;
    int priority;
    char state;
    int nTime;  //how long needed to be finished
    int rTime;  //how long it already run
    int aTime;  //time when arriving
    int fTime;  //time when finished
    int rspTime; //time when responsed
    struct _pcb *next;
} PCB;

typedef struct _processList{
    PCB* head;
    PCB* tail;
} List;

extern int ALGORITHM;
extern int PID;
extern PCB *runningList, *sp;
extern List *waitList, *newList, *exitList;

/**
 * initialize all the list
*/
void init();

/**
 * create a new process then initialize it and return its pointer
 * 
 * input pid of this process
 * return a struct _pcb pointer to this new process
*/
PCB* create_process();

/**
 * input a new process to newList and sort the newList according to arriving time
*/
void sort_newList(PCB *sp);

/**
 * kill a process which is not finished
 * 
 * the process sp will be killed from waitList or runningList, and memory space will be free
*/
void kill(PCB *sp);

/**
 * kill all the processes in waitList and runningList
*/
void killall(void);

/**
 * modify a process`s PCB
*/
void modify(PCB *sp);

/**
 * show the total number of processes in waitList
 * 
 * @returns the number of processes in waitList
*/
int pNumber(void);

/**
 * display all the PCBs in waitList or runningList
*/
void display();

#endif