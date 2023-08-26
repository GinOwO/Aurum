#include "queues.h"
#include "process.h"

#include<vector>
#include<queue>
#include<algorithm>

JobQueue::JobQueue(){
    // Nothing to do here
}

void JobQueue::push(Process p){
    jobQueue.push(p);
}

Process JobQueue::pop(){
    Process p = jobQueue.front();
    jobQueue.pop();
    return p;
}

bool JobQueue::empty(){
    return jobQueue.empty();
}

Queue::Queue(bool (*c)(Process, Process)){
    this->comparator = c;
}

void Queue::push(Process p){
    if(!finalized)
        readyQueue.push_back(p);
    else
        readyQueue.insert(std::upper_bound(readyQueue.begin(), readyQueue.end(), p, this->comparator), p);
}

Process Queue::pop(){
    if(!finalized){
        std::sort(readyQueue.begin(), readyQueue.end(), this->comparator);
        finalized = true;
    }
    Process p = readyQueue.front();
    readyQueue.erase(readyQueue.begin());
    return p;
}

bool Queue::empty(){
    return readyQueue.empty();
}

std::vector<Process> Queue::getQueue() const{
    return readyQueue;
}

void Queue::finalize(){
    std::sort(readyQueue.begin(), readyQueue.end(), this->comparator);
    finalized = true;
}

ReadyQueue::ReadyQueue(bool (*c)(Process, Process)): Queue(c){
    // Nothing to do here
}

WaitingQueue::WaitingQueue(bool (*c)(Process, Process)): Queue(c){
    // Nothing to do here
}
