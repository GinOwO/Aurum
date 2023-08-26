#include "program.h"
#include "ctexceptions.h"

#include<string>
#include<vector>
#include<cstdint>
#include<utility>

Program::Program(int _startTime,const std::string _name, int _priority){
    this->content = new std::vector<std::pair<int,int>>;
    this->ptr = 0;
    this->startTime = _startTime;
    this->name = _name;
    this->priority = _priority;
}

Program::~Program(){
    delete this->content;
}

Program* Program::clone(const Program* _program){
    Program* forkedProgram = new Program{this->startTime,this->name};
    forkedProgram->content = new std::vector<std::pair<int,int>>(*(_program->content));
    forkedProgram->ptr = _program->ptr;
    return forkedProgram;
}

void Program::load(int _type, int _resource){
    content->push_back({_type, _resource});
}

std::pair<int, int> Program::get(const size_t&n){
    if(n>=this->content->size() || n<0) throw OutOfBoundsException();
    return this->content->at(n);
}

std::pair<int,int> Program::next(){
    return this->get(ptr++);
}

void Program::seek(const int& offset,const int& anchor=0){
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

size_t Program::tell(){
    return this->ptr;
}

int Program::getStartTime(){
    return this->startTime;
}

int Program::getPriority(){
    return this->priority;
}

std::string Program::getName(){
    return this->name;
}

std::pair<int,int> Program::peek(){
    return this->get(ptr);
}

bool Program::arrivalCmp(Program* a, Program* b){
    return a->getStartTime()<b->getStartTime();
}