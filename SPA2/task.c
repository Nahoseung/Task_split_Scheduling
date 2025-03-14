
# define Utilization_Bound 70.0;

/*
Task
Task i의 정보를 담고 있는 구조체
Task i는 (C,T)로 구성
i가 증가할 수록 우선 순위는 감소
Split task와 Non-split task, Body task tail task를 서로 구분하지 않음
*/

typedef struct Task 
{
    int priority; 
    int sub_num;
    int runtime;
    int period;
    float Utilization; 
} task;


task Task1 = {1,1,5,10,0.5f};
task Task2 = {2,1,5,10,0.5f};
task Task3 = {3,1,3,15,0.2f};
task Task4 = {4,1,4,20,0.2f};
task Task5 = {5,1,5,25,0.2f};

typedef struct UQ
{
    task* list[5];
    int rear,tail;
}UQ;

UQ* task_arr;



/*
Task_info
Task i의 정보 현재 상황을 담고있는 구조체

num_of_subtasks: 현재 Split task의 Subtask의 개수 즉, Tail Subtask의 번호와 동일

next_run_tasks: 다음 수행해야할 (sub)task의 번호
*/

typedef struct Task_info
{
    int num_of_subtasks;
    int next_run_tasks; 
}task_info;

task_info Task_manager[5]; 
Task_manager = {
    {1,1},
    {1,1},
    {1,1},
    {1,1},
    {1,1}
};

/*
Processor
Processor i의 정보를 담고 있는 구조체

Pnum: 현재 Processor의 번호

Utilization: 현재 Processor에 할당된 Task들의 Utilization 총 합

WaitQ: 각 Processor에 할당된 Task들의 배열
*/

typedef struct Processor
{
    int Pnum;
    int Utilization;
    task WaitQ[5];
} processor;

processor Processor_manager[3]; 

Processor_manager = {
    {1,0},
    {2,0},
    {3,0}
};


void Push_task(task T);
task Pop_task();

void Push_processor(processor P);
processor Pop_processor(); //Utilization 최소값

void Assign_task(processor P, task T);

/////////////////////////////////

void Push_task(task T)
{
    
}


int main(){
    task_arr-> list[0] = &Task1;
    return ;
}



