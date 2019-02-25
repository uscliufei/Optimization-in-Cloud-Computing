#include "main.h"

Server:: Server(){
	this.vm_num = 4;
	this.ready_time = 0;
}

Server:: Server(int vm_num){
	this.vm_num = vm_num;
	this.ready_time = 0;
}

Server:: updateTime(int period){
	this.ready_time += ready_time;
}

