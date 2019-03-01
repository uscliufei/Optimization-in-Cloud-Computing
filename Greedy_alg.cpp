#include "baseline.h"
using namespace std;
float TOUP(int time){
 //int t; //from 12 am
 if(time <= 8.5) {
     return 0.219;
 } else if(time <= 12) {
     return 0.246;
 } else if(time <= 18) {
     return 0.270;
 } else if(time <= 21.5) {
     return 0.246;
 } else {
     return 0.219;
 }
}

float Price_function(Task task,Server server,float time)
{
    return 0;

}

float energy_model(Task cur_task,Server server,int time){

    //should include the static power

    float cur_cpu = 0,cur_memory = 0;
    for(int i = 0; i < server.vm_num;i++)
    {
        if(server.v[i].status == 1)
        {
            cur_cpu += server.v[i].cpu_frac;
        }
    }
    float utilization_rate = cur_cpu;
    cout<<"utilization_rate "<<utilization_rate << endl;
    //
    float dynamic_power;
    if(utilization_rate < server.utilization_opt_rate)
    {
        dynamic_power = utilization_rate * server.alaph;
    }
    else{
        cout<<"alaph" << server.alaph << endl;
        cout<<"beta" << server.beta << endl;
        dynamic_power = server.utilization_opt_rate * server.alaph + (utilization_rate - server.utilization_opt_rate)*(utilization_rate - server.utilization_opt_rate)*server.beta;
        cout<<"dynamic_power is " << dynamic_power << endl;
    }
    return dynamic_power;

}



bool greedy(Task cur_task,Server *servers,int server_num)
{
    float tmp,min_cost = -1;
    int server_id = -1;
    int vm_type = cur_task.get_vmtype();
    int hard_deadline;
    hard_deadline = rand()%7200;
    cout<<"-------------------------------"<<endl;
    cout<<"cur time is " << cur_task.gettime() << endl;
    cout<<"hard_deadline: " << hard_deadline << endl;
    cout<<"execution time "<<cur_task.getexecution_time()<<endl;
    if( cur_task.getexecution_time() > hard_deadline)
    {
        cout<<"reject Task!" << endl;
        return false;
    }
    for(int i = 0; i < server_num; i++){
        //
        /*if(cur_task.gettime() > servers[i].v[vm_type].avaiable_time)
        {
            servers[i].v[vm_type].status = 0;
        }
        else{
            cout<<"current server busy!" << endl;
            continue;
        }*/
        //
        // cout<<"task cpu required " << cur_task.getcpu() << endl;
        // cout<<"servers cpu " << servers[i].v[vm_type].cpu_frac << endl;
        // cout<<"task mem required " << cur_task.getmemory() << endl;
        // cout<<"servers mem " << servers[i].v[vm_type].memory_frac << endl;
        if(cur_task.getcpu() > servers[i].v[vm_type].cpu_frac &&  cur_task.getmemory() > servers[i].v[vm_type].memory_frac)
        {
            cout<<"No CPU or memory" << endl;
            continue;
        }
        cout<<"cpu mem pass" << endl;
        if(min_cost == -1)
        {
            //min_cost = Price_function(cur_task,servers[i],cur_task.gettime());
            min_cost = energy_model(cur_task,servers[i],cur_task.gettime());
            cout << "min_cost "<<min_cost << endl;
            server_id = i;
        }
        else{
              //tmp  = Price_function(cur_task,servers[i],cur_task.gettime());
            tmp = energy_model(cur_task,servers[i],cur_task.gettime());
            cout << "min_cost "<<min_cost << endl;
              if(tmp < min_cost)
              {
                min_cost = tmp;
                server_id = i;
            }
        }
        //there is a case that no server is free so the task would be dropped.
    }
    if(server_id != -1)
    {
        cout<<"id is " << server_id << endl;
        servers[server_id].v[vm_type].status = 1;
        servers[server_id].v[vm_type].avaiable_time = cur_task.gettime() + cur_task.getexecution_time();
    }
    else{
        cout<<"all the server are busy!" << endl;
    }
    cout<<"-------------------------------"<<endl;
    return true;
}