#include "Task_Q.h"
#include "stdio.h"

// task_stack task_set;
// task_stack* UQ = &task_set;

task Task1 = {1,1,6,10};
task Task2 = {2,1,5,10};
task Task3 = {3,1,3,15};
task Task4 = {4,1,4,20};
task Task5 = {5,1,5,25};
task Task6 = {6,1,15,30};

task task_pool[Num_of_P-1];  //Split task 상한 Num_of_Q + Num_of_P -1;
int pool_index = 0;


task* temp_set[Num_of_T] = {&Task1,&Task2,&Task3,&Task4,&Task5,&Task6};


/// *************** For Task stack  *************** ///
void init_task_stack(task_stack* task_stack_ptr)
{
    task_stack_ptr->top = -1; //현재 stack에 들어가 있는 task를 가리킴
}

int is_full(task_stack* task_stack_ptr)
{
    if(task_stack_ptr->top >= (Num_of_T - 1) ) return 1;
    return 0;
}

int is_empty(task_stack* task_stack_ptr)
{
    if(task_stack_ptr->top < 0) return 1;
    return 0;
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

    // task_stack_ptr->top++;
    task_stack_ptr->list[++task_stack_ptr->top] = T;
    return;
}

void init_taskset(task_stack* task_stack_ptr)
{

    init_task_stack(task_stack_ptr);

    for(int i=0;i<Num_of_T;i++)
    {
        Push_task(temp_set[i], task_stack_ptr);
        task_stack_ptr->list[i]->Utilization = ((task_stack_ptr->list[i]->runtime) / (task_stack_ptr->list[i]->period));
    }
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
    printf("Task (%d,%d) : %f ( %f / %f ) \n",T->priority,T->sub_num,T->Utilization,T->runtime,T->period);
    return;
}

// task* Split_task(task* T,float U)
// {

// }


/// *************** For Node  *************** ///


task* new_task()
{

    if(pool_index> Num_of_P)
    {
        printf("NO MORE SPLIT");
        return NULL;
    }

    return &task_pool[pool_index++];
}


/// *************** For Test  *************** ///

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