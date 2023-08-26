#ifndef _AURUM_PROCESS_H
#define _AURUM_PROCESS_H 1

#include<utility>
#include<string>
#include<vector>

class Process{
    int ptr;
    int priority;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    std::string name;
    std::vector<std::pair<int,int>> instructions;
public:
    static int timeToTick;
    static int cyclesToTick;
    static void kill(Process*);
    static bool processArrivalCmp(Process*, Process*);
    static bool processPriorityCmp(Process*, Process*);
    static bool processBurstCmp(Process*, Process*);
    static bool processWaitingCmp(Process*, Process*);
    static bool processTurnaroundCmp(Process*, Process*);
    static bool processResponseCmp(Process*, Process*);
    static bool processNameCmp(Process*, Process*);

    Process(std::string, int, int, int, int=5);
    void push(const std::pair<int,int>&);
    std::pair<int,int> next();
    std::pair<int,int> peek();

    Process* fork();
    int updateFront(int);

    bool eof() const;
    int getPriority() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getWaitingTime() const;

    void setPriority(int);
    void setArrivalTime(int);
    void setBurstTime(int);
    void setWaitingTime(int);
};

#endif