#include "mlfq.h"           // Path: include/mlfq.h

#include "process.h"        // Path: include/process.h
#include "queues.h"         // Path: include/queues.h
#include "basealg.h"        // Path: include/basealg.h
#include "ctexceptions.h"   // Path: include/ctexceptions.h


MultiLevelFeedbackQueue::MultiLevelFeedbackQueue(
    Queue* aq, Queue* rq, Queue* wq, Queue* bq, Queue* dq,
    int ttt,int ctt, Queue& q1, Queue& q2, Queue& q3) : Queue1(q1),
    BaseAlgorithm(aq, rq, wq, bq, dq, ttt, ctt), Queue2(q2), Queue3(q3){

}

bool MultiLevelFeedbackQueue::comparator(Process *p1, Process *p2){
    return Process::processPriorityCmp(p1, p2);
}

void MultiLevelFeedbackQueue::run(){
    if(completed()) throw ExecutionCompletedException();
    Process *process = nullptr;
    this->ticksElapsed++;

    [&](){
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
                this->Queue1.push(process);
                this->counts[process] = 0;
            }
        }
    }();

    if(!blockedQueue->empty()){
        process = blockedQueue->front();
        process->setWaitingTime(process->getWaitingTime()+timePerTick);
        if(!process->updateFront(1)){
            process->next();
            if(process->eof()) deadQueue->push(blockedQueue->pop());
            else{
                process = blockedQueue->pop();
                switch(this->counts[process]){
                case 0: this->Queue1.push(process); break;
                case 1: this->Queue2.push(process); break;
                default : this->Queue3.push(process);
                }
            }
        }
        process = nullptr;
    }

    if(!waitingQueue->empty()){
        for(int i=0;i<waitingQueue->size();i++){
            process = waitingQueue->pop();
            process->setWaitingTime(process->getWaitingTime()+timePerTick);
            if(!process->updateFront(1)){
                process->next();
                if(process->eof()) deadQueue->push(process);
                else{
                    switch(this->counts[process]){
                    case 0: this->Queue1.push(process); break;
                    case 1: this->Queue2.push(process); break;
                    default : this->Queue3.push(process);
                    }
                }
            }
            else waitingQueue->push(process);
        }
        process = nullptr;
    }

    auto fn = [&](Queue& que){
        process = que.front();
        std::pair<int,int> instr = process->peek();
        if(instr.first==0){
            if(instr.second==0){
                process->next();
                instr = process->peek();
            }
            else if(instr.second==1){
                deadQueue->push(que.pop());
            }
        }

        if(instr.first==1){
            if(!process->updateFront(1)){
                process->next();
                instr = process->peek();
            }
            int rt = process->getRunningTime();
            int ct = int(rt>=8) + int(rt>=24);
            if(ct!=this->counts[process]){
                this->counts[process]=ct;
                process = que.pop();
                switch(this->counts[process]){
                case 0: this->Queue1.push(process); break;
                case 1: this->Queue2.push(process); break;
                default: this->Queue3.push(process);
                }
            }
        }
        else if(instr.first==2){
            process = que.pop();
            this->counts[process]++;
            blockedQueue->push(process);
        }
        else if(instr.first==3){
            process = que.pop();
            this->counts[process]++;
            waitingQueue->push(process);
            waitingQueue->sort(Process::processWaitingCmp);
        }
    };

    if(!this->Queue1.empty()){
        process = this->Queue1.front();
        for(auto&c:this->Queue1.getQueue()){
            if(c!=process)
                c->setWaitingTime(c->getWaitingTime()+timePerTick);
        }
        for(auto&c:this->Queue2.getQueue())
            c->setWaitingTime(c->getWaitingTime()+timePerTick);
        for(auto&c:this->Queue3.getQueue())
            c->setWaitingTime(c->getWaitingTime()+timePerTick);
        fn(Queue1);
    }
    else if(!this->Queue2.empty()) {
        process = this->Queue2.front();
        for(auto&c:this->Queue2.getQueue()){
            if(c!=process)
                c->setWaitingTime(c->getWaitingTime()+timePerTick);
        }
        for(auto&c:this->Queue3.getQueue())
            c->setWaitingTime(c->getWaitingTime()+timePerTick);
        fn(Queue2);
    }
    else{
        process = this->Queue3.front();
        for(auto&c:this->Queue3.getQueue()){
            if(c!=process)
                c->setWaitingTime(c->getWaitingTime()+timePerTick);
        }
        fn(Queue3);
    }
}
