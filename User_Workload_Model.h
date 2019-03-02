#ifndef USER_H
#define USER_H
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

class Task {
    private:
    int time;
    float cpu_frac;
    float memory_frac;
    float execution_time; //sec
    int vm_type;
    float hard_deadline;
    public:
    Task();
    ~Task();
    void settime(int time);
    void setcpu(float cpu);
    void setmemory(float memory);
    void setexecution_time(float execution_time);
    void sethard_deadline(float hard_deadline);
    int gettime();
    float getcpu();
    float getmemory();
    int getexecution_time();
    void print_task();
    int get_vmtype();
    float gethard_deadline();


};

// class Job {
// public:
//      Task *t;
//      int deadline;
//      int task_num;
//      int job_id;
//      Job();
//      Job(int job_id, int task_num);
//      ~Job();
//      void configJob();
// };

#endif