#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "Task_Q.h"

/*
Processor

Processor i의 정보를 담고 있는 구조체

Pnum: Processor의 고유 번호

Utilization: 현재 Processor에 할당된 Task들의 Utilization 총 합

WaitQ: 각 Processor에 할당된 Task들의 배열
*/


typedef struct Processor
{
    int Pnum;
    float Utilization;
    task_stack* Wait_Q;
    bool Pre_assigned; //1: Pre_assigned , 0: Normal
} processor;


//Processor들을 관리할 자료 구조
typedef struct Processor_stack
{
    processor* list[Num_of_P];
    int top; //현재 Stack에서 가장 top에 있는 자료의 위치
}processor_stack;


void init_processor_stack(processor_stack* processor_stack_ptr);
bool P_is_full(processor_stack* processor_stack_ptr);
bool P_is_empty(processor_stack* processor_stack_ptr);

void Push_processor(processor* P, processor_stack* processor_stack_ptr);
processor* Pop_processor(processor_stack* processor_stack_ptr);

void init_processor(processor* P_set[], task_stack* Wait_Q_set[]);
processor* get_min_processor(processor* processor_stack_ptr[],int len);

void Assign_task(task* T, processor* P);
void Print_processor(processor* P);


#endif /*PROCESSOR_H_*/