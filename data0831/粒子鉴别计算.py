# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 14:21:24 2023

@author: 10977
"""

import numpy as np
import matplotlib.pyplot as plt

N = [1,2,3,4,6,8,10,12,14,16]   # * 938 MeV/c^2
z = [1,1,1,2,3,4,5,6,7,8]
nuclide = ["H","Deutron","Triton","He","Li","Be","B","C","N", "O"]

x = np.linspace(20, 2020,2000)
# 非相对论区dE  = AMz^2*ln(E/M)/E
# 相对论区  dE  = AMz^2*(ln(E/M)-ln(1-2E/Mc^2)-2E/Mc^2)/E
for i in range(0,9):  #[8]
    y1 = 175*N[i]*z[0]**2*np.log(x/N[i])/x 
    # y2 = 100*N[i]*z[0]**2*(np.log(x/N[i])-np.log(1-2*x/(N[i]*938))-2*x/(N[i]*938))/x
    name = nuclide[i]
    plt.plot(x,y1,label=f"{i}")
    # plt.plot(x,y2,label="y2")
    
plt.xlabel("E/MeV")
plt.ylabel("dE/MeV")
plt.legend(nuclide[:9])
plt.xlim(50,500)
plt.ylim(0,70)
plt.title("Particle Discrimination Simulation")
plt.show()
    
