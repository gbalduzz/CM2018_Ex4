#!/bin/python3

import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("second_order_ODE_solution.txt")

fig_id = 0

plt.figure(fig_id)
fig_id += 1
plt.plot(data[:,0], data[:,1])
plt.xlabel("t")
plt.ylabel(r"$\theta$")

plt.figure(fig_id)
fig_id += 1
plt.plot(data[:,1], data[:,2])
plt.xlabel(r"$\theta$")
plt.ylabel(r"$\dot{\theta}$")

plt.show()

