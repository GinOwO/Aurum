#ifndef AURUM_MULTI_LEVEL_FEEDBACK_QUEUE
#define AURUM_MULTI_LEVEL_FEEDBACK_QUEUE

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h
#include "basealg.h"    // Path: include/basealg.h

#include <unordered_map>

class MultiLevelFeedbackQueue : public BaseAlgorithm{
    Queue& Queue1;
    Queue& Queue2;
    Queue& Queue3;
    std::unordered_map<Process*, int> counts;
public:
    MultiLevelFeedbackQueue(Queue*,Queue*,Queue*,Queue*,Queue*,int,int,Queue&,Queue&,Queue&);
    void run();
    static bool comparator(Process *p1, Process *p2);
};


#endif
