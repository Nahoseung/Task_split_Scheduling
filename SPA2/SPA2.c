#include "Task_Q.h"
#include "Processor.h"

float Utilization_bound;

task_stack task_set;
task_stack* UQ = &task_set;

task Task1 = {1,1,3,10};
task Task2 = {2,1,15,20};
task Task3 = {3,1,2,20};
task Task4 = {4,1,2,20};
// task Task5 = {5,1,4,40};
// task Task6 = {6,1,25,40};
// task Task7 = {7,1,4,40};
// task Task8 = {8,1,4,40};

task* temp_set[Num_of_T] = {&Task1,&Task2,&Task3,&Task4};

task* task_manager[Num_of_T+1];

// task Task1 = {1,1,3.0f,4.0f};
// task Task2 = {2,1,4.25f,10.0f};
// task Task3 = {3,1,4.25f,10.0f};

// task* temp_set[Num_of_T] = {&Task1,&Task2,&Task3};

processor P1; 
processor P2;
// processor P3;
processor* P_set[Num_of_P] = {&P1,&P2};

task_stack p1_waitQ;
task_stack p2_waitQ;
task_stack p3_waitQ;
task_stack* Wait_Q_set[Num_of_P] = {&p1_waitQ,&p2_waitQ};

processor_stack P_stack;
processor_stack* PQ = &P_stack;

processor_stack Pre_stack;
processor_stack* PQ_pre = &Pre_stack;


void init()
{  
    Utilization_bound = init_taskset(temp_set);
    init_task_stack(UQ);

    init_task_info(task_manager);

    init_processor(P_set,Wait_Q_set);

    // init PQ 
    init_processor_stack(PQ);
    // Push_processor(&P3,PQ);
    Push_processor(&P2,PQ);
    Push_processor(&P1,PQ); // init PQ : P1/P2/P3/

    // init_PQ_pre
    init_processor_stack(PQ_pre); // init PQ pre :  NULL/
}


void Split_task(task* T, float Processor_U, int P_num)
{
    task* Tail_T = new_task(); 
    float Origin_U = T->Utilization;
    float Origin_R = T->runtime;
    Copy(T,Tail_T);

    T->Utilization = Utilization_bound - Processor_U;
    T->runtime = (T->Utilization) * (T->period); //조정한 Utilization에 따른 run-time 적용

    Tail_T->Utilization = Origin_U - T->Utilization;
    Tail_T->runtime = Origin_R - T->runtime;
    Tail_T->synthetic_deadline = T->synthetic_deadline - T->runtime;
    Tail_T->sub_num++;

    // task_manager[Tail_T->priority].processor_num = P_num;
    task_manager[Tail_T->priority]= Tail_T;

    Push_task(Tail_T,UQ);

    return ;
}


float Sum_of_H_priority(int P_num, int tail_priority)
{
    task_stack* P = P_set[P_num -1]->Wait_Q;
    int temp_i = P->top+1;
    float sum =0.0f;

    while(temp_i >=0)
    {
        if( P->list[temp_i]->priority < tail_priority) sum+= P->list[temp_i]->Utilization;
        temp_i --;
    }
    return sum;
}


bool Tail_Schedulability()
{
    bool flag = true;
    for(int i=1; i< Num_of_T+1 ; i++)
    {
        if(task_manager[i])
        {
            task* T = task_manager[i];
            float Synthetic_U = T->runtime / T->synthetic_deadline ;
            float H_sum = Sum_of_H_priority(T->Assigned_P,T->priority);
            float temp = (H_sum*T->period) / T->synthetic_deadline + Synthetic_U;

            printf("(%f * %f) / %f + %f = %f \n", H_sum,T->period,T->synthetic_deadline,Synthetic_U,temp);

            if( temp > Utilization_bound)
            {
                printf("IM Tail task(%d,%d) IM in Processor %d  and Im Not Schedulable. \n",T->priority,T->sub_num,T->Assigned_P);
                flag = false;
            }
            
        }
    }
    return flag;
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
        return false;
    }
    
    return true;
}

/******************* SPA2 Algorithm ***********************/

void main()
{

    init();
    printf("-----------------------------------------------------------\n");
    /*********** PRE-ASSIGN ************/

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

    while(!is_empty(UQ))
    {
        processor* min_P = get_min_processor(PQ->list,PQ->top);
        task* T = Pop_task(UQ);

        /**SELECT Processor**/

        if (min_P->Utilization >= Utilization_bound)
        {
            printf("NO MORE NORMAL PROCESSOR : ");
            min_P = Pop_processor(PQ_pre);

            //PRE-assigned P까지 모두 꽉 찬 경우
            if(min_P->Utilization >= Utilization_bound)
            {
                printf("ALL PROCESSORS FULLY UTILIZED \n");
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
            Split_task(T,min_P->Utilization,min_P->Pnum);
            Assign_task(T,min_P);
        }
    }

    printf("-----------------------------------------------------------\n");

    Print_processor(P_set[0]); // Processor 1 waitQ ->
    Print_processor(P_set[1]); // Processor 2 waitQ ->
    // Print_processor(P_set[2]); // Processor 3 waitQ ->


    task* temp = Pop_task(P_set[0]->Wait_Q);
    Print_task(temp);
    temp = Pop_task(P_set[1]->Wait_Q);
    Print_task(temp);

    // temp = Pop_task(P_set[2]->Wait_Q);
    // Print_task(temp);

    if(Tail_Schedulability()) printf("ALL TAIL TASKS SCHEDULABLE\n");
    
    return;
}