#include "Task_Q.h"
#include "stdio.h"

// task_stack task_set;
// task_stack* UQ = &task_set;

task Task1 = {1,1,6,10};
task Task2 = {2,1,3,10};
task Task3 = {3,1,3,15};
task Task4 = {4,1,4,20};
task Task5 = {5,1,5,25};
task Task6 = {6,1,15,30};

task* temp_set[Q_size] = {&Task1,&Task2,&Task3,&Task4,&Task5,&Task6};



void init_stack(task_stack* task_arr)
{
    task_arr->top = -1;
}

int is_full(task_stack* task_arr)
{
    if(task_arr->top >= (Q_size - 1) ) return 1;
    return 0;
}

int is_empty(task_stack* task_arr)
{
    if(task_arr->top < 0) return 1;
    return 0;
}


task* Pop_task(task_stack* task_arr)
{
    if(is_empty(task_arr))
    {
        printf("UNDER FLOW\n");
        return 0;
    }

    return task_arr->list[task_arr->top--];
}

void Push_task(task* T,task_stack* task_arr)
{
    if(is_full(task_arr))
    {
        printf("OVER FLOW\n");
        return;
    }

    // task_arr->top++;
    task_arr->list[++task_arr->top] = T;
    return;
}

void init_taskset(task_stack* task_arr)
{

    init_stack(task_arr);

    for(int i=0;i<Q_size;i++)
    {
        Push_task(temp_set[i], task_arr);
        task_arr->list[i]->Utilization = ((task_arr->list[i]->runtime) / (task_arr->list[i]->period));
    }
}


// int main()
// {
//     init_taskset(UQ);
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