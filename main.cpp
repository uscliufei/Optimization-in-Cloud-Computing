#include "main.h"
#include <math.h>
#include<bits/stdc++.h> 

ServerFarm:: ServerFarm(){
	this.server_num = 10;
}


ServerFarm:: ServerFarm(int server_num){
	this.server_num = server_num;
}

ServerFarm:: void configServer(int farm_id, int vm_num){ 
	for(int i = 0; i < server_num; i++){
		s[i] = new Server(vm_num);
		s[i].farm_id = farm_id;
	}
}

Server:: Server(){
	this.vm_num = 4;
}

Server:: Server(int vm_num){
	v = new VM[vm_num];
	this.vm_num = vm_num;
}

void Server:: configVM(){
	float fractions_cpu[vm_num + 1];
	fractions_cpu[0] = 0;
	for(int i = 1; i < vm_num; i++){
		fractions_cpu[i] =  rand() / double(RAND_MAX);
	}

	float fractions_memory[vm_num];
	for(int i = 1; i < vm_num; i++){
		fractions_memory[i] =  rand() / double(RAND_MAX);
	}

	fractions_memory[vm_num] = 1;
	fractions_cpu[vm_num] = 1;
	sort(f, f + vm_num);
	for(int i = 0; i < vm_num; i++){
		v[i].cpu_frac = fractions_cpu[i + 1] - fractions_cpu[i];
		v[i].memory_frac = fractions_memory[i + 1] - fractions_memory[i];
	}
}

void VM:: updateTime(int period){
	this.avaiable_time += period;
}

Job:: Job(int job_id, int task_num){
	this.job_id = job_id;
	this.task_num = task_num;
	t = new Task[task_num];
}

void Job:: configJob(){
	for(int i = 0; i < task_num; i++){
		t[i].job_id = job_id;
	}
}


