#ifndef _AURUM_QUEUE_H
#define _AURUM_QUEUE_H 1

#include "ptable.h"
#include "queues.h"
#include "basealg.h"

#include<vector>
#include<string>
#include<queue>
#include<map>

class Scheduler{
    int idleTime;
    int wastedCycles;
    int cyclesPerTick;
    int timeUnitsPerTick;
    int algorithmID;
    int timeQuantum;
    Queue arrivalQueue;
    Queue readyQueue;
    Queue waitingQueue;
    Queue blockedQueue;
    Queue deadQueue;
    std::map<int,int> ganttChart;
    BaseAlgorithm* algorithm;

public:
    static int pid;

    ProcessTable processTable;
    Scheduler(const int&,const int&);
    void load(const std::string&);
    void reset();
    void selectAlgorithm(const std::string&);

    void nextTick();

    // TODO : Remove this
    void simulate();
};

#endif
