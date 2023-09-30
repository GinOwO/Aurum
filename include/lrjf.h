#ifndef AURUM_LONGEST_JOB_FIRST_H
#define AURUM_LONGEST_JOB_FIRST_H

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h
#include "basealg.h"    // Path: include/basealg.h

class LongestRemainingJobFirst : public BaseAlgorithm{
public:
    LongestRemainingJobFirst(Queue*,Queue*,Queue*,Queue*,Queue*,int,int);
    void run();
    static bool comparator(Process *p1, Process *p2);
};

#endif