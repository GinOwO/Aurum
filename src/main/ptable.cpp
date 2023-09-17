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

std::string ProcessTable::viewProcess(int pid){
    std::string s, q; int i=1;
    auto P = this->getProcess(pid)->viewInstr();
    for(auto&[a,b]:P){
        q = std::to_string(i) + ". ";
        if(a==1) q+="CPU\t";
        else if(a==2) q+="IO\t";
        else if(a==3) q+="WAIT\t";
        else continue;
        q+=std::to_string(b)+"\n";
        s+=q;
        i++;
    }
    return s;
}

std::vector<int> ProcessTable::listProcesses(){
    std::vector<int> v;
    for(auto&[a,_]:table) v.push_back(a);
    return v;
}
