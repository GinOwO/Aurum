#include "process.h"
#include "ctexceptions.h"

#include<utility>
#include<string>
#include<vector>

int Process::timeToTick = 0;
int Process::cyclesToTick = 0;
void Process::kill(Process* p){
    delete p;
}

Process::Process(std::string _name, 
        const std::vector<int>& _times, int _priority){
    this->ptr=0;
    this->name=_name;
    this->times=std::vector<int>(_times);
    this->priority=_priority;
}

void Process::push(const std::pair<int,int>& instr){
    int ttt = Process::timeToTick;
    int ctt = Process::cyclesToTick;
    int q=instr.second;
    if(ttt<1) ttt=1;
    if(ctt<1) ctt=1;
    if(instr.first==1) q /= ctt;
    else if(instr.first>1) q/= ttt;
    instructions.push_back({instr.first, q});
}

std::pair<int,int> Process::next(){
    if(ptr>=instructions.size()) throw EndOfFileException();
    return this->instructions[ptr++];
}

Process* Process::fork(){
    Process* p = new Process(this->name, this->times);
    p->instructions = this->instructions;
    p->priority = this->priority;
    return p;
}

int Process::getPriority() const{
    return this->priority;
}

int Process::getArrivalTime() const{
    return this->times[0];
}

int Process::getBurstTime() const{
    return this->times[1];
}

int Process::getWaitingTime() const{
    return this->times[2];
}

int Process::getTurnaroundTime() const{
    return this->times[3];
}

int Process::getResponseTime() const{
    return this->times[4];
}
