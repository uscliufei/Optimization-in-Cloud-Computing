#include <iostream>
#include <stdlib.h>
#include <fstream>
#include<sstream>
#include <string>
using namespace std;
// float TOUP(int time){
// 	//int t; //from 12 am
// 	if(time <= 8.5) {
// 		return 0.219;
// 	} else if(time <= 12) {
// 		return 0.246;
// 	} else if(time <= 18) {
// 		return 0.270;
// 	} else if(time <= 21.5) {
// 		return 0.246;
// 	} else {
// 		return 0.219;
// 	}
// }
class Task {
	private:
	int time;
	float cpu;
	float memory;
	public:
	Task(){
		time = -1;
		cpu = -1;
		memory = -1;
	}
	// Task(int time, float cpu, float memory) {

	// }
	void settime(int time){
		this->time = time;
	}
	void setcpu(float cpu){
		this->cpu = cpu;
	}
	void setmemory(float memory){
		this->memory = memory;
	}
	int gettime(){
		return time;
	}
	float getcpu(){
		return cpu;
	}
	float getmemory(){
		return memory;
	}
 

};

int main() {
	int number_of_lines = 688564;
	// FILE *fp1;
	// fp1 = fopen("task_eventstime.txt","r");
	// FILE *fp2;
	// fp2 = fopen("task_usageCPU_rate.txt","r");
	// FILE *fp3;
	// fp3 = fopen("task_eventsmemory_request.txt","r");
	ifstream fp1("_task_eventstime.txt");
	ifstream fp2("_task_eventsCPU request.txt");
	//ifstream fp2("test_cpu.txt");

	ifstream fp3("_task_eventsmemory request.txt");

	Task data[100];//TODO:Need to Change
	int flag =0;
	for(int i = 0; i <100; i++){
			int num;
			float cpu;
			float memory;
			string tmp_time, tmp_cpu, tmp_memory;
			//cout<<i<<endl;

			getline(fp1,tmp_time);
			//cout<<tmp_time<<endl;
			if(tmp_time == "") {
				continue;
			}
        	num = stoi(tmp_time);
        	//cout<<num<<endl;

			getline(fp2,tmp_cpu);
			cout<<"tmp_cpu "<< tmp_cpu << endl;
			if(tmp_cpu == "") {
				flag++;
				cout<<flag<<endl;
				continue;
			}
			cout<<tmp_cpu<<endl;
        	cpu = stof(tmp_cpu);

        	getline(fp3,tmp_memory);
        	if(tmp_memory == "") {
				continue;
			}
			cout<<memory<<" memory"<<endl;
        	memory = stof(tmp_memory);

			// // fscanf(fp1, "%d/n", &num);
			// // fscanf(fp2, "%f/n", &cpu);
			// // fscanf(fp3, "%f/n", &memory);
		   cout << "num " << num << "cpu " << cpu << "memory " << memory << endl; 

			data[i].settime(num);
			data[i].setcpu(cpu);
			data[i].setmemory(memory);

			cout<<data[i].gettime()<<" time"<<endl;
			cout<<data[i].getcpu()<<" cpu"<<endl;
			cout<<data[i].getmemory()<<" memory"<<endl;


	}	
	fp1.close();
	fp2.close();
	fp3.close();
}