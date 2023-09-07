# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 21:45:55 2023

@author: 10977
"""

nuclide = ["252Cf"]  #"Neutron" "1--100H""AmBe"
# nuclide = ["H","He","Li","Be","B", "O","N","C","Deutron","Triton"]  #
# particle_types = ["neutron", "proton", "deuteron", "triton", "e-", 
#                   "gamma", "alpha", "Li6", "Be8", "B10", "C12", 
#                   "N14", "O16"]
neutron_0 = []
neutron_1 = []
gamma_0 = []
gamma_1 = []
count = []
rest = []

time = []
# time0 = []

particle = []
particle_0 = []
particle_1 = []

useless00 = []
useless10 = []
wrong = []
for i in nuclide:
    with open(i+".txt","r") as data:
        for line in data:
            datalist = line.strip().split('  ')
            # count.append()
            if float(datalist[2]) >0 :
                # if datalist[3] == "gamma":
                #     time.append(datalist)
                if float(datalist[0]) == 0:
                    if float(datalist[1]) == 0:
                        useless00.append(datalist)
                    else:
                        if datalist[3] == "neutron":
                            neutron_0.append(datalist)
                        elif datalist[3] == "gamma":
                            gamma_0.append(datalist)
                        else:
                            rest.append(datalist)
                else:
                    if float(datalist[1]) == 0:
                        useless10.append(datalist)
                    else:
                        if datalist[3] == "neutron":
                            neutron_1.append(datalist)
                        elif datalist[3] == "gamma":
                            gamma_1.append(datalist)
                        else:
                            count.append(datalist)
            else:
                wrong.append(datalist)
    data.close()
                     
total =  len(neutron_0)+len(neutron_1)+len(count)+len(gamma_0)+len(gamma_1)+len(rest)+len(particle)   
print("有效事件数：",total)   
# print("proton:",len(particle),"占比：",len(particle)/total)
# print("无能损proton：",len(particle_0),"占比：",len(particle_0)/total)
# print("有能损proton：",len(particle_1),"占比：",len(particle_1)/total)
print("无能损中子：",len(neutron_0),"占比：",len(neutron_0)/total)
print("有能损中子：",len(neutron_1),"占比：",len(neutron_1)/total)
print("无能损gamma：",len(gamma_0),"占比：",len(gamma_0)/total)
print("有能损gamma：",len(gamma_1),"占比：",len(gamma_1)/total)
print("有能损带电粒子：",len(count),"占比：",len(count)/total)
print("无能损带电粒子：",len(rest),"占比：",len(rest)/total)           
print("useless:",len(useless00)+len(useless10),"双无：",len(useless00),"前有后无：",len(useless10))
print("wrong:",len(wrong))
print(len(wrong)+len(useless00)+len(useless10)+total)

# for i in range(0,10):
#     print(useless[i])
# energy = []
# for i in range(0,len(useless00)):
#     energy.append(float(useless00[i][5]))
# print(min(energy),max(energy))
# for i in range(0,len(neutron_0)):
#     energy.append(float(neutron_0[i][5]))
# print(min(energy),max(energy))
# print(neutron_1)
# print(len(time))