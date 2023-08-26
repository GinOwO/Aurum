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

    virtual void run() = 0; // A single tick
};


#endif