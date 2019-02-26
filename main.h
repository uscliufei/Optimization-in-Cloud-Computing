#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

class ServerFarm
{
public:
	Server *s;
	int farm_id;
	int server_num;
 	ServerFarm();
 	ServerFarm(int server_num);
 	~ServerFarm();
 	void configServer(int farm_id);
};

class Server
{	
public:
	VM *v;
	int vm_num;
 	int farm_id;
 	const int cpu_total = 1;
 	const int memory_total = 1;
 	Server();
 	Server(int vm_num);
 	~Server();
 	
};

class VM
{
public:
 	int cpu_frac;
 	int memory_frac;
 	int ready_time = 0;
 	VM();
 	~VM();
 	void updateTime(int);
};

class Job
{
public:
 	Task *t;
 	int deadline;
 	int task_num;
 	int job_id;
 	Job();
 	Job(int job_id, int task_num);
 	~Job();
 	void configJob();
};

class Task
{
public:
	int job_id;
	int start_time;
	int exe_period;
	int task_type;
 	float cpu_usage;
 	float memory_usage;
 	Task(int start_time, int job_id, int task_type, float cpu_usage, float memory_usage);
 	~Task();
};