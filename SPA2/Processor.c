#include "Processor.h"
#include "Task_Q.h"
#include <stdio.h>
#include <math.h>
// task_stack task_set;
// task_stack* UQ = &task_set;
// processor P1;
// processor P2;
// processor P3;
// task_stack p1_waitQ;
// task_stack p2_waitQ;
// task_stack p3_waitQ;



processor* Pop_processor(processor* processor_arr[])
{
    int min_i=0;

    for(int i=1; i<Num_of_P;i++)
    {
        if(processor_arr[i]->Utilization < processor_arr[min_i]->Utilization)
        {
            min_i = i;
        }
    }
    return processor_arr[min_i];
}


void init_processor(processor* processor_arr[])
{
    for (int i=0; i<Num_of_P; i++)
    {
        processor_arr[i]->Pnum =i;
        processor_arr[i]->Utilization = 0.0f;
        init_stack(processor_arr[i]->Wait_Q);
    }
}

void Assign_task(task* T, processor* P)
{
    Push_task(T,P->Wait_Q);
    float temp = P->Utilization;
    P->Utilization = P->Utilization + T->Utilization;
    // floor(P->Utilization);
    printf("P%d (%f) : Gonna assign Task(%d,%d) %f  After :  %f \n",(P->Pnum+1),temp,T->priority,T->sub_num,T->Utilization, P->Utilization );
    return;
}
void Print_processor(processor* P)
{
    printf("P%d Utilization : %f  Wait Q -> " ,(P->Pnum+1) ,P->Utilization);
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

