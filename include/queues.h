#ifndef _AURUM_QUEUES_H
#define _AURUM_QUEUES_H 1

#include "process.h"

#include<vector>
#include<queue>

class Queue{
protected:
    std::vector<Process*> queue;
public:
    Queue();
    ~Queue();
    void push(Process*);
    Process* pop();
    Process* front();
    int size();
    bool empty();
    void clear();
    std::vector<Process*> getQueue() const;
    void sort(bool (*cmp)(Process*, Process*)=Process::processArrivalCmp);
};

#endif