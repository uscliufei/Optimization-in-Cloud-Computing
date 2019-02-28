#include "main.h"

VM:: VM(){
	this->avaiable_time = 0;
}

VM:: ~VM(){};

void VM:: updateTime(int period){
	this->avaiable_time += period;
}



Server:: Server(){
	this->vm_num = 4;
}

Server:: Server(int vm_num){
	v = new VM[vm_num];
	this->vm_num = vm_num;
}

Server:: ~Server(){};

void Server:: configVM(){
	double fractions_cpu[vm_num + 1];
	fractions_cpu[0] = 0;
	for(int i = 1; i < vm_num; i++){
		while(true){
			double r = rand() / double(RAND_MAX);
			if(r >= 0.1 && r <= 0.4){
				fractions_cpu[i] = r;
				break;
			}
		}
	}

	double fractions_memory[vm_num + 1];
	for(int i = 1; i < vm_num; i++){
		while(true){
			double r = rand() / double(RAND_MAX);
			if(r >= 0.1 && r <= 0.4){
				fractions_memory[i] = r;
				break;
			}
		}
	}

	fractions_memory[vm_num] = 1;
	fractions_cpu[vm_num] = 1;
	sort(fractions_memory, fractions_memory + vm_num);
	sort(fractions_cpu, fractions_cpu + vm_num);
	for(int i = 0; i < vm_num; i++){
		v[i].cpu_frac = fractions_cpu[i + 1] - fractions_cpu[i];
		v[i].memory_frac = fractions_memory[i + 1] - fractions_memory[i];
	}
}

ServerFarm:: ServerFarm(){
	this->server_num = 10;
}


ServerFarm:: ServerFarm(int server_num){
	this->server_num = server_num;
	s = new Server[server_num];
}

void ServerFarm::  configServer(int farm_id, int vm_num){ 
	for(int i = 0; i < server_num; i++){
		Server cur_vm(vm_num) ;
		s[i] = cur_vm;
		s[i].farm_id = farm_id;
	}
}

// Job:: Job(int job_id, int task_num){
// 	this->job_id = job_id;
// 	this->task_num = task_num;
// 	t = new Task[task_num];
// }

// void Job:: configJob(){
// 	for(int i = 0; i < task_num; i++){
// 		t[i].job_id = job_id;
// 	}
// }

int main(int argc, char const *argv[]) {
	ServerFarm *test = new ServerFarm(10);
	test->configServer(1, 4);
	test->farm_id = 1;
	// test->server_num = 4;
	cout<< "farmid " << test->farm_id << " servernum " << test->server_num << endl; 
	for(int i = 0; i < test->server_num; i++){
		test->s[i].configVM();
		for(int j = 0; j < test->s[i].vm_num; j++){
			cout << test->s[i].v[j].cpu_frac << "  "  << test->s[i].v[j].memory_frac << endl;
		}
		cout << "===========" << endl;
	}

	return 0;
}

