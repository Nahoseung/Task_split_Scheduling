
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
    float Utilization; // (runtime / period )
} task;

task UQ[5]; //Task 구조체의 배열

/*
Task_info
Task i의 정보 현재 상황을 담고있는 구조체

num_of_subtasks: 현재 Split task의 Subtask의 개수 즉, Tail Subtask의 번호와 동일

num_of_complete_tasks: 현재까지 완료된 task의 번호를 의미 
*/

typedef struct Task_info
{
    int num_of_subtasks;
    int num_of_complete_tasks ;
}task_info;

task_info Task_manager[5]; // Task_info 구조체를 관리하는 배열

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
    task WaitQ[10];
} processor;

processor Processor_manager[3]; // Processor 구조체의 배열


int main(){
    return ;
}



