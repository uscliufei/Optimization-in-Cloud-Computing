#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include<algorithm>

using namespace std;

class VM {
public:
 	double cpu_frac;
 	double memory_frac;
 	int avaiable_time;
 	VM();
 	~VM();
 	void updateTime(int);
};

class Server {	
public:
	VM *v;
	int vm_num;
 	int farm_id;
 	// const int cpu_total = 1;
 	// const int memory_total = 1;
 	Server();
 	Server(int vm_num);
 	~Server();
 	void configVM();
};

class ServerFarm {
public:
	Server *s;
	int farm_id;
	int server_num;
 	ServerFarm();
 	ServerFarm(int server_num);
 	~ServerFarm();
 	void configServer(int farm_id, int vm_num);
};


// class Task {
// public:
// 	int job_id;
// 	int start_time;
// 	int exe_period;
// 	int task_type;
//  	float cpu_usage;
//  	float memory_usage;
//  	Task();
//  	Task(int start_time, int job_id, int task_type, float cpu_usage, float memory_usage, int exe_period);
//  	~Task();
// };


// class Job {
// public:
//  	Task *t;
//  	int deadline;
//  	int task_num;
//  	int job_id;
//  	Job();
//  	Job(int job_id, int task_num);
//  	~Job();
//  	void configJob();
// };



#endif