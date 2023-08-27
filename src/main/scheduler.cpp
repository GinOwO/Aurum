#include "scheduler.h"

#include "ctexceptions.h"
#include "program.h"
#include "process.h"
#include "queues.h"
#include "ptable.h"
#include "schalg.h"

#include<iostream>
#include<regex>
#include<cctype>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>

std::regex patStart(R"/(^STR_PROCESS\s\"([\w\s]+)\"\s(\d+)\s(\d+)$)/");
std::regex patEnd(R"/(^END_PROCESS$)/");
std::regex validOP(R"/(^(CPU|IO|WAIT)\s(\d+)$)/");

/*
Input file must be of form:
STR_PROCESS "<string Name>" <int arrivalTime> <priority>
OP1 <resource taken>
OP2 <resource taken>
OP3 <resource taken>
..
..
..
OPn <resource taken>
END_PROCESS
PROCESS "<string Name>" <int arrivalTime> <priority>
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
PRIORITY    Optional, lower is higher priority
*/

int Scheduler::pid = 1000;

Scheduler::Scheduler(const int& _cyclesPerTick, const int& _timeUnitsPerTick){
    this->processTable = ProcessTable();
    this->cyclesPerTick = _cyclesPerTick;
    this->timeUnitsPerTick = _timeUnitsPerTick;
    this->idleTime=0;
    this->wastedCycles=0;
    this->algorithmID=0;
    this->algorithm = nullptr;
    this->arrivalQueue = Queue();
    this->readyQueue = Queue();
    this->waitingQueue = Queue();
    this->blockedQueue = Queue();
    this->deadQueue = Queue();
    this->ganttChart = std::map<int, int>();
}

void Scheduler::reset(){
    this->arrivalQueue.clear();
    this->idleTime=0;
    this->wastedCycles=0;
}

void Scheduler::load(const std::string& _path){
    this->reset();
    Process::timeToTick = this->timeUnitsPerTick;
    Process::cyclesToTick = this->cyclesPerTick;

    this->arrivalQueue = Queue();
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
                std::stoi(match[2]),(name = match[1]),std::stoi(match[3])});
        }
        else if(started && std::regex_match(s, match, validOP)){
            int _type;
            if(match[1]=="CPU") _type=1;
            else if(match[1]=="IO") _type=2;
            else if(match[1]=="WAIT") _type=3;
            programs[programs.size()-1]->load(_type,std::stoi(match[2]));
        }
        else if(started && std::regex_match(s, match, patEnd)){
            started = 0;
            name = "unknown";
        }
        else throw FileException("Process"+name);
    }
    fd.close();
    
    int prev=0, ticks=0;
    double _time=0;
    for(Program* c:programs){
        Process* P = new Process(c->getName(),c->getStartTime(),0,0,c->getPriority());
        try{
            P->push({0,0}); // 0,0 = start
            while(1){
                int tt = 1;
                if(c->peek().first==1) tt = this->cyclesPerTick;
                else if(c->peek().first>1) tt = this->timeUnitsPerTick;
                if(c->peek().first==prev){
                    _time+=ceil(c->peek().second/tt);
                }
                else{
                    prev=c->peek().first;
                    ticks+=_time;
                    _time=ceil(c->peek().second/tt);
                }
                P->push(c->peek());
                c->next();
            }
        }
        catch(OutOfBoundsException){
            P->push({0,1}); // 0,1 = end
            P->setBurstTime(ticks);
            ticks = 0;
            this->arrivalQueue.push(P);
            P->setPID(Scheduler::pid);
            this->processTable.insert(Scheduler::pid++, P);
        }
        delete c;
    }
    this->arrivalQueue.sort();
    return;
}

void Scheduler::selectAlgorithm(const std::string& name){
    if(!availableAlgorithms.count(name))
        throw UnavailableAlgorithmException(name);
    if(name=="Longest Remaining Job First"){
        this->algorithmID = 1;
        this->algorithm = new LongestRemainingJobFirst(&this->arrivalQueue,
            &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }/*
    else if(name=="Shortest Job First"){
        this->algorithmID = 2;
        this->algorithm = new ShortestJobFirst(
            &this->arrivalQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="First Come First Serve"){
        this->algorithmID = 3;
        this->algorithm = new FirstComeFirstServe(
            &this->arrivalQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="Round Robin"){
        this->algorithmID = 4;
        this->algorithm = new RoundRobin(
            &this->arrivalQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="Priority"){
        this->algorithmID = 5;
        this->algorithm = new Priority(
            &this->arrivalQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    */
    
}

void Scheduler::simulate(){
    if(!this->algorithm) throw FatalException();
    while(1){
        try{
            this->algorithm->run();
            
            if(!readyQueue.empty()){
                if(!ganttChart.size()) ganttChart[this->algorithm->getTicksElapsed()]=readyQueue.front()->getPID();
                else if(ganttChart.rbegin()->second!=readyQueue.front()->getPID())
                    ganttChart[this->algorithm->getTicksElapsed()]=readyQueue.front()->getPID();
            }
            else this->idleTime++;
        }
        catch(ExecutionCompletedException){
            std::cout << "Execution Completed.\n";
            break;
        }
    }
    for(auto&c:ganttChart) std::cout << c.first << "\t";
    std::cout << '\n';
    for(auto&c:ganttChart) std::cout << c.second << "\t";
    std::cout << '\n';
}


// TODO REMOVE THIS
void Scheduler::dispState(){
    std::cout << "Ticks Elapsed:"<< this->algorithm->getTicksElapsed() <<"\nArrival Queue:";
    for(auto&c:arrivalQueue.getQueue()) std::cout << c->getName() << " ";
    std::cout << "\nReady Queue:";
    for(auto&c:readyQueue.getQueue()) std::cout << c->getName() << " ";
    std::cout << "\nWaiting Queue:";
    for(auto&c:waitingQueue.getQueue()) std::cout << c->getName() << " ";
    std::cout << "\nBlocked Queue:";
    for(auto&c:blockedQueue.getQueue()) std::cout << c->getName() << " ";
    std::cout << "\nDead Queue:";
    for(auto&c:deadQueue.getQueue()) std::cout << c->getName() << " ";
    std::cout << "\n\n";
}