#include "baseline.h"
void round_robin(Task cur_task, ServerFarm *serverfarms,int serverfarm_num, int server_num,float time_slot,queue<Task> &task_queue)
{
    int vm_type = cur_task.get_vmtype();
    int b = 0;

    if(cur_task.gethard_deadline() == -1)
    {
        cur_task.sethard_deadline(cur_task.gettime() + rand()%7200);
        cout<<"allocate harddeadline! " << endl;
    }

     if(cur_task.getexecution_time() < time_slot){
        time_slot = cur_task.getexecution_time();
        cout<<"Gonnona finish!" << endl;
    }

    for(int i = 0;i < serverfarm_num;i++)
    {
        for(int j = 0;j < server_num; j++)
        {
            if(serverfarms[i].s[j].v[vm_type].avaiable_time + time_slot  < cur_task.gethard_deadline()) //SAL
            {
                if(cur_task.getcpu() < serverfarms[i].s[j].v[vm_type].cpu_frac &&  cur_task.getmemory() < serverfarms[i].s[j].v[vm_type].memory_frac)
                {
                    cout << "allocate the task to serverfarms:" << i <<" server: " << j << endl;
                    serverfarms[i].s[j].v[vm_type].avaiable_time = serverfarms[i].s[j].v[vm_type].avaiable_time + time_slot;
                    float left_execution_time = cur_task.getexecution_time() - time_slot;
                    cur_task.setexecution_time(left_execution_time);
                    if (left_execution_time == 0)
                    {
                        cout << "Done with this task !" << endl;

                    }
                    else{
                        cout<<"Put the task back into the quene" << endl;
                        cur_task.settime(cur_task.gettime() + time_slot);
                        task_queue.push(cur_task);
                    }
                    b = 1;
                    break;
                }
                else{
                    cout<<"No CPU or memory" << endl;
                    continue;
                }
            }
            else{
                cout << "this server not avaiable! "<<endl;
                continue;
            }
        }
        if(b == 1)
            {break;}
    }

}