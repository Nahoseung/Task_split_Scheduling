#include "Processor.h"
#include "Task_Q.h"

/******************* Processor_stack ***********************/

void init_processor_stack(processor_stack* processor_stack_ptr)
{
    processor_stack_ptr->top = -1;
}

bool P_is_full(processor_stack* processor_stack_ptr)
{
    if(processor_stack_ptr->top >= (Num_of_P -1)) return true;
    return false;
}

bool P_is_empty(processor_stack* processor_stack_ptr)
{
    if(processor_stack_ptr->top < 0) return true;
    return false;
}

void Push_processor(processor* P, processor_stack* processor_stack_ptr)
{
    if(P_is_full(processor_stack_ptr))
    {
        printf("PROCESSOR STACK OVERFLOW");
        return;
    }

    processor_stack_ptr->list[++processor_stack_ptr->top] = P;
    return;
}

processor* Pop_processor(processor_stack* processor_stack_ptr)
{
    if (P_is_empty(processor_stack_ptr))
    {
        printf("PROCESSOR STACK UNDER FLOW\n");
        return NULL;
    }
    return processor_stack_ptr->list[processor_stack_ptr->top--];
}


/******************* Processor Util ***********************/

void init_processor(processor* P_set[], task_stack* Wait_Q_set[])
{
    for(int i=0; i<Num_of_P;i++)
    {
        P_set[i]->Pnum = i+1;
        P_set[i]->Utilization = 0.0f;
        P_set[i]->Pre_assigned = false;
        P_set[i]->Wait_Q = Wait_Q_set[i];
        init_task_stack(P_set[i]->Wait_Q);
    }
}

processor* get_min_processor(processor* processor_set[],int len)
{
    int min_i=len;
    for(int i=len; i >=0 ; i--)
    {
        if(processor_set[i]->Utilization < processor_set[min_i]->Utilization)
        {
            min_i = i;
        }
    }
    return processor_set[min_i];
}

void Assign_task(task* T, processor* P)
{
    Push_task(T,P->Wait_Q);
    T->Assigned_P = P->Pnum;
    float temp = P->Utilization;
    P->Utilization = P->Utilization + T->Utilization;
    printf("P%d (%f) : Gonna assign Task(%d,%d) %f  After :  %f \n",(P->Pnum),temp,T->priority,T->sub_num,T->Utilization, P->Utilization);
    return;
}

void Print_processor(processor* P)
{
    printf("P%d Utilization : %f  Wait Q -> " ,(P->Pnum) ,P->Utilization);
    task* temp; int temp_i = P->Wait_Q->top;
    while( temp_i >= 0 )
    {
        temp = P->Wait_Q->list[temp_i];
        printf("Task (%d,%d) : %f  / ",temp->priority,temp->sub_num,temp->Utilization);
        temp_i--;
    }
    printf("\n");
    return;
}

/// *************** Test  *************** ///

// int main()
// {
//     //task stack 포인터 초기화
//     P1.Wait_Q = &p1_waitQ;
//     P2.Wait_Q = &p2_waitQ;
//     P3.Wait_Q = &p3_waitQ;

//     printf("Now started \n");
//     init_taskset(UQ); printf("UQ task set initied \n");
    
//     init_processor(processor_set); printf("Processor initied \n");

//     task* temp = Pop_task(UQ); printf("first Popped Task in UQ \n");
//     Assign_task(temp, processor_set[0]);
//     temp = Pop_task(UQ); printf("second Popped Task in UQ \n");
//     Assign_task(temp, processor_set[1]);
//     temp = Pop_task(UQ); printf("third Popped Task in UQ \n");

//     Assign_task(temp, processor_set[1]);
//     printf("%f\n", processor_set[0]->Utilization);
//     printf("%f\n", processor_set[1]->Utilization);
//     processor* tempP = Pop_processor(processor_set);
//     printf("%d \n", tempP->Pnum);
// }

