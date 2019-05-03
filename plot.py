import random
import numpy as np
import matplotlib.pyplot as plt

x = [i for i in range(200)]
total_cost = []
for i in range(250):
    if i < 50:
        cost = random.uniform( (200 - i) * 900, (200 - i) * 1000)
        total_cost.append(cost)
    elif i >= 50 and i < 100:
        cost = random.uniform( (200 - i)  * 800, (200 - i) * 900)
        total_cost.append(cost)
    elif i >= 100 and i < 150:
        cost = random.uniform( (200 - i/1.5) * 750, (200 - i) * 800)
        total_cost.append(cost)
    else:
        cost = random.uniform( (200 - i/1.5) * 740, (200 - i) * 770)
        total_cost.append(cost)

plt.figure()
plt.plot(x, total_cost)

# x=[0,1]
# y=[0,1]
 
# plt.figure()
# plt.plot(x,y)
# plt.xlabel("time(s)")
# plt.ylabel("value(m)")
# plt.title("A simple plot")
plt.show()