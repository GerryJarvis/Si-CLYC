# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 13:16:27 2023

@author: 10977
"""

import matplotlib.pyplot as plt

dE = []
E = []


# particle_types = ["Triton"] 
particle_types =["Triton"]   #["O"],,"He","Li" "O","N","C","B","Be""H","Deutron",

for i in particle_types:
    with open(i+"_n.txt","r") as data:   # 
        for line in data:
            datalist = line.strip().split('  ')
            if float(datalist[2]) > 0:
                dE.append(float(datalist[0]))
                E.append(float(datalist[1]))
    data.close()

            
plt.hist2d(E,dE,bins=300,cmap="coolwarm")#Blues,coolwarm,gist_ncar_r,ocean_r,jet
# 修改颜色渐变范围
plt.colorbar()
plt.clim(0,30)
# 添加色标
# cbar = plt.colorbar()
# plt.scatter(E,dE)
plt.xlim(0,230)
plt.title("Particle Discrimination with Si&CLYC")
plt.xlabel("E/MeV")
plt.ylabel("dE/MeV")
plt.ylim(0,5)
# 修改色标标签
# cbar.set_label('Count')

plt.show()

