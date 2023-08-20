#include "process.h"

#include "ctexceptions.h"

#include<string>
#include<vector>
#include<cstdint>
#include<fstream>

Process::Process(int _pid=0){
    this->content = new std::vector<std::string>;
    this->ptr = 0;
}

Process::~Process(){
    delete this->content;
}

Process* Process::fork(const Process* _process){
    Process* forkedProcess = new Process;
    forkedProcess->content = new std::vector<std::string>(*(_process->content));
    forkedProcess->ptr = _process->ptr;
    return forkedProcess;
}

Process* Process::load(const std::string& path){
    Process* _process = new Process;
    std::ifstream fd; 
    std::string s;
    fd.open(path);
    while(!fd.eof()){
        std::getline(fd, s,'\n');
        _process->content->push_back(s);
    }
    return _process;
}

std::string Process::get(const size_t&n){
    if(n>=this->content->size()) throw OutOfBoundsException();
    return (n<content->size())?content->at(n):"";
}

std::string Process::next(){
    return this->get(ptr++);
}

void Process::seek(const int& offset,const int& anchor=0){
    int idx;
    switch(anchor){
        case 0: idx=offset; break;
        case 1: idx=this->ptr+offset; break;
        case 2: idx=this->content->size()-offset; break;
        default: return;
    }
    if(idx<0 || idx>=this->content->size()) throw OutOfBoundsException();
    this->ptr=idx;
}

size_t Process::tell(){
    return this->ptr;
}

void Process::setPID(const int& _pid){
    this->pid = _pid;
}

int Process::getPID(){
    return this->pid;
}