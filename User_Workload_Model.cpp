#include "User_Workload_Model.h"
using namespace std;

Task::Task(){
		time = -1;
		cpu_frac = -1;
		memory_frac = -1;
		execution_time = -1;
		vm_type = rand()%4;
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
void Task::setexecution_time(int execution_time){
	this->execution_time = execution_time;
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
void Task::print_task()
{
	cout<<"time: "<<time<<" cpu: "<<cpu_frac<<" memory: "<<memory_frac<<" execution_time " << execution_time << endl;
}
int Task::get_vmtype()
{
	return vm_type;
}
