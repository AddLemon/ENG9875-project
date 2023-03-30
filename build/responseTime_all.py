#!python3
#encoding:utf-8

import os
import matplotlib.pyplot as plt

def read_evaluation_file(file_num):
    if file_num == 1:
        fd = open("FCFS_responseTime.txt", "r")
    elif file_num == 2:
        fd = open("HRRN_responseTime.txt", "r")
    elif file_num == 3:
        fd = open("SJF_responseTime.txt", "r")
    elif file_num == 4:
        fd = open("STCF_responseTime.txt", "r")
    else:
        raise ValueError("file_num must be 1 to 4")
    
    ret = fd.readlines()
    fd.close()
    return ret

def aTime_short():
    data_FCFS = read_evaluation_file(1)
    data_HRRN = read_evaluation_file(2)
    data_SJF = read_evaluation_file(3)
    data_STCF = read_evaluation_file(4)
    FCFS_aTime_short = [float(x) for x in data_FCFS[0].strip().split(' ')]
    HRRN_aTime_short = [float(x) for x in data_HRRN[0].strip().split(' ')]
    SJF_aTime_short = [float(x) for x in data_SJF[0].strip().split(' ')]
    STCF_aTime_short = [float(x) for x in data_STCF[0].strip().split(' ')]

    xaxis = [i + 1 for i in range(-1,100,4)]

    plt.plot(xaxis, FCFS_aTime_short, label="FCFS")
    plt.plot(xaxis, HRRN_aTime_short, label="HRRN")
    plt.plot(xaxis, SJF_aTime_short, label="SJF")
    plt.plot(xaxis, STCF_aTime_short, label="STCF")

    plt.legend()
    plt.title("algorithms with concentrated arriving time")
    plt.ylabel("Response Time")
    plt.xlabel("ratio / *10%")
    plt.savefig("responseTime_all_aTime_short.png")
    plt.clf()
    print("ok")

def nTime_short():
    data_FCFS = read_evaluation_file(1)
    data_HRRN = read_evaluation_file(2)
    data_SJF = read_evaluation_file(3)
    data_STCF = read_evaluation_file(4)
    FCFS_nTime_short = [float(x) for x in data_FCFS[1].strip().split(' ')]
    HRRN_nTime_short = [float(x) for x in data_HRRN[1].strip().split(' ')]
    SJF_nTime_short = [float(x) for x in data_SJF[1].strip().split(' ')]
    STCF_nTime_short = [float(x) for x in data_STCF[1].strip().split(' ')]

    xaxis = [i + 1 for i in range(-1,100,4)]

    plt.plot(xaxis, FCFS_nTime_short, label="FCFS")
    plt.plot(xaxis, HRRN_nTime_short, label="HRRN")
    plt.plot(xaxis, SJF_nTime_short, label="SJF")
    plt.plot(xaxis, STCF_nTime_short, label="STCF")

    plt.legend()
    plt.title("algorithms with short needed time")
    plt.ylabel("Response Time")
    plt.xlabel("ratio / *10%")
    plt.savefig("responseTime_all_nTime_short.png")
    plt.clf()
    print("ok")

def nTime_long():
    data_FCFS = read_evaluation_file(1)
    data_HRRN = read_evaluation_file(2)
    data_SJF = read_evaluation_file(3)
    data_STCF = read_evaluation_file(4)
    FCFS_nTime_long = [float(x) for x in data_FCFS[2].strip().split(' ')]
    HRRN_nTime_long = [float(x) for x in data_HRRN[2].strip().split(' ')]
    SJF_nTime_long = [float(x) for x in data_SJF[2].strip().split(' ')]
    STCF_nTime_long = [float(x) for x in data_STCF[2].strip().split(' ')]

    xaxis = [i + 1 for i in range(-1,100,4)]

    plt.plot(xaxis, FCFS_nTime_long, label="FCFS")
    plt.plot(xaxis, HRRN_nTime_long, label="HRRN")
    plt.plot(xaxis, SJF_nTime_long, label="SJF")
    plt.plot(xaxis, STCF_nTime_long, label="STCF")

    plt.legend()
    plt.title("algorithms with long needed time")
    plt.ylabel("Response Time")
    plt.xlabel("ratio / *10%")
    plt.savefig("responseTime_all_nTime_long.png")
    plt.clf()
    print("ok")

aTime_short()
nTime_short()
nTime_long()