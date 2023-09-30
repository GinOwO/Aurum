#ifndef AURUM_QUEUES_H
#define AURUM_QUEUES_H

#include "process.h"

#include <vector>
#include <queue>

class Queue{
protected:
    std::vector<Process*> queue;
public:
    Queue();
    ~Queue();
    Queue cloneQueue();

    Process* pop();
    Process* front();

    int size();
    bool empty();
    void clear();
    void push(Process*);
    std::vector<Process*> getQueue() const;

    void sort(bool (*cmp)(Process*, Process*)=Process::processArrivalCmp);
};

#endif
