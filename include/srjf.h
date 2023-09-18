#ifndef _AURUM_SHORTEST_REMAINING_JOB_FIRST_H
#define _AURUM_SHORTEST_REMAINING_JOB_FIRST_H 1

#include "process.h"         // Path: include/process.h
#include "queues.h"          // Path: include/queues.h
#include "basealg.h"         // Path: include/basealg.h
#include "ctexceptions.h"    // Path: include/ctexceptions.h

class ShortestRemainingJobFirst : public BaseAlgorithm{
public:
    ShortestRemainingJobFirst(Queue*,Queue*,Queue*,Queue*,Queue*,int,int);
    void run();
    static bool comparator(Process *p1, Process *p2);
};

#endif
