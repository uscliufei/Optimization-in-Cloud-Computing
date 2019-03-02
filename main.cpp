#include "Cloud_Platform_Model.h"
#include "User_Workload_Model.h"
#include "baseline.h"
int main() {

    //clound model
    cout<<"start clound model" << endl;

    ServerFarm serverfarm[10];
    for(int i = 0;i < 10;i++)
    {
        serverfarm[i].configServer(i, 4);
        for(int j = 0; j < serverfarm[i].server_num; j++ )
        {
            serverfarm[i].s[j].configVM();
        }
            
    }

    //task model
    cout<<"start task model " << endl;
    int number_of_lines = 688564;
    ifstream fp1("task_events_time.txt");
    ifstream fp2("task_events_CPU request.txt");
    ifstream fp3("task_events_memory request.txt");
    ifstream fp4("execution_time.txt");

    Task data[300];//TODO:Need to Change
    int flag =0;
    for(int i = 0; i <300; i++){
            int start_time;
            float cpu;
            float memory;
            float execution_time;
            string tmp_time, tmp_cpu, tmp_memory,tmp_execution_time;

            getline(fp1,tmp_time);
            if(tmp_time == "") {
                continue;
            }
            start_time = stoi(tmp_time);

            getline(fp2,tmp_cpu);
            if(tmp_cpu == "") {
                continue;
            }
            cpu = stof(tmp_cpu);

            getline(fp3,tmp_memory);
            if(tmp_memory == "") {
                continue;
            }
            memory = stof(tmp_memory);

            getline(fp4,tmp_execution_time);
            if(tmp_execution_time == "") {
                continue;
            }
            execution_time = stof(tmp_execution_time);

            data[i].settime(start_time);
            data[i].setcpu(cpu);
            data[i].setmemory(memory);
            data[i].setexecution_time(execution_time);

    }
    fp1.close();
    fp2.close();
    fp3.close();
    fp4.close();
    // for(int i = 100;i < 130;i++)
    // {
    //     if (data[i].gettime() == -1)
    //     {
    //         cout<<"not enough info! skip!" << endl;
    //         continue;
    //     } 
    //     greedy(data[i],serverfarm[0].s,10);
    // }

    queue<Task> task_queue;
    Task cur_task;
    for(int i = 0; i< 300; i++)
    {
        if(task_queue.empty())
        {
            if (data[i].gettime() == -1)
              {
                cout<<"not enough info! skip!" << endl;
                continue;
            }
            else{
                cur_task = data[i];
                
            }     
        }
        else{
                Task q1 = task_queue.front();
                if(q1.gettime() < data[i].gettime())
                {
                    cur_task = q1;
                    task_queue.pop();
                    i--;
                                    }
                else{
                    if (data[i].gettime() == -1)
                    {
                        cout<<"not enough info! skip!" << endl;
                        continue;
                    }
                    else{
                        cur_task = data[i];
                    }
                }
        }
        cout<<"------------"<<endl;
        round_robin(cur_task,serverfarm,10,10,100,task_queue);
    }
    cout<<"--------------"<<endl;
    while(!task_queue.empty())
    {
        cur_task = task_queue.front();
        round_robin(cur_task,serverfarm,10,10,100,task_queue);
        cout<<"task_queue.size(): "<<task_queue.size()<<endl;
        cout<<"pop the task " << endl;
        task_queue.pop();
        cout<<"task_queue.size(): "<<task_queue.size()<<endl;
    }


}
