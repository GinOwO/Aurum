#ifndef AURUM_BASE_ALGORITHM_H
#define AURUM_BASE_ALGORITHM_H

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h

#include <algorithm>

class BaseAlgorithm{
protected:
    Queue *arrivalQueue;
    Queue *readyQueue;
    Queue *waitingQueue;
    Queue *blockedQueue;
    Queue *deadQueue;
    int timePerTick;
    int cyclesPerTick;
    int ticksElapsed;
    int totalProcesses;

public:
    BaseAlgorithm(Queue* arrivalQueue, Queue* readyQueue, Queue* waitingQueue,
            Queue* blockedQueue, Queue* deadQueue,int timePerTick, int cyclesPerTick){
        this->arrivalQueue = arrivalQueue;
        this->readyQueue = readyQueue;
        this->waitingQueue = waitingQueue;
        this->blockedQueue = blockedQueue;
        this->deadQueue = deadQueue;
        this->timePerTick = timePerTick;
        this->cyclesPerTick = cyclesPerTick;
        this->ticksElapsed = 0;
        this->totalProcesses = this->arrivalQueue->size();
    };

    void arrivalLoad(){
        Process *process = nullptr;
        Queue temp;
        if(!this->arrivalQueue->empty()){
            for(int i=this->arrivalQueue->size();i>0;i--){
                process = this->arrivalQueue->pop();
                if(process->getArrivalTime()<=this->ticksElapsed*this->timePerTick)
                    temp.push(process);
                else this->arrivalQueue->push(process);
            }
        }
        temp.sort(Process::processPriorityCmp);
        if(!temp.empty()){
            for(int i=temp.size();i>0;i--){
                process = temp.pop();
                this->readyQueue->push(process);
            }
        }
    }

    int getTicksElapsed(){
        return this->ticksElapsed;
    }

    void setTicksElapsed(int x){
        this->ticksElapsed = x;
    }

    bool completed(){
        return this->deadQueue->size()>=this->totalProcesses;
    }

    virtual void run() = 0; // A single tick
};


#endif
