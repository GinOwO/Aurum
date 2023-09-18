#ifndef _AURUM_BASE_ALGORITHM_H
#define _AURUM_BASE_ALGORITHM_H 1

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h

#include<algorithm>

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
        if(!this->arrivalQueue->empty()){
            for(int i=0;i<this->arrivalQueue->size();i++){
                process = this->arrivalQueue->pop();
                if(process->getArrivalTime()<=this->ticksElapsed*this->timePerTick){
                    this->readyQueue->push(process);
                }
                else this->arrivalQueue->push(process);
            }
            process = nullptr;
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
