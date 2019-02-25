#include "main.h"


ServerFarm:: ServerFarm(int farm_id){
	this.server_num = 10;
	this.s = new Server[10];
}


ServerFarm:: ServerFarm(int server_num){
	this.server_num = server_num;
	this.s = new Server[server_num];
}

ServerFarm:: void configServer(int farm_id, int vm_num){
	for(int i = 0; i < server_num; i++){
		s[i].farm_id = farm_id;
		s[i].vm_num = vm_num;
		s[i].ready_time = 0;
	}
}

Server:: Server(){
	this.vm_num = 4;
	this.ready_time = 0;
}


Server:: updateTime(int period){
	this.ready_time += ready_time;
}

