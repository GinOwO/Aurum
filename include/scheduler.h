#ifndef _AURUM_QUEUE_H
#define _AURUM_QUEUE_H 1

#include "ctexceptions.h"
#include "program.h"
#include "process.h"
#include "ptable.h"
#include "queues.h"

#include<vector>
#include<string>
#include<queue>

// TODO

class Scheduler{
    int idleTime;
    int wastedCycles;
    int cyclesPerTick;
    int timeUnitsPerTick;
    Queue arrivalQueue;
    ProcessTable processTable;
public:
    static int pid;

    Scheduler(const int&,const int&);
    void load(const std::string&);
    void reset();
};

#endif