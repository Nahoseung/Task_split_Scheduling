#include "Task_Q.h"
#include "Processor.h"
#include <stdio.h>


float Utilization_bound ;
task_stack task_set;
task_stack* UQ = &task_set;

processor P1;
processor P2;
processor P3;

task_stack p1_waitQ;
task_stack p2_waitQ;
task_stack p3_waitQ;

processor* processor_set[Num_of_P] = {&P1,&P2,&P3};

// void get_Utilization()
// {
//     float n = Num_of_T;
//     Utilization_bound =  n * (pow(2.0, 1.0 / n) - 1);
//     printf("For %d tasks Utilization Bound is :  %f \n",Num_of_T, Utilization_bound);
//     return;
// }

void init()
{  
    Utilization_bound = init_taskset(UQ);
    P1.Wait_Q = &p1_waitQ;
    P2.Wait_Q = &p2_waitQ;
    P3.Wait_Q = &p3_waitQ;
    init_processor(processor_set);
}

void Split_task(task* T, float Processor_U)
{
    task* Tail_T = new_task(); 
    float Origin_U = T->Utilization;
    float Origin_R = T->runtime;
    Copy(T,Tail_T);

    T->Utilization = Utilization_bound - Processor_U;
    T->runtime = (T->Utilization) * (T->period); //조정한 Utilization에 따른 Run-time 적용
    // floor(Body_T->Utilization);

    Tail_T->Utilization = Origin_U - T->Utilization;
    Tail_T->runtime = Origin_R - T->runtime;
    Tail_T->sub_num++;
    // floor(Tail_T->Utilization);


    /*
    Utilization 조정에 따른  Runtime 조정하는 로직 필요.
    */

    Push_task(Tail_T,UQ);

    return ;
}

int simple_test()
{
    
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
            printf("ALL PROCESSORS FULLY UTILIZED CANT ASSIGN TASK : ");
            Print_task(T);
            break;
        }

        if(min_P->Utilization + T->Utilization <= Utilization_bound )
        {
            printf("Normal_assign -> ");
            Assign_task(T,min_P);
        }

        else
        {   
            printf("Split -> ");

            Split_task(T,min_P->Utilization);
            Assign_task(T,min_P);
        }
    }


    //TEST CASE
    Print_processor(processor_set[0]);
    Print_processor(processor_set[1]);
    Print_processor(processor_set[2]);

    
    //// 
    task* temp;

    temp = Pop_task(processor_set[0]->Wait_Q);
    Print_task(temp);
    temp = Pop_task(processor_set[1]->Wait_Q);
    Print_task(temp);
    temp = Pop_task(processor_set[2]->Wait_Q);
    Print_task(temp);

    
    return 0;
}