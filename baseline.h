#ifndef BASELINE_H
#define BASELINE_H
#include <iostream>
#include "Cloud_Platform_Model.h"
#include "User_Workload_Model.h"
float TOUP(int time);
float Price_function(Task task,Server server,float time);
float energy_model(Task cur_task,Server server,int time);
bool greedy(Task cur_task,Server *servers,int server_num);
#endif