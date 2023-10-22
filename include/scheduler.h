#ifndef AURUM_QUEUE_H
#define AURUM_QUEUE_H

#include "ptable.h"
#include "queues.h"
#include "basealg.h"

#include <vector>
#include <string>
#include <queue>
#include <utility>

struct __State__{
    int ticksElapsed;
    int idleTime;
    int wastedCycles;
    ProcessTable processTable;
    Queue arrivalQueue;
    Queue readyQueue;
    Queue waitingQueue;
    Queue blockedQueue;
    Queue deadQueue;
    Queue Queue1;
    Queue Queue2;
    Queue Queue3;
    std::vector<std::pair<int,int>> ganttChart;
};

using State = struct __State__;

class Scheduler{
    int idleTime;
    int wastedCycles;
    int cyclesPerTick;
    int timeUnitsPerTick;
    int algorithmID;
    int timeQuantum;
    BaseAlgorithm* algorithm;

public:
    static int pid;

    Queue arrivalQueue;
    Queue readyQueue;
    Queue waitingQueue;
    Queue blockedQueue;
    Queue deadQueue;
    Queue Queue1;
    Queue Queue2;
    Queue Queue3;
    ProcessTable processTable;
    std::vector<std::pair<int,int>> ganttChart;

    int getId() const noexcept;
    Scheduler(const int&,const int&);
    void load(const std::string&);
    void reset();
    void selectAlgorithm(const std::string&);
    bool isCompleted();
    std::string getAlgorithmName() const;
    std::string logging() const noexcept;

    void nextTick();
    State getState();
    void setState(State&);
    Process* fork(int);
};

#endif
