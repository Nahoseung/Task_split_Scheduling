#include "Task_Q.h"

task task_pool[Num_of_P-1];  // Split task 상한 : Num_of_P -1
int pool_index = 0;


/****** *******/
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


/// *************** Task stack  *************** ///

void init_task_stack(task_stack* task_arr)
{
    task_arr->top = -1; //현재 stack에 들어가 있는 task를 가리킴
}

bool is_full(task_stack* task_arr)
{
    if(task_arr->top >= (Num_of_T - 1) ) return true;
    return false;
}

bool is_empty(task_stack* task_arr)
{
    if(task_arr->top < 0) return true;
    return false;
}


task* Pop_task(task_stack* task_arr)
{
    if(is_empty(task_arr))
    {
        printf("UNDER FLOW\n");
        return NULL;
    }

    return task_arr->list[task_arr->top--];
}

void Push_task(task* T, task_stack* task_arr)
{
    if(is_full(task_arr))
    {
        printf("OVER FLOW\n");
        return;
    }

    task_arr->list[++task_arr->top] = T;
    return;
}


float init_taskset(task* temp_set[])
{
    float U = get_Utilization();
    float Light_Bound = get_lighttask(U);
    
    for(int i=0;i<Num_of_T;i++)
    {
        temp_set[i]->Utilization = temp_set[i]->runtime / temp_set[i]->period;

        if(temp_set[i]->Utilization > Light_Bound) temp_set[i]->Heavy = true;
        else temp_set[i]->Heavy = false;
    }
    
    return U;
}

/****** Task util ******/

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
    printf("Task (%d,%d) : %f ( %f / %f ) Heavy : %d \n",T->priority,T->sub_num,T->Utilization,T->runtime,T->period,T->Heavy);
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