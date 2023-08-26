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

Process::Process(int _pid, std::string _name, 
        const std::vector<int>& _times, int _priority){
    this->ptr=0;
    this->pid=_pid;
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

Process* Process::fork(int _pid){
    Process* p = new Process(_pid, this->name, this->times);
    p->instructions = this->instructions;
    return p;
}