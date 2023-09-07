#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May 31 14:35:03 2023

@author: gerry
"""


nuclide = ["H","He","Li","Be","B", "O","N","C","Deutron","Triton"]  #

particle_types = ["neutron", "proton", "deuteron", "triton", "e-", 
                  "gamma", "alpha", "Li6", "Be8", "B10", "C12", 
                  "N14", "O16"]
particle_lists = {particle_type: [] for particle_type in particle_types}
rest = []

for i in nuclide:
    with open(i+".txt","r") as data:
        for line in data:
            datalist = line.strip().split('  ')
            particle_type = datalist[3]
            if particle_type in particle_lists:
                particle_lists[particle_type].append(datalist)
            else :
                rest.append(datalist)

particle_lists["rest"] = rest
 
for i in particle_types:
    with open(i+".txt","w") as file: #"~/re/"+
        data = particle_lists[i]
        for j in range(0,len(data)):
            file.write(data[j][0]+"  "+data[j][1]+"  "+data[j][2]+"  "+data[j][3]+"\n")
    file.close()

with open("rest.txt","w") as rfile:
    rdata = particle_lists["rest"]
    for j in range(0,len(rdata)):
        rfile.write(rdata[j][0]+"  "+rdata[j][1]+"  "+rdata[j][2]+"  "+rdata[j][3]+"\n")
    rfile.close()
            
