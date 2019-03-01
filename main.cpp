#include "Cloud_Platform_Model.h"
#include "User_Workload_Model.h"
#include "baseline.h"
int main() {

    //clound model
    cout<<"start clound model" << endl;
    /*ServerFarm *test = new ServerFarm(10);
    cout<<"-------------"<<endl;
    test->configServer(1, 4);
    test->farm_id = 1;
    cout<< "farmid " << test->farm_id << " servernum " << test->server_num << endl; 
    for(int i = 0; i < test->server_num; i++){
        test->s[i].configVM();
        for(int j = 0; j < test->s[i].vm_num; j++){
            cout << test->s[i].v[j].cpu_frac << "  "  << test->s[i].v[j].memory_frac << endl;
        }
        cout << "===========" << endl;
    }*/

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
    for(int i = 100;i < 130;i++)
    {
        if (data[i].gettime() == -1)
        {
            cout<<"not enough info! skip!" << endl;
            continue;
        } 
        greedy(data[i],serverfarm[0].s,10);
    }

}
