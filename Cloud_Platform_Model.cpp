#include "Cloud_Platform_Model.h"

VM:: VM(){
	this->avaiable_time = 0;
	status = 0;
}

VM:: ~VM(){
};

void VM:: updateTime(int period){
	this->avaiable_time += period;
}



Server:: Server(){
	this->vm_num = 4;
	while(true){
			double r = rand() / double(RAND_MAX);
			if(r >= 0.4 && r <= 0.7){
				utilization_opt_rate = r;
				break;
			}
		}

	while(true){
			double r = rand() / double(RAND_MAX);
			if(r >= 0.3 && r <= 0.5){
				alaph = r;
				//cout<<"alaph" << alaph << endl;
				break;
			}
		}
			
	int r = rand()%10 + 5;
	beta = r;
	//cout<<"beta "<<beta << endl;


}

Server:: Server(int vm_num){
	v = new VM[vm_num];
	this->vm_num = vm_num;
	while(true){
			double r = rand() / double(RAND_MAX);
			if(r >= 0.3 && r <= 0.5){
				alaph = r;
				//cout<<"alaph" << alaph << endl;
				break;
			}
		}
			
	int r = rand()%10 + 5;
	beta = r;

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
	s = new Server[10];
}

ServerFarm:: ~ServerFarm(){}

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




