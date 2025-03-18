#ifndef TASK_Q_H
#define TASK_Q_H

#define Num_of_T 6
#define Num_of_P 3

#include <stdbool.h>
#include <math.h>
#include <stdio.h>

/*
Task
Task i의 정보를 담고 있는 구조체
Task i는 (C,T)로 구성
i가 증가할 수록 우선 순위는 감소
Split task와 Non-split task, Body task tail task를 서로 구분하지 않음
*/

typedef struct Task 
{
    int priority; 
    int sub_num; 
    float runtime;
    float period;
    float Utilization; 
    bool Heavy; //  1 : Heavy, 0 : Light 
} task;


//Task 들을 관리할 자료 구조
typedef struct task_stack
{
    task* list[Num_of_T];
    int top; //현재 Stack에서 가장 top에 있는 자료의 위치
}task_stack;



float get_Utilization();
float get_lighttask(float U);

void init_task_stack(task_stack* task_arr);
bool is_full(task_stack* task_arr);
bool is_empty(task_stack* task_arr);

task* Pop_task(task_stack* task_arr);
void Push_task(task* T,task_stack* task_arr);
float init_taskset(task* temp_set[]);

void Copy(task* T,task* copied_task);
void Print_task(task* T);
task* new_task();


#endif /*TASK_Q_H_*/
