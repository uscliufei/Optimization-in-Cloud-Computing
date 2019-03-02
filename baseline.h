#ifndef BASELINE_H
#define BASELINE_H
#include <iostream>
#include <queue>
#include <cstdlib>
#include "Cloud_Platform_Model.h"
#include "User_Workload_Model.h"
float TOUP(int time);
float Price_function(Task task,Server server,float time);
float energy_model(Task cur_task,Server server,int time);
bool greedy(Task cur_task,Server *servers,int server_num);
void round_robin(Task cur_task, ServerFarm *serverfarms,int serverfarm_num, int server_num,float time_slot,queue<Task> &task_queue);
#endif