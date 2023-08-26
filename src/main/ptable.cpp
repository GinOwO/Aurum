#include "ptable.h"

#include "process.h"
#include "ctexceptions.h"

#include<unordered_map>

ProcessTable::ProcessTable(){
    table = std::unordered_map<int, Process*>();
}

ProcessTable::~ProcessTable(){
    clear();
}

void ProcessTable::insert(int _pid, Process* p){
    if(exists(_pid)) this->kill(_pid);
    table[_pid] = p;
}

void ProcessTable::kill(int pid){
    if(!exists(pid)) throw ProcessDoesNotExistException();
    delete table[pid];
    table.erase(pid);
}

bool ProcessTable::exists(int pid){
    return table.count(pid);
}

Process* ProcessTable::getProcess(int pid){
    if(!exists(pid))
        throw ProcessDoesNotExistException();
    return table[pid];
}

void ProcessTable::clear(){
    std::vector<int> tmp;
    for(auto& process: table) tmp.push_back(process.first);
    for(auto& pid: tmp) kill(pid);
}