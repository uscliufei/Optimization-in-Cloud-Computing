#include <stdlibb>
#include <iostream>
float energy_model(Task cur_task,Server server,int time){
    float cur_cpu = 0,cur_memory = 0;
    for(int i = 0; i < server.vm_num;i++)
    {
        if(server.vm[i].status == 1)
        {
            cur_cpu += server.vm[i].cpu_frac;
        }
    }
    float utilization_rate = cur_cpu;
    //
    float dynamic_power;
    if(utilization_rate < server.utilization_opt_rate)
    {
        dynamic_power = utilization_rate * server.alaph
    }
    else{
        dynamic_power = utilization_opt_rate * server.alaph + (utilization_rate - utilization_opt_rate)*(utilization_rate - utilization_opt_rate)*server.beta
    }

}



bool greedy(Task cur_task,Server *servers,int server_num)
{
    float tmp,min_cost = -1;
    int server_id;
    int vm_type = cur_task.vm_type;
    if( cur_task.excution_time > 3600)
        return false;
    for(int i = 0; i < server_num; i++){
        if(cur_task.cpu_frac > servers[i].vm[vm_type].cpu_frac &&  cur_task.memory_frac > servers[i].vm[vm_type].memory_frac)
        {
            continue;
        }
        if(min_cost == -1)
        {
            min_cost = Price_function(cur_task,servers[i],cur_task.start_time);
        }
        else{
              tmp  = Price_function(cur_task,servers[i]);
              if(tmp < min_cost)
              {
                min_cost = tmp;
                server_id = i
            }
        }
    }
    server[i].vm[vm_type].status = 1;
    return true;


}