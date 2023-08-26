#ifndef _AURUM_QUEUES_H
#define _AURUM_QUEUES_H 1

#include "process.h"

#include<vector>
#include<queue>

/*
bool (*processArrivalCmp)(Process*, Process*) = [](Process* a, Process* b){
    return a->getArrivalTime()<b->getArrivalTime();
};
bool (*processPriorityCmp)(Process*, Process*) = [](Process* a, Process* b){
    return a->getPriority()<b->getPriority() ||
    (a->getPriority()==b->getPriority()&&a->getArrivalTime()<b->getArrivalTime());
};
*/
class Queue{
    std::vector<int> queue;
public:
    Queue();
    ~Queue();
    void push(int);
    int pop();
    int front();
    int size();
    bool empty();
    void clear();
    std::vector<int> getQueue() const;
};

#endif