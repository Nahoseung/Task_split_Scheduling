#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include "Task_Q.h"

/*
Processor
Processor i의 정보를 담고 있는 구조체

Pnum: 현재 Processor의 번호

Utilization: 현재 Processor에 할당된 Task들의 Utilization 총 합

WaitQ: 각 Processor에 할당된 Task들의 배열
*/

typedef struct Processor
{
    int Pnum;
    float Utilization;
    task_stack* Wait_Q;
} processor;



processor* Pop_processor(processor* processor_stack_ptr[]);
void init_processor(processor* processor_stack_ptr[]);
void Assign_task(task* T, processor* P);
void Print_processor(processor* P);

#endif/*PROCESSOR_H_*/