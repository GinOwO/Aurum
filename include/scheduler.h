#ifndef _SCHV_QUEUE_H
#define _SCHV_QUEUE_H 1

#include "program.h"
#include "ctexceptions.h"
#include "process.h"

#include<vector>
#include<string>
#include<queue>

// TODO

class Scheduler{
    int idleTime;
    int wastedCycles;
    int cyclesPerTick;
    int timeUnitsPerTick;
    std::queue<Process> arrivalQueue;
public:
    Scheduler(const int&,const int&);
    void load(const std::string&);
    void reset();
};

#endif