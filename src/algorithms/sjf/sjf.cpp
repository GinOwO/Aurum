#include "sjf.h"    //Path: include/sjf.h

#include "process.h"    // Path: include/process.h
#include "queues.h"     // Path: include/queues.h
#include "basealg.h"    // Path: include/basealg.h
#include "ctexceptions.h"   // Path: include/ctexceptions.h

ShortestJobFirst::ShortestJobFirst(
    Queue* aq, Queue* rq, Queue* wq, Queue* bq, Queue* dq, int ttt, int ctt):
    BaseAlgorithm(aq, rq, wq, bq, dq, ttt, ctt) {
  }

bool ShorteestJobFirst::comparator(Process *p1, Process *p2) {
    return Process::processBurstCmp(p1, p2);
    }

void ShortestJobFirst::run() {
    if (completed()) throw ExecutionCompletedException();
    Process *process = nullptr;
    this->ticksElapsed++; 

    this->arrivalLoad();

    if (!blockedQueue->empty()) {
        process = blockedQueue->front();
        if (!process->updateFront(timePerTick)) {
            process->next();
            if (process->eof()) deadQueue->push(blockedQueue->pop());
            else readyQueue->push(blockedQueue->pop());
        }
        process = nullptr;
    }

    if (!waitingQueue->empty()) {
        for (int i = 0; i < waitingQueue->size(); i++) {
            process = waitingQueue->pop();
            if (!process->updateFront(timePerTick)) {
                process->next();
                if (process->eof()) deadQueue->push(process);
                else readyQueue->push(process);
            }
            else waitingQueue->push(process);
        }
        process = nullptr;
    }
        
    if (!this->readyQueue->empty()) {
        this->readyQueue->sort(comparator);  // Sort by burst time (shortest job first)
            
        process = readyQueue->front();
        std::pair<int,int> instr = process->peek();
        if (instr.first == 0) {
            if (instr.second == 0) {
                process->next();
                instr = process->peek();
            }
            else if (instr.second == 1) {
                deadQueue->push(readyQueue->pop());
            }
        }

        if (instr.first == 1) {
            if (!process->updateFront(cyclesPerTick)) {
                process->next();
                instr = process->peek();
            }
        }
        else if (instr.first == 2) blockedQueue->push(readyQueue->pop());
        else if (instr.first == 3) {
            waitingQueue->push(readyQueue->pop());
            waitingQueue->sort(Process::processWaitingCmp);
        }
        process = nullptr;
    }
}
