# Optimization-in-Cloud-Computing
  In order to reduce energy and time cost created by data center when it transfers data between machines, 
we will perform resource provisioning and task scheduling using Greedy algorithm and Round-robin scheduling algorithm 
such that total energy is minimized.
Also, later this project will present DRL-Cloud, a novel Deep Reinforcement Learning (DRL)-based RP and TS system, to minimize energy 
cost for large-scale CSPs with very large number of servers that receive enormous numbers of user requests per day.
Explanation of each file :
1. read_data.py: used to filter out a large amount of original data from csv files to the simple txt files included in the repository
2. Cloud_Platform_Model.h   Cloud_Platform_Model.cpp:
used to create the high level class models, server and server farm models, which are used to support and analyze the indicators of the result.
3. User_Workload_Model.cpp  User_Workload_Model.h  baseline.h:
used to create workload model, cloud platform model and energy consumption model, which are used to support and analyze the indicators of the result.
4. Round_robin_alg.cpp  Greedy_alg.cpp:
used to implement our two baseline Algorithms: greedy and round robin algorithm.

