#ifndef _AURUM_QUEUE_H
#define _AURUM_QUEUE_H 1

#include "ctexceptions.h"
#include "program.h"
#include "process.h"
#include "ptable.h"
#include "queues.h"
#include "basealg.h"

#include<vector>
#include<string>
#include<queue>

class Scheduler{
    int idleTime;
    int wastedCycles;
    int cyclesPerTick;
    int timeUnitsPerTick;
    int algorithmID;
    Queue arrivalQueue;
    Queue readyQueue;
    Queue waitingQueue;
    Queue blockedQueue;
    Queue deadQueue;
    ProcessTable processTable;
    BaseAlgorithm* algorithm;
public:
    static int pid;

    Scheduler(const int&,const int&);
    void load(const std::string&);
    void reset();
    void simulate();
    void selectAlgorithm(const std::string&);
};

#endif