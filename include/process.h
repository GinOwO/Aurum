#ifndef _SCHV_PROCESS_H
#define _SCHV_PROCESS_H 1

#include<queue>
#include<utility>
#include<string>
#include<vector>

class Process{
    int ptr;
    int pid;
    int priority;
    std::string name;
    std::vector<std::pair<int,int>> instructions;

    // arrivalTime, burstTime, waitingTime, turnaroundTime, responseTime
    std::vector<int> times;
public:
    static int timeToTick;
    static int cyclesToTick;
    static void kill(Process*);

    Process(int,std::string, const std::vector<int>&, int=5);
    void push(const std::pair<int,int>&);
    std::pair<int,int> next();
    Process* fork(int);
};

#endif