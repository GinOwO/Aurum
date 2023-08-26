#ifndef _SCHV_QUEUE_H
#define _SCHV_QUEUE_H 1

#include "process.h"

#include<vector>
#include<queue>

class JobQueue{
    std::queue<Process> jobQueue;
public:
    JobQueue();
    void push(Process);
    Process pop();
    bool empty();
};

class Queue{
protected:
    bool (*comparator)(Process, Process);
    bool finalized=false;

    std::vector<Process> readyQueue;
public:
    Queue(bool (*)(Process, Process));
    void push(Process);
    Process pop();
    bool empty();
    void finalize();
    std::vector<Process> getQueue() const;
};

class ReadyQueue: public Queue{
public:
    ReadyQueue(bool (*)(Process, Process));
};

class WaitingQueue: public Queue{
public:
    WaitingQueue(bool (*)(Process, Process));
};

#endif