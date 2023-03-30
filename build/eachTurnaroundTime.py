#!python3
#encoding:utf-8

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def read_evaluation_file():
    fd = open("STCF_each_turnaroundTime.txt", "r")
    ret = fd.readlines()
    fd.close()
    return ret

def main():
    data = read_evaluation_file()
    turnTime = [int(x) for x in data[0].strip().split(' ')]
    weightTurnTime = [float(x) for x in data[1].strip().split(' ')]
    nTime = [int(x) for x in data[2].strip().split(' ')]

    data_turnTime = pd.DataFrame({'x':nTime, 'y': turnTime})
    data_weightTTime = pd.DataFrame({'x':nTime, 'y': weightTurnTime})
    mean_turnTime = data_turnTime.groupby('x').mean()
    mean_weightTTime = data_weightTTime.groupby('x').mean()

    plt.plot(mean_turnTime.index, mean_turnTime['y'], label="turnaround time ")
    plt.plot(mean_weightTTime.index, mean_weightTTime['y'], label="weighted turnaround time")

    plt.legend()
    plt.ylabel("time")
    plt.xlabel("needed time of each process")
    plt.savefig("STCF_eachTurnaroundTime.png")
    plt.clf()
    print("ok")


main()