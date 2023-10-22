#ifndef AURUM_PROCESS_H
#define AURUM_PROCESS_H

#include <utility>
#include <string>
#include <vector>

class Process{
    int ptr;
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int runningTime;
    std::string name;
    std::vector<std::pair<int,int>> instructions;
public:
    static int timeToTick;
    static int cyclesToTick;
    static void kill(Process*);
    static bool processNameCmp(Process*, Process*);
    static bool processArrivalCmp(Process*, Process*);
    static bool processPriorityCmp(Process*, Process*);
    static bool processBurstCmp(Process*, Process*);
    static bool processWaitingCmp(Process*, Process*);

    Process(std::string, int, int, int, int=5);
    std::vector<std::pair<int,int>> viewInstr() const;
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
    int getPID() const;
    int getRunningTime() const;
    std::string getName() const;

    void setPriority(int);
    void setArrivalTime(int);
    void setBurstTime(int);
    void setWaitingTime(int);
    void setPID(int);
};

#endif
