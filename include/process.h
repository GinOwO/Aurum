#ifndef _AURUM_PROCESS_H
#define _AURUM_PROCESS_H 1

#include<utility>
#include<string>
#include<vector>

class Process{
    int ptr;
    int priority;
    std::string name;
    std::vector<std::pair<int,int>> instructions;

    // arrivalTime, burstTime, waitingTime, turnaroundTime, responseTime
    std::vector<int> times;
public:
    static int timeToTick;
    static int cyclesToTick;
    static void kill(Process*);

    Process(std::string, const std::vector<int>&, int=5);
    void push(const std::pair<int,int>&);
    std::pair<int,int> next();
    Process* fork();
    int getPriority() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getResponseTime() const;
};

#endif