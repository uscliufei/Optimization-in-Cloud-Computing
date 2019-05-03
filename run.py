import env as e
import read_data
import math
from DQN import DeepQNetwork
import numpy as np
import price_model as p
import total_cost

def read_task(i , df_task_usage):
    input_time = (df_task_usage['start time'].loc[i]) / float(1000000 * 3600)
    execution_time = df_task_usage['execution_time'].loc[i]
    CPU_rate = df_task_usage['CPU rate'].loc[i]
    memory_usage = df_task_usage['canonical memory usage'].loc[i]
    job_ID = df_task_usage['job ID'].loc[i]
    task_index = df_task_usage['task index'].loc[i]
    curr_task = e.Task(input_time, CPU_rate, memory_usage, task_index, job_ID)
    return curr_task

def get_observation_1(curr_task, env):
    observation_1 = [curr_task.input_time, curr_task.request_cpu, curr_task.request_memory, curr_task.vm_type]
    # print(len(env.serverfarms))
    # print(len(env.serverfarms[0].servers))
    for svfm in env.serverfarms:
        for sv in svfm.servers:
            observation_1.append(sv.vms[curr_task.vm_type].cpu - sv.vms[curr_task.vm_type].using_cpu)
            observation_1.append(sv.vms[curr_task.vm_type].memory - sv.vms[curr_task.vm_type].using_memory)
    observation_1 = np.array(observation_1)
    # print("observation_1 " + str(observation_1.shape))
    return observation_1


def get_observation_2(curr_task, curr_server_farm):
    observation_2 = [curr_task.input_time, curr_task.request_cpu, curr_task.request_memory, curr_task.vm_type]
    for sv in curr_server_farm.servers:
        observation_2.append(sv.vms[curr_task.vm_type].cpu - sv.vms[curr_task.vm_type].using_cpu)
        observation_2.append(sv.vms[curr_task.vm_type].memory - sv.vms[curr_task.vm_type].using_memory)
    observation_2 = np.array(observation_2)
    return observation_2


if __name__ == "__main__":
    n_serverfarms = 20
    n_servers = 15
    n_vms = 5
    env = e.cloud_env(n_serverfarms, n_servers, n_vms)

    df_task_usage = read_data.read_data()
    job_queue = {}

    RL_farm = DeepQNetwork(n_serverfarms * 24, n_serverfarms * n_servers * 2 + 4, '_farm',
              learning_rate = 0.01,
              reward_decay = 0.9,
              e_greedy = 0.9,
              replace_target_iter = 200,
              memory_size = 2000,
              # output_graph=True
              )

    RL_server = []
    for i in range(n_serverfarms):
        dqn = DeepQNetwork(n_servers, n_servers * 2 + 4, '_server_' + str(i), 
              learning_rate = 0.01,
              reward_decay = 0.9,
              e_greedy = 0.9,
              replace_target_iter = 200,
              memory_size = 2000,
              # output_graph=True
              )
        RL_server.append(dqn)

    # RL_server = [ DeepQNetwork(n_servers, n_servers + 3,
    #           learning_rate = 0.01,
    #           reward_decay = 0.9,
    #           e_greedy = 0.9,
    #           replace_target_iter = 200,
    #           memory_size = 2000,
    #           # output_graph=True
    #           ) for _ in range(n_serverfarms) ]

    RL_server_n = [0 for _ in range(n_serverfarms)]
    last_input_time = 0

    #df_task_usage.shape[0]
    for it in range(250):
        for i in range(1000):
            #read data
            curr_task = read_task(i,df_task_usage)
            env.update_env(last_input_time,curr_task.input_time)


            # if str(job_ID) not in jobs:
            #     curr_job = env.Job(job_ID)
            #     jobs[str(job_ID)] = cur_job
                
            #need a hashmap tp match the id to the job
            #curr_job.tasks.append(curr_task)
            observation_1_new = get_observation_1(curr_task, env)

            #stage_1
            action1 = RL_farm.choose_action(observation_1_new)
            farm_id, waiting_time = env.step_farm(action1)
            curr_server_farm = env.serverfarms[farm_id]

            #stage_2
            observation_2_new = get_observation_2(curr_task,curr_server_farm)
            action2 = RL_server[farm_id].choose_action(observation_2_new)
            server_id = int(action2)
            curr_server = curr_server_farm.servers[server_id]

            #check hard_deadline & cpu,memory
            curr_task.start_time = curr_task.input_time + waiting_time
            curr_task.end_time =  curr_task.start_time +  curr_task.execution_time

            print("----------------------")
            print("start_time : " + str(curr_task.start_time))
            print("execution_time : " + str(curr_task.execution_time))
            print("deadline :" + str(curr_task.deadline))
            print("cpu :" + str(curr_task.request_cpu) + " memory: " + str(curr_task.request_memory))


            if curr_task.end_time > curr_task.deadline:
                drop = True
            else:
                if not env.check_server(curr_task.start_time, curr_server, curr_task):
                    drop, server_id = env.check_server_farm(curr_task.start_time, curr_server_farm, curr_task)
                    curr_server = curr_server_farm.servers[server_id]
                    action2 = server_id
                else:
                    drop = False

            
            if drop:
                reward_stage1_new = -1
                reward_stage2_new = -1
            #
            else:
                curr_server.waiting_tasks.append(curr_task)
                # power_next = curr_server.power(curr_task.start_time)
                # power_prev = curr_server.power(curr_server.prev_time)
                # diff1 = abs(p.Price_model(curr_task.start_time, power_next - power_prev))

                price_next_server = curr_server.cal_total_price(curr_task.input_time, curr_task.start_time )
                price_prev_server = curr_server.cal_total_price(curr_task.input_time, curr_server.prev_time )
                diff1 = abs(price_next_server - price_prev_server)

                if diff1 < 0.5:
                    reward_stage2_new = 25
                else:
                    reward_stage2_new = math.exp(1/diff1) * 5

                # power_next = curr_server_farm.power(curr_task.start_time)
                # power_prev = curr_server_farm.power(curr_server_farm.prev_time)
                # diff2 = abs(p.Price_model(curr_task.start_time, power_next - power_prev))

                price_next_farm = curr_server_farm.cal_total_price(curr_task.input_time, curr_task.start_time )
                price_prev_farm = curr_server_farm.cal_total_price(curr_task.input_time, curr_server_farm.prev_time )
                diff2 = abs(price_next_farm - price_prev_farm)

                if diff2 < 0.5:
                    reward_stage1_new = 25
                else:
                    reward_stage1_new = math.exp(1/diff2) * 5


                curr_server.prev_time = curr_task.start_time
                curr_server_farm.prev_time = curr_task.start_time


            if i >= 1: 
                RL_farm.store_transition(observation_1_last, action1, reward_stage1_old, observation_1_new)
                RL_server[farm_id].store_transition(observation_2_last, action2, reward_stage2_old, observation_2_new)

            observation_1_last = observation_1_new
            observation_2_last = observation_2_new
            reward_stage1_old = reward_stage1_new
            reward_stage2_old = reward_stage2_new

            RL_server_n[server_id] += 1
            last_input_time = curr_task.input_time
          
            if (i > 200) and (i % 5 == 0):
                RL_farm.learn()

            if (RL_server_n[server_id] > 200) and (server_id % 5 == 0):
                RL_server[server_id].learn()

            if drop:
                print("task " + str(i) + " drop")
            else:
                print("task " + str(i) + ": farm " + str(farm_id) + " server: " + str(server_id))
            print("----------------------")
            if i == 999:
                print("total_cost")
                print(total_cost.total_price(it))


   
        