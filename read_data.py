import pandas as pd
import os
def process_data(csv_path):
    file = os.listdir(csv_path)
    file_num = 0
    for f in file:
        if 'csv' in f:
            file_num = file_num + 1
            if file_num != 1:
                df = pd.concat([df, pd.read_csv(csv_path + f,header = None)], axis=0, ignore_index=True)
            else:
                df = pd.read_csv(csv_path + f,header = None)
    return df

path = "/Users/macbook/Desktop/cluster-data-subset/data_subset/"
df_schema = pd.read_csv(path + 'schema.csv')

csv_path = path + 'job_events_subset/'
df_job_events = process_data(csv_path)
         


#machine_attributes_subset
csv_path = path + 'machine_attributes_subset/'
df_machine_attributes = process_data(csv_path)    

#machine_events_subset
csv_path = path + 'machine_events_subset/'
df_machine_events = process_data(csv_path)

#task_constraints_subset
csv_path = path + 'task_constraints_subset/'
df_task_constraints = process_data(csv_path)

#task_events_subset
csv_path = path + 'task_events_subset/'
df_task_events = process_data(csv_path)

#task_usage_subset
csv_path = path + 'task_usage_subset/'
df_task_usage = process_data(csv_path)

head_dic = {}
file_list = ['job_events','machine_attributes','machine_events','task_constraints','task_events','task_usage']
head_dic = {}

for file in file_list:
    for indexs in df_schema.index:
        if file in df_schema.loc[indexs].values[0]:
            if file in head_dic:
                head_dic[file].append(df_schema.loc[indexs].values[2])
            else:
                head_dic[file] = [df_schema.loc[indexs].values[2]]

  
df_job_events.columns = head_dic['job_events']
df_machine_attributes.columns = head_dic['machine_attributes']
df_machine_events.columns = head_dic['machine_events']
df_task_constraints.columns = head_dic['task_constraints']
df_task_events.columns = head_dic['task_events']
df_task_usage.columns = head_dic['task_usage']

df_task_usage['execution_time'] = (df_task_usage['end time'] - df_task_usage['start time'])/10**6




'''for i in range(df_job_events.shape[1]):
    df_job_events.iloc[:,i].to_csv('job_events' + df_job_events.columns.values[i]+'.txt', sep='\t', index=False)

for i in range(df_machine_attributes.shape[1]):
    df_machine_attributes.iloc[:,i].to_csv('machine_attributes'+ df_machine_attributes.columns.values[i]+'.txt', sep='\t', index=False)

for i in range(df_machine_events.shape[1]):
    df_machine_events.iloc[:,i].to_csv('machine_events'+ df_machine_events.columns.values[i]+'.txt', sep='\t', index=False)

for i in range(df_task_constraints.shape[1]):
    df_task_constraints.iloc[:,i].to_csv('task_constraints'+ df_task_constraints.columns.values[i]+'.txt', sep='\t', index=False)

for i in range(df_task_events.shape[1]):
    df_task_events.iloc[:,i].to_csv('task_events_'+ df_task_events.columns.values[i]+'.txt', sep='\n', index=False,float_format = '%.6f')

for i in range(df_task_usage.shape[1]):
    df_task_usage.iloc[:,i].to_csv('task_usage'+ df_task_usage.columns.values[i]+'.txt', sep='\t', index=False)'''

for i in range(df_task_events.shape[1]):
    df_task_events.iloc[:,i].to_csv('task_events_'+ df_task_events.columns.values[i]+'.txt', sep='\n', index=False,float_format = '%.6f')

df_task_usage['execution_time'].to_csv('execution_time.txt',sep='\n', index=False)


   











