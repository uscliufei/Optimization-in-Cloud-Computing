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
	int vm_num;
 	int ready_time;
 	int farm_id;
 	const int cpu_total = 1;
 	const int memory_total = 1;
 	Server();
 	~Server();
 	void updateTime(int);
};

class VM
{
public:
 	int vm_type;
 	int cpu_frac;
 	int memory_frac;
 	VM();
 	~VM();
};

class Job
{
public:
 	Task *t;
 	int task_num;
 	Job();
 	~Job();
};

class Task
{
public:
 	float core;
 	float memory;
 	Task();
 	~Task();
 
};