#include "Task_Q.h"
#include "Processor.h"
#include <stdio.h>
#include<math.h>
#define Utilization_bound 0.70f

task_stack task_set;
task_stack* UQ = &task_set;

processor P1;
processor P2;
processor P3;

task_stack p1_waitQ;
task_stack p2_waitQ;
task_stack p3_waitQ;

processor* processor_set[Num_of_P] = {&P1,&P2,&P3};

void init()
{  
    init_taskset(UQ);
    P1.Wait_Q = &p1_waitQ;
    P2.Wait_Q = &p2_waitQ;
    P3.Wait_Q = &p3_waitQ;
    init_processor(processor_set);
}


int main()
{
    init();

    while(!is_empty(UQ))
    {
        processor* min_P = Pop_processor(processor_set);
        task* T = Pop_task(UQ);

        if (min_P->Utilization >= Utilization_bound)
        {
            printf("ALL PROCESSORS FULLY UTILIZED\n");
            break;
        }

        if(min_P->Utilization + T->Utilization <= Utilization_bound)
        {
            Assign_task(T,min_P);
        }

        else
        {
            //Split Task
            task temp_Body_T; 
            task temp_Tail_T; 
            
            temp_Body_T = *(T);
            temp_Tail_T = *(T);
            
            task* Body_T = &temp_Body_T;
            task* Tail_T = &temp_Tail_T;


            Body_T->Utilization = Utilization_bound - min_P->Utilization;
            floor(Body_T->Utilization);
            Tail_T->Utilization = T->Utilization - Body_T->Utilization;
            floor(Tail_T->Utilization);
            Tail_T->sub_num++;

            Assign_task(Body_T,min_P);
            Push_task(Tail_T,UQ);
        }
    }


    //TEST CASE
    printf("P1 Utilization : %f \n", processor_set[0]->Utilization);
    printf("P2 Utilization : %f \n", processor_set[1]->Utilization);
    printf("P3 Utilization : %f \n", processor_set[2]->Utilization);
    task* temp;
    temp = Pop_task(processor_set[0]->Wait_Q);
    printf("priority: %d  subnum: %d utilization : %f \n",temp->priority, temp->sub_num,temp->Utilization);

    temp = Pop_task(processor_set[1]->Wait_Q);
    printf("priority: %d  subnum: %d utilization : %f \n",temp->priority, temp->sub_num,temp->Utilization);

    temp = Pop_task(processor_set[2]->Wait_Q);
    printf("priority: %d  subnum: %d utilization : %f \n",temp->priority, temp->sub_num,temp->Utilization);
    
    return 0;
}