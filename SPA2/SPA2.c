#include "Task_Q.h"
#include "Processor.h"

float Utilization_bound;

task_stack task_set;
task_stack* UQ = &task_set;

task Task1 = {1,1,6,10};
task Task2 = {2,1,5,10};
task Task3 = {3,1,3,15};
task Task4 = {4,1,4,20};
task Task5 = {5,1,5,25};
task Task6 = {6,1,15,30};
task* temp_set[Num_of_T] = {&Task1,&Task2,&Task3,&Task4,&Task5,&Task6};

processor P1; 
processor P2;
processor P3;
processor* P_temp_set[Num_of_P] = {&P1,&P2,&P3};

task_stack p1_waitQ;
task_stack p2_waitQ;
task_stack p3_waitQ;
task_stack* Wait_Q_set[Num_of_P] = {&p1_waitQ,&p2_waitQ,&p3_waitQ};

processor_stack processor_set;
processor_stack* PQ = &processor_set;

processor_stack Pre_set;
processor_stack* PQ_pre = &Pre_set;


void init()
{  
    Utilization_bound = init_taskset(temp_set);
    init_task_stack(UQ);

    init_processor(P_temp_set,Wait_Q_set);
    // init PQ 
    init_processor_stack(PQ);
    Push_processor(&P3,PQ);
    Push_processor(&P2,PQ);
    Push_processor(&P1,PQ); // init PQ : P1/P2/P3/

    // init_PQ_pre
    init_processor_stack(PQ_pre); // init PQ pre :  NULL/
    
    printf("\n");
}


void Split_task(task* T, float Processor_U)
{
    task* Tail_T = new_task(); 
    float Origin_U = T->Utilization;
    float Origin_R = T->runtime;
    Copy(T,Tail_T);

    T->Utilization = Utilization_bound - Processor_U;
    T->runtime = (T->Utilization) * (T->period); //조정한 Utilization에 따른 Run-time 적용

    Tail_T->Utilization = Origin_U - T->Utilization;
    Tail_T->runtime = Origin_R - T->runtime;
    Tail_T->sub_num++;

    Push_task(Tail_T,UQ);

    return ;
}

bool simple_test(task* T, int num_of_Lower_T ,int num_of_rest_P)
{
    /* RETURN PRE ASSIGN OR NOT */
    float sum=0.0f ,temp;

    for(int i= num_of_Lower_T+1; i < Num_of_T;i++)
    {
        sum+=temp_set[i]->Utilization;
    }

    printf("Sum of lower priority than T%d is %f \n",num_of_Lower_T+1,sum);

    if(sum > num_of_rest_P*Utilization_bound) 
    {
        printf("T%d IS HEVAY BUT AFFORDABLE \n" , num_of_Lower_T+1);
        printf("\n");
        return false;
    }
    
    printf("\n");
    return true;
}



void main()
{

    init();

    /*********** Pre-Assign ************/

    for (int i=0; i<Num_of_T;i++)
    {
        task* T = temp_set[i];

        if(T->Heavy && simple_test(T,i,PQ->top))
        {
            processor* P = Pop_processor(PQ);
            printf("PRE-ASSIGN -> ");
            Assign_task(T,P);
            P->Pre_assigned = true;
            Push_processor(P,PQ_pre);
        }

        else 
        {
            Push_task(T,UQ);
        }
    }


    /***********NORMAL ASSIGN *************/

    printf("---------------------------------------\n");
    while(!is_empty(UQ))
    {
        processor* min_P = get_min_processor(PQ->list,PQ->top);
        task* T = Pop_task(UQ);

        /**SELECT Processor**/
        if (min_P->Utilization >= Utilization_bound)
        {
            printf("NO MORE NORMAL PROCESSOR : ");
            min_P = Pop_processor(PQ_pre);

            //PRE-assign P까지 모두 꽉 찬 경우
            if(min_P->Utilization >= Utilization_bound)
            {
                printf("ALL PROCESSORS FULLY UTILIZED\n");
                break;
            }
        }

        /**ASSIGN Task**/
        if(min_P->Utilization + T->Utilization <= Utilization_bound )
        {
            printf("Normal_assign -> ");
            Assign_task(T,min_P);

            if(min_P->Pre_assigned)
            {
                Push_processor(min_P,PQ_pre);
            }
        }

        else
        {   
            printf("Split -> ");

            Split_task(T,min_P->Utilization);
            Assign_task(T,min_P);
        }
    }

    printf("\n");

    Print_processor(PQ->list[2]);
    Print_processor(PQ->list[1]);
    Print_processor(PQ->list[0]);
    
    return ;
}