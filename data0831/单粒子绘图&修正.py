# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 13:16:27 2023

@author: 10977
"""

import matplotlib.pyplot as plt

dE = []
E = []

test = []

particle_types = ["Triton"]  #["H","He","Li","Be","B", "O","N","C","Deutron","Triton"]   #
# particle_types = ["neutron", "proton", "deuteron", "triton", "e-", 
#                   "gamma", "alpha", "Li6", "Be8", "B10", "C12", neutron
#                   "N14", "O16", "rest"]

for i in particle_types:
    with open(i+".txt","r") as data:   # 
        for line in data:
            datalist = line.strip().split('  ')
            if float(datalist[2]) > 0:
                # dE.append(float(datalist[0]))
                # E.append(float(datalist[1]))
                if float(datalist[0])/4 + float(datalist[1])/250 > 1:
                    dE.append(float(datalist[0])/2)
                    E.append(float(datalist[1])/2)
                    ls = [str(float(datalist[0])/2),str(float(datalist[1])/2),datalist[2],datalist[3]]
                    test.append(ls)
                else:
                    dE.append(float(datalist[0]))
                    E.append(float(datalist[1]))
                    test.append(datalist)          
    data.close()
    # fix 
    with open(i+"_n.txt","w") as data_n:
        for i in range(0,len(test)):
            data_n.write(test[i][0] + "  " +test[i][1] + "  "+test[i][2] + "  "+test[i][3] + "\n")
    data_n.close()

            
plt.hist2d(E,dE,bins=500,cmap="coolwarm")#Blues,coolwarm,gist_ncar_r,ocean_r,jet
# 修改颜色渐变范围
plt.colorbar()
plt.clim(0,50)
# 添加色标
# cbar = plt.colorbar()
# plt.scatter(E,dE)
# plt.xlim(0,2000)                   #(0,2000)
plt.title("Particle Discrimination with Si&CLYC")
plt.xlabel("E/MeV")
plt.ylabel("dE/MeV")
# plt.ylim(0,140)                        #(0,140)
# 修改色标标签
# cbar.set_label('Count')

plt.show() 
