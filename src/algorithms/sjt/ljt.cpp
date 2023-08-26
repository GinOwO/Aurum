#include "ljt.h"        // Path: include/ljt.h

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h
#include "basealg.h"    // Path: include/basealg.h

LongestJobFirst::LongestJobFirst(
    Queue* aq, Queue* rq, Queue* wq, Queue* bq, Queue* dq, int ttt,int ctt):
    BaseAlgorithm(aq, rq, wq, bq, dq, ttt, ctt){

}

bool LongestJobFirst::comparator(Process *p1, Process *p2){
    return !Process::processBurstCmp(p1, p2);
}

void LongestJobFirst::run(){
    bool rpopped = 0;
    Process *process = nullptr;
    this->ticksElapsed++; 

    this->arrivalLoad();

    if(!this->readyQueue->empty()){
        process = readyQueue->front();
        std::pair<int,int> instr = process->peek();
        if(instr.first==0){
            if(instr.second==0){
                process->next();
                instr = process->peek();
            }
            else{
                rpopped = 1;
            }
        }

        if(instr.first==1){
            if(!process->updateFront(cyclesPerTick)){
                process->next();
                instr = process->peek();
            }
        }
        if(instr.first==2) blockedQueue->push(readyQueue->pop());
        if(instr.first==3){
            waitingQueue->push(readyQueue->pop());
            waitingQueue->sort(Process::processWaitingCmp);
        }
        process = nullptr;
    }

    if(!blockedQueue->empty()){
        if(rpopped>=waitingQueue->size()){
            process = blockedQueue->front();
            if(!process->updateFront(timePerTick)){
                process->next();
                if(process->eof()) deadQueue->push(blockedQueue->pop());
                else readyQueue->push(blockedQueue->pop());
            }
            process = nullptr;
        }
    }

    if(!waitingQueue->empty()){
        for(int i=0;i+rpopped<waitingQueue->size();i++){
            process = waitingQueue->pop();
            if(!process->updateFront(timePerTick)){
                process->next();
                if(process->eof()) deadQueue->push(waitingQueue->pop());
                else readyQueue->push(waitingQueue->pop());
            }
            else waitingQueue->push(process);
        }
        process = nullptr;
    }

    if(rpopped) readyQueue->sort(comparator);
}