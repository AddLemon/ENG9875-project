#!python3
#encoding:utf-8

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def read_evaluation_file(file_num):
    if file_num == 1:
        fd = open("FCFS_each_turnaroundTime.txt", "r")
    elif file_num == 2:
        fd = open("HRRN_each_turnaroundTime.txt", "r")
    elif file_num == 3:
        fd = open("SJF_each_turnaroundTime.txt", "r")
    elif file_num == 4:
        fd = open("STCF_each_turnaroundTime.txt", "r")
    else:
        raise ValueError("file_num must be 1 to 4")
    
    ret = fd.readlines()
    fd.close()
    return ret

def main():
    data_FCFS = read_evaluation_file(1)
    data_HRRN = read_evaluation_file(2)
    data_SJF = read_evaluation_file(3)
    data_STCF = read_evaluation_file(4)
    FCFS_weightTurnTime = [float(x) for x in data_FCFS[0].strip().split(' ')]
    HRRN_weightTurnTime = [float(x) for x in data_HRRN[0].strip().split(' ')]
    SJF_weightTurnTime = [float(x) for x in data_SJF[0].strip().split(' ')]
    STCF_weightTurnTime = [float(x) for x in data_STCF[0].strip().split(' ')]
    FCFS_nTime = [int(x) for x in data_FCFS[2].strip().split(' ')]
    HRRN_nTime = [int(x) for x in data_HRRN[2].strip().split(' ')]
    SJF_nTime = [int(x) for x in data_SJF[2].strip().split(' ')]
    STCF_nTime = [int(x) for x in data_STCF[2].strip().split(' ')]

    data_FCFS_weightTurnTime = pd.DataFrame({'x':FCFS_nTime, 'y': FCFS_weightTurnTime})
    data_HRRN_weightTurnTime = pd.DataFrame({'x':HRRN_nTime, 'y': HRRN_weightTurnTime})
    data_SJF_weightTurnTime = pd.DataFrame({'x':SJF_nTime, 'y': SJF_weightTurnTime})
    data_STCF_weightTurnTime = pd.DataFrame({'x':STCF_nTime, 'y': STCF_weightTurnTime})
    mean_FCFS = data_FCFS_weightTurnTime.groupby('x').mean()
    mean_HRRN = data_HRRN_weightTurnTime.groupby('x').mean()
    mean_SJF = data_SJF_weightTurnTime.groupby('x').mean()
    mean_STCF = data_STCF_weightTurnTime.groupby('x').mean()

    # plt.plot(mean_FCFS.index, mean_FCFS['y'], label="FCFS")
    plt.plot(mean_HRRN.index, mean_HRRN['y'], label="HRRN")
    plt.plot(mean_SJF.index, mean_SJF['y'], label="SJF")
    plt.plot(mean_STCF.index, mean_STCF['y'], label="STCF")

    plt.legend()
    plt.ylabel("turnaround time")
    plt.xlabel("needed time of each process")
    plt.savefig("eachTurnaroundTime.png")
    plt.clf()
    print("ok")


main()