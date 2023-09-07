# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 13:16:27 2023

@author: 10977
"""

import matplotlib.pyplot as plt

dE = []
E = []

test1 = []
test2 = []
test = []

particle_types = ["Particle1"]
# particle_types =["H","He","Li","Be","B", "O","N","C","Deutron","Triton"]   #["Triton"] 

for i in particle_types:
    with open(i+".txt","r") as data:   # 
        for line in data:
            datalist = line.strip().split('  ')
            if float(datalist[2]) > 0:
                dE.append(float(datalist[0]))
                E.append(float(datalist[1]))
    data.close()

            
plt.hist2d(E,dE,bins=500,cmap="coolwarm")#Blues,coolwarm,gist_ncar_r,ocean_r,jet
# 修改颜色渐变范围
plt.colorbar()
plt.clim(0,5)
# 添加色标
# cbar = plt.colorbar()
# plt.scatter(E,dE)
plt.xlim(0,2000)
plt.title("Particle Discrimination with Si&CLYC")
plt.xlabel("E/MeV")
plt.ylabel("dE/MeV")
plt.ylim(0,150)
# 修改色标标签
# cbar.set_label('Count')

plt.show()

# print(len(test))
# for i in range(0,11):
#     print(test[i])
    
# print(len(test2))
# for i in range(0,10):
#     print(test2[i])