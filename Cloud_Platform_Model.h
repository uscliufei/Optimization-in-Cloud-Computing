#ifndef CLOUD_H
#define CLOUD_H

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;

class VM {
public:
 	double cpu_frac;
 	double memory_frac;
 	int avaiable_time;
    int status;
 	VM();
 	~VM();
 	void updateTime(int period);
};

class Server {	
public:
	VM *v;
	int vm_num;
 	int farm_id;
    double alaph;
    int beta;
    double utilization_opt_rate;
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







#endif