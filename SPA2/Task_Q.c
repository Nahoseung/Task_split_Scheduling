#include "Task_Q.h"

task task_pool[Num_of_P-1];  // Split task 상한 : Num_of_P -1
int pool_index = 0;


/******************* Utilization ***********************/
float get_Utilization()
{
    float n = Num_of_T;
    float U = n * (pow(2.0, 1.0 / n) - 1);
    printf("For %d tasks Utilization Bound is :  %f \n",Num_of_T, U);
    return U;
}

float get_lighttask(float U)
{
    float Light_bound = U/(1+U);
    printf("For %d tasks Light_Bound is :  %f \n",Num_of_T, Light_bound);
    return Light_bound;
}


/******************* Task_stack ***********************/

void init_task_stack(task_stack* task_stack_ptr)
{
    task_stack_ptr->top = -1; //현재 stack에 들어가 있는 task를 가리킴
}

bool is_full(task_stack* task_stack_ptr)
{
    if(task_stack_ptr->top >= (Num_of_T - 1) ) return true;
    return false;
}

bool is_empty(task_stack* task_stack_ptr)
{
    if(task_stack_ptr->top < 0) return true;
    return false;
}


task* Pop_task(task_stack* task_stack_ptr)
{
    if(is_empty(task_stack_ptr))
    {
        printf("UNDER FLOW\n");
        return NULL;
    }

    return task_stack_ptr->list[task_stack_ptr->top--];
}

void Push_task(task* T, task_stack* task_stack_ptr)
{
    if(is_full(task_stack_ptr))
    {
        printf("OVER FLOW\n");
        return;
    }

    task_stack_ptr->list[++task_stack_ptr->top] = T;
    return;
}

/******************* Task Util ***********************/

float init_taskset(task* task_set[])
{
    float U = get_Utilization();
    float Light_Bound = get_lighttask(U);
    
    for(int i=0;i<Num_of_T;i++)
    {
        task_set[i]->Utilization = task_set[i]->runtime / task_set[i]->period;
        task_set[i]->synthetic_deadline = task_set[i]->period;
        task_set[i]->Assigned_P = 0;
        if(task_set[i]->Utilization > Light_Bound) task_set[i]->Heavy = true;
        else task_set[i]->Heavy = false;
    }
    
    return U;
}


void Copy(task* T, task* copied_task)
{
    copied_task->priority = T->priority;
    copied_task->sub_num = T->sub_num;
    copied_task->period = T->period;
    copied_task->Utilization = T->Utilization;
    return;
}

void Print_task(task* T)
{
    printf("Task (%d,%d) : %f ( %f / %f -> %f ) \n",T->priority,T->sub_num,T->Utilization,T->runtime,T->period,T->synthetic_deadline);
    return;
}

task* new_task()
{
    if(pool_index> Num_of_P)
    {
        printf("NO MORE SPLIT");
        return NULL;
    }

    return &task_pool[pool_index++];
}

void init_task_info(task* task_manager[])
{
    for(int i=0;i<Num_of_T+1;i++){
        task_manager[i] = NULL;
    }
    return;
}


/// *************** Test  *************** ///

// int main()
// {
//     init_taskset(UQ);
//     init_pool();
//     task* temp = Pop_task(UQ);
//     printf("%d , %d , %f , %f , %f \n",temp->priority,temp->sub_num,temp->runtime,temp->period,temp->Utilization);
//     temp = Pop_task(UQ);
//     printf("%d , %d , %f , %f , %f \n",temp->priority,temp->sub_num,temp->runtime,temp->period,temp->Utilization);
//     temp = Pop_task(UQ);
//     printf("%d , %d , %f , %f , %f \n",temp->priority,temp->sub_num,temp->runtime,temp->period,temp->Utilization);
//     temp = Pop_task(UQ);
//     printf("%d , %d , %f , %f , %f \n",temp->priority,temp->sub_num,temp->runtime,temp->period,temp->Utilization);
//     temp = Pop_task(UQ);
//     printf("%d , %d , %f , %f , %f \n",temp->priority,temp->sub_num,temp->runtime,temp->period,temp->Utilization);
// }