#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep  1 11:22:02 2023

@author: qww
"""

"""
generate 252Cf neutron source energy
using equations
"""

import matplotlib.pyplot as plt
import numpy as np


k = 1.38
T = 1.43
x = np.linspace(0,30,100)
# y = 2*np.sqrt(x)*np.exp(-x/(k*T))/np.sqrt(np.pi*2.92)
y = 2*np.sqrt(x)*np.exp(-x/1.43)/np.sqrt(np.pi*2.92)
plt.plot(x,y)
plt.xlim(0,30)
plt.ylim(0,0.4)
plt.xlabel("Energy/MeV")
plt.ylabel("Probability")
plt.show()
# print(max(y),list(y).index(max(y)),x[list(y).index(max(y))])

# t = 0
# for i in range(0,len(y)):
#     if x[i] <= 10:
#         t += y[i]*x[i]
        
# print(t)
# with open("CfEnergy.txt","w") as data:
#     for i in range(0,len(y)):
#         if x[i] <= 12:
#             data.write("/gps/hist/point  "+str(x[i]) + " "+str(y[i]))
# data.close()