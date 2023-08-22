#include "scheduler.h"
#include "program.h"
#include "ctexceptions.h"
#include "process.h"

#include<regex>
#include<cctype>
#include<vector>
#include<string>
#include<fstream>

std::regex patStart(R"/(^STR_PROCESS\s\"([\w\s]+)\"\s(\d+)$)/");
std::regex patEnd(R"/(^END_PROCESS$)/");
std::regex validOP(R"/(^(CPU|IO|WAIT)\s(\d+)$)/");

/*
Input file must be of form:
STR_PROCESS "<string Name>" <int arrivalTime>
OP1 <resource taken>
OP2 <resource taken>
OP3 <resource taken>
..
..
..
OPn <resource taken>
END_PROCESS
PROCESS "<string Name>" <int arrivalTime>
OP1 <resource taken>
OP2 <resource taken>
..
..
..
etc

OPs         Resource Type(must be integer)
CPU         Cycles
IO          Time(in TU)
WAIT        Time(in TU)         
*/

Scheduler::Scheduler(const int& _cyclesPerTick, const int& _timeUnitsPerTick){
    this->cyclesPerTick = _cyclesPerTick;
    this->timeUnitsPerTick = _timeUnitsPerTick;
    this->idleTime=0;
    this->wastedCycles=0;
}

void Scheduler::reset(){
    this->arrivalQueue = std::queue<Process>();
    this->idleTime=0;
    this->wastedCycles=0;
}

void Scheduler::load(const std::string& _path){
    this->reset();
    Process::timeToTick = this->timeUnitsPerTick;
    Process::cyclesToTick = this->cyclesPerTick;

    this->arrivalQueue = std::queue<Process>();
    std::vector<Program*> programs;
    std::string s, name="unknown";
    std::smatch match;
    std::ifstream fd;
    int started=0, aTime;
    fd.open(_path);
    if(fd.fail()) throw FileException("cannot open file.");

    while(std::getline(fd,s,'\n')){
        if(!started && std::regex_match(s, match, patStart)){
            started=1;
            programs.push_back(new Program{
                std::stoi(match[2]),(name = match[1])});
        }
        else if(started && std::regex_match(s, match, validOP)){
            int _type;
            if(match[1]=="CPU") _type=1;
            else if(match[1]=="IO") _type=2;
            else if(match[1]=="WAIT") _type=3;
            programs[programs.size()-1]->load(_type,std::stoi(match[2]));
        }
        else if(started && std::regex_match(s, match, patEnd)){
            started=0;
            name = "unknown";
        }
        else throw FileException("Process"+name);
    }
    fd.close();
    
    int pid = 1000;
    std::sort(programs.begin(), programs.end(), [](Program* a, Program* b){return a->getStartTime()<b->getStartTime();});
    for(Program* c:programs){
        Process P(pid++,c->getName(),{c->getStartTime(),0,0,0,0});
        try{
            P.push({0,0}); // 0,0 = start
            while(1){
                P.push(c->peek());
                c->next();
            }
        }
        catch(OutOfBoundsException){
            P.push({0,1});
            arrivalQueue.push(P);
        }
        delete c;
    }
    return;
}