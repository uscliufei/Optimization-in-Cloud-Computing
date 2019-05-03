import price_model as p
import numpy as np
import random

#user_workload_model
class Job:
    def __init__(self, job_id):
        self.job_id = job_id
        self.tasks = []
        
class Task:
    def __init__(self, input_time, request_cpu, request_memory, task_id, job_id, n_vm = 5):
        self.input_time = input_time
        self.request_cpu = request_cpu
        self.request_memory = request_memory
        self.task_id = task_id
        self.job_id = job_id
        self.deadline = random.randint(6, 12) + input_time
        self.execution_time = random.randint(1, 6)
        self.vm_type = random.randint(0, n_vm-1)

        self.start_time = input_time
        self.end_time = input_time + self.execution_time

#cloud_platform_model
class Server_farm:
    def __init__(self, Server_farm_id, n_servers, n_vm):
        self.n_servers = n_servers
        self.Server_farm_id = Server_farm_id
        self.n_vm = n_vm
        self.servers = []
        self.initialize_servers()
        self.total_price = 0
        self.prev_time = 0

    def initialize_servers(self):
        self.servers = [Server(i, self.n_vm) for i in range(self.n_servers)]

    def power(self, time):
        power = 0
        for i in range(self.n_servers):
            power += self.servers[i].power(time)
        return power

    def price(self, time):
        return p.Price_model(time, self.power(time))

    def cal_total_price(self, current_time, time):
        total_cost = 0
        for sv in self.servers:
            total_cost += sv.cal_total_price(current_time, time)
        return total_cost


class Server:
    def __init__(self, server_id, n_vm):
        self.n_vm = n_vm
        self.server_id = server_id
        self.vms = []
        self.cpu = 1
        self.memory = 1
        self.utilization_opt_rate = random.uniform(0.4, 0.7) #in the range of 0.4 to 0.7
        self.alpha = random.uniform(0.3, 0.5)
        self.beta = random.uniform(10, 15)
        self.working_tasks = []
        self.waiting_tasks = []
        self.initialize_vm()
        self.total_cost = 0
        self.prev_time = 0

    #not done yet
    def get_cpu_memory(self, time, vm_type):

        cpu = self.vms[vm_type].using_cpu
        memory = self.vms[vm_type].using_memory

        for task in self.working_tasks:
            if time > task.end_time and task.vm_type == vm_type:
                cpu -= task.request_cpu
                memory -= task.request_memory

        for task in self.waiting_tasks:
            if task.vm_type == vm_type and task.start_time < time and task.end_time > time:
                cpu += task.request_cpu
                memory += task.request_memory

        cpu = self.vms[vm_type].cpu - cpu
        memory = self.vms[vm_type].memory - memory

        return cpu,memory


    def initialize_vm(self):
        cpu = [random.random() for _ in range(self.n_vm)]
        memory = [random.random() for _ in range(self.n_vm)]
        for i in range(self.n_vm):
            self.vms.append( Vm( i, cpu[i]/sum(cpu), memory[i]/sum(memory)) )


    def power(self,time):
        utilization_rate = 0
        for i in range(self.n_vm):
            cpu, memory = self.get_cpu_memory(time, i)
            utilization_rate  += cpu

        #static power
        if utilization_rate == 0:
            power_static = 0
        else:
            power_static = 0.5

        #dynamic power
        if utilization_rate < self.utilization_opt_rate:
            power_dynamic = utilization_rate * self.alpha
        else:
            power_dynamic = self.utilization_opt_rate * self.alpha + (utilization_rate - self.utilization_opt_rate) ** 2 * self.beta

        return (power_dynamic + power_static)



    def price(self, time, power):
        return p.Price_model(time, self.power(time))


    def cal_total_price(self, current_time, time):
        cost = self.total_cost
        period = int(time - current_time)
        for i in range(1,period):
            cost += self.price (current_time + i, self.power(current_time + i))
        return cost





class Vm:
    def __init__(self, type_id, cpu, memory):
        self.type_id = type_id
        self.cpu = cpu
        self.memory = memory
        self.using_cpu = 0
        self.using_memory = 0


class cloud_env:
    def __init__(self, n_serverfarms = 10, n_servers = 10, n_vms = 5):

        self.n_serverfarms = n_serverfarms
        self.n_servers = n_servers
        self.n_vms = n_vms

        self.action_space_stage_1 = [i for i in range(n_serverfarms * 24 )] #the action space also contains the time.
        self.action_space_stage_2 = [i for i in range(n_servers)]

        self.n_actions_stage_1 = len(self.action_space_stage_1)
        self.n_actions_stage_2 = len(self.action_space_stage_2)

        self.n_features = 4 # cpu, memory for task and server
        self.serverfarms = []
        self.initialize_serverfarms()


    def initialize_serverfarms(self):
        self.serverfarms = [Server_farm(i, self.n_servers, self.n_vms) for i in range(self.n_serverfarms)]

    def step_farm(self, action):
        #choose action means assign this task to this serverfarm

        farm_id = int(action/24);
        waiting_time = int(action)%24

        return farm_id, waiting_time


    # def step_server(self, action, time, time_prev, cur_task):

    #     #choose action means assign this task to this serverfarm
    #     server = serverfarms[farm].servers[action]
    #     power_next = server.power(start_time)
    #     power_prev = server.power(time_prev)

    #     reward_stage2 = - server.price(start_time, power_next -  power_prev)

    #     #state_change
    #     vm_type = cur_task.vm_type
    #     cur_task.start_time = start_time
    #     # server.vms[vm_type].using_cpu += cur_task.request_cpu
    #     # server.vms[vm_type].usng_memory += cur_task.request_memory

    #     #refreash the farm

    #     #refresh_env(cur_task)

    #     return reward_stage2

    def update_env(self, last_input_time, time):
        for svfm in self.serverfarms:
            for sv in svfm.servers:
                new_working_tasks = []
                new_waiting_tasks = []

                for working_task in sv.working_tasks:
                    if working_task.end_time > time:
                        new_working_tasks.append(working_task)
                    else:
                        sv.vms[working_task.vm_type].using_cpu -= working_task.request_cpu
                        sv.vms[working_task.vm_type].using_memory -= working_task.request_memory

                for waiting_task in sv.waiting_tasks:
                    if waiting_task.start_time > time:
                        new_working_tasks.append(waiting_task)
                        sv.vms[waiting_task.vm_type].using_cpu += waiting_task.request_cpu
                        sv.vms[waiting_task.vm_type].using_memory += waiting_task.request_memory
                    else:
                        new_waiting_tasks.append(waiting_task)

                sv.working_tasks = new_working_tasks;
                sv.waiting_tasks = new_waiting_tasks;

        for svfm in self.serverfarms:
            total_cost_farm = 0
            for sv in svfm.servers:
                sv.total_cost_server =  sv.cal_total_price(last_input_time, time)
                total_cost_farm += sv.total_cost_server
            svfm.total_price += total_cost_farm



    def check_server(self, time,curr_server,curr_task):

        vm_type = curr_task.vm_type
        cpu, memory = curr_server.get_cpu_memory(time, vm_type)

        print("server cpu " + str(cpu) + " memory " + str(memory))

        if cpu > curr_task.request_cpu and memory > curr_task.request_memory:
            return True
        else:
            return False

    def check_server_farm(self, time, cur_server_farm, curr_task):
        vm_type = curr_task.vm_type
        server_id = -1
        drop = True
        for i in range(len(cur_server_farm.servers)):
            if self.check_server(time, cur_server_farm.servers[i], curr_task):
                server_id = i
                drop = False
                break
        return drop, server_id




