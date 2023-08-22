#include<queue>
#include<utility>
#include<string>
#include<vector>

#ifndef _SCHV_PROCESS_H
#define _SCHV_PROCESS_H 1

class Process{
    int ptr;
    int pid;
    std::string name;
    std::vector<std::pair<int,int>> instructions;

    // arrivalTime, burstTime, waitingTime, turnaroundTime, responseTime
    std::vector<int> times;
public:
    static int timeToTick;
    static int cyclesToTick;

    Process(int,std::string, const std::vector<int>&);
    void push(const std::pair<int,int>&);
    std::pair<int,int> next();

};

#endif