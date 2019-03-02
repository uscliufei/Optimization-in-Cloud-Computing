#include "User_Workload_Model.h"
using namespace std;

Task::Task(){
		time = -1;
		cpu_frac = -1;
		memory_frac = -1;
		execution_time = -1;
		vm_type = rand()%4;
		hard_deadline = -1;
	}
Task::~Task(){}

void Task::settime(int time){
		this->time = time;
	}
void Task::setcpu(float cpu){
		this->cpu_frac = cpu;
	}
void Task::setmemory(float memory){
		this->memory_frac = memory;
	}
void Task::setexecution_time(float execution_time){
	this->execution_time = execution_time;
}
void Task::sethard_deadline(float hard_deadline){
	this->hard_deadline = hard_deadline;
}
int Task::gettime(){
		return time;
	}
float Task::getcpu(){
	return cpu_frac;
}
float Task::getmemory(){
	return memory_frac;
}
int Task::getexecution_time()
{
	return execution_time;
}
float Task::gethard_deadline()
{
	return hard_deadline;
}
void Task::print_task()
{
	cout<<"time: "<<time<<" cpu: "<<cpu_frac<<" memory: "<<memory_frac<<" execution_time " << execution_time << endl;
}
int Task::get_vmtype()
{
	return vm_type;
}
