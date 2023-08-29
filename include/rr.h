#ifndef _AURUM_ROUND_ROBIN_H
#define _AURUM_ROUND_ROBIN_H 1

#include "process.h"         // Path: include/process.h
#include "queues.h"          // Path: include/queues.h
#include "basealg.h"         // Path: include/basealog.h
#include "ctexceptions.h"    // Path: include/ctexceptions.h

class RoundRobin : public BaseAlgorithm {
public:
    RoundRobin(Queue* aq, Queue* rq, Queue* wq, Queue* bq, Queue* dq, int ttt, int ctt, int tq);
    void run() override;

private:
    int timeQuantum;
};

#endif 
