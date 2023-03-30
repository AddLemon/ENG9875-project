#!python3
#encoding:utf-8

import os
import matplotlib.pyplot as plt

def read_evaluation_file():
    fd = open("STCF_responseTime.txt", "r")
    ret = fd.readlines()
    fd.close()
    return ret

def main():
    data = read_evaluation_file()
    aTime_short = [float(x) for x in data[0].strip().split(' ')]
    nTime_short = [float(x) for x in data[1].strip().split(' ')]
    nTime_long = [float(x) for x in data[2].strip().split(' ')]

    xaxis = [i + 1 for i in range(-1,25,1)]

    plt.plot(xaxis, aTime_short, label="ratio of concentrated arriving Time ")
    plt.plot(xaxis, nTime_short, label="ratio of short needed time")
    plt.plot(xaxis, nTime_long, label="ratio of long needed time")

    plt.legend()
    plt.ylabel("Response Time")
    plt.xlabel("ratio / *10%")
    plt.savefig("STCF_responseTime.png")
    plt.clf()
    print("ok")


main()