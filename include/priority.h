#ifndef AURUM_PRIORITY_H
#define AURUM_PRIORITY_H

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h
#include "basealg.h"    // Path: include/basealg.h

class PriorityAlgorithm : public BaseAlgorithm{
public:
    LongestRemainingJobFirst(Queue*,Queue*,Queue*,Queue*,Queue*,int,int);
    void run();
    static bool comparator(Process *p1, Process *p2);
};

#endif
