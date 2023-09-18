#include "process.h"
#include "ctexceptions.h"

#include<utility>
#include<string>
#include<vector>
#include<cmath>

int Process::timeToTick = 0;
int Process::cyclesToTick = 0;
void Process::kill(Process* p){
    delete p;
}

Process::Process(std::string _name, int _at, int _bt, int _wt, int _priority){
    this->ptr=0;
    this->name=_name;
    this->arrivalTime=_at;
    this->burstTime=_bt;
    this->waitingTime=_wt;
    this->priority=_priority;
}

void Process::push(const std::pair<int,int>& instr){
    int ttt = Process::timeToTick;
    int ctt = Process::cyclesToTick;
    double q=instr.second;
    if(ttt<1) ttt=1;
    if(ctt<1) ctt=1;
    if(instr.first==1) q = ceil(q/ctt);
    else if(instr.first>1) q = ceil(q/ttt);
    this->instructions.push_back({instr.first, q});
}

std::vector<std::pair<int,int>> Process::viewInstr() const{
    return this->instructions;
}

std::pair<int,int> Process::next(){
    if(eof()) throw EndOfFileException();
    return this->instructions[ptr++];
}

std::pair<int,int> Process::peek(){
    if(eof()) throw EndOfFileException();
    return this->instructions[ptr];
}

int Process::updateFront(int t){
    if(eof()) throw EndOfFileException();
    this->instructions[ptr].second=std::max(
        this->instructions[ptr].second-t, 0
    );
    this->burstTime=std::max(this->burstTime-t, 0);
    return this->instructions[ptr].second;
}

Process* Process::fork(){
    Process* p = new Process(this->name, this->arrivalTime, 
        this->burstTime, this->waitingTime, this->priority);
    p->ptr = this->ptr;
    p->instructions = this->instructions;
    p->pid = this->pid;
    return p;
}

int Process::getPriority() const{
    return this->priority;
}

int Process::getArrivalTime() const{
    return this->arrivalTime;
}

bool Process::eof() const{
    return this->ptr>this->instructions.size() || this->instructions.size()==0;
}

int Process::getBurstTime() const{
    return this->burstTime;
}

int Process::getWaitingTime() const{
    return this->waitingTime;
}

int Process::getPID() const{
    return this->pid;
}

void Process::setPriority(int _priority){
    this->priority=_priority;
}

void Process::setArrivalTime(int _arrivalTime){
    this->arrivalTime=_arrivalTime;
}

void Process::setBurstTime(int _burstTime){
    this->burstTime=_burstTime;
}

void Process::setWaitingTime(int _waitingTime){
    this->waitingTime=_waitingTime;
}

void Process::setPID(int _pid){
    this->pid=_pid;
}

std::string Process::getName() const{
    return this->name;
}

// Comparators
bool Process::processNameCmp(Process* a, Process* b){
    return a->name<b->name;
}

bool Process::processArrivalCmp(Process* a, Process* b){
    return a->getArrivalTime()<b->getArrivalTime() ||
        (a->getArrivalTime()==b->getArrivalTime()&&Process::processNameCmp(a,b));
}

bool Process::processPriorityCmp(Process* a, Process* b){
    return a->getPriority()<b->getPriority() ||
        (a->getPriority()==b->getPriority()&&Process::processArrivalCmp(a,b));
}

bool Process::processBurstCmp(Process* a, Process* b){
    return a->getBurstTime()<b->getBurstTime() ||
        (a->getBurstTime()==b->getBurstTime()&&Process::processArrivalCmp(a,b));
}

bool Process::processWaitingCmp(Process* a, Process* b){
    return a->getWaitingTime()<b->getWaitingTime() ||
        (a->getWaitingTime()==b->getWaitingTime()&&Process::processArrivalCmp(a,b));
}

// End of Comparators
