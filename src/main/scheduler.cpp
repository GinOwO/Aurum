#include "scheduler.h"

#include "ctexceptions.h"
#include "program.h"
#include "process.h"
#include "queues.h"
#include "ptable.h"
#include "schalg.h"

#include <sstream>
#include <regex>
#include <cctype>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#include <QFile>
#include <QTextStream>

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
    this->timeQuantum=2;
    this->algorithm = nullptr;
    this->arrivalQueue = Queue();
    this->readyQueue = Queue();
    this->waitingQueue = Queue();
    this->blockedQueue = Queue();
    this->deadQueue = Queue();
    this->ganttChart = std::vector<std::pair<int, int>>();
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
    std::string s, name = "unknown";
    std::smatch match;
    QFile fd(QString::fromStdString(_path));
    int started = 0, aTime;

    if (!fd.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileException("Cannot open file.");
    }

    QTextStream in(&fd);

    while (!in.atEnd()) {
        s = in.readLine().toStdString();
        if (!started && std::regex_match(s, match, patStart)) {
            started = 1;
            programs.push_back(new Program{
                                           std::stoi(match[2]), (name = match[1]), std::stoi(match[3]) });
        }
        else if (started && std::regex_match(s, match, validOP)) {
            int _type;
            if (match[1] == "CPU") _type = 1;
            else if (match[1] == "IO") _type = 2;
            else if (match[1] == "WAIT") _type = 3;
            programs[programs.size() - 1]->load(_type, std::stoi(match[2]));
        }
        else if (started && std::regex_match(s, match, patEnd)) {
            started = 0;
            name = "unknown";
        }
        else throw FileException("Process" + name);
    }

    fd.close();
    
    int prev=0, ticks=0;
    for(Program* c:programs){
        Process* P = new Process(c->getName(),c->getStartTime(),0,0,c->getPriority());
        try{
            P->push({0,0}); // 0,0 = start
            while(1){
                int tt = 1;
                if(c->peek().first==1) tt = this->cyclesPerTick;
                else if(c->peek().first>1) tt = this->timeUnitsPerTick;
                ticks+=ceil(c->peek().second/tt);
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
}

void Scheduler::selectAlgorithm(const std::string& name){
    if(!availableAlgorithms.count(name))
        throw UnavailableAlgorithmException(name);
    if(this->arrivalQueue.empty())
        throw InvalidInputException();
    if(name=="Longest Remaining Job First"){
        this->algorithmID = 1;
        this->algorithm = new LongestRemainingJobFirst(&this->arrivalQueue,
            &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="Shortest Remaining Job First"){
        this->algorithmID = 2;
        this->algorithm = new ShortestRemainingJobFirst(
            &this->arrivalQueue, &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="First Come First Serve"){
        this->algorithmID = 3;
        this->algorithm = new FirstComeFirstServe(&this->arrivalQueue,
          &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
          &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    else if(name=="Round Robin"){
        this->algorithmID = 4;
        this->algorithm = new RoundRobin(
            &this->arrivalQueue, &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick, this->timeQuantum);
    }
    else if(name=="Priority Algorithm"){
        this->algorithmID = 5;
        this->algorithm = new PriorityAlgorithm(&this->arrivalQueue,
            &this->readyQueue, &this->waitingQueue, &this->blockedQueue,
            &this->deadQueue, this->timeUnitsPerTick, this->cyclesPerTick);
    }
    
}

State Scheduler::getState(){
    State state;
    state.ticksElapsed = this->algorithm->getTicksElapsed();
    state.idleTime = this->idleTime;
    state.wastedCycles = this->wastedCycles;
    state.arrivalQueue = this->arrivalQueue.cloneQueue();
    state.readyQueue = this->readyQueue.cloneQueue();
    state.waitingQueue = this->waitingQueue.cloneQueue();
    state.deadQueue = this->deadQueue.cloneQueue();
    state.blockedQueue = this->blockedQueue.cloneQueue();
    state.ganttChart = std::vector<std::pair<int,int>>(this->ganttChart);
    return state;
}

void Scheduler::setState(State state){
    this->algorithm->setTicksElapsed(state.ticksElapsed);
    this->idleTime = state.idleTime;
    this->wastedCycles = state.wastedCycles;
    this->arrivalQueue = state.arrivalQueue;
    this->readyQueue = state.readyQueue;
    this->waitingQueue = state.waitingQueue;
    this->deadQueue = state.deadQueue;
    this->blockedQueue = state.blockedQueue;
    this->ganttChart = state.ganttChart;
}

void Scheduler::nextTick(){
    if(!this->algorithm) throw FatalException();
    this->algorithm->run();
    if(!readyQueue.empty()){
        if(!ganttChart.size() || ganttChart.rbegin()->second!=readyQueue.front()->getPID())
            ganttChart.push_back({this->algorithm->getTicksElapsed(),readyQueue.front()->getPID()});
    }
    else{
        this->idleTime++;
        this->wastedCycles+=cyclesPerTick;
        if(!ganttChart.size() || ganttChart.rbegin()->second!=-1)
            ganttChart.push_back({this->algorithm->getTicksElapsed(),-1});
    }
}

Process* Scheduler::fork(int pid){
    auto p = this->processTable.getProcess(pid)->fork();
    p->setPID(Scheduler::pid);
    this->processTable.insert(Scheduler::pid++,p);
    return p;
}

bool Scheduler::isCompleted(){
    return this->algorithm != nullptr && this->algorithm->completed();
}

std::string Scheduler::getAlgorithmName() const{
    if(this->algorithmID<1)
        throw UnavailableAlgorithmException("Alg Not Selected");
    return availableAlgorithmsMap.at(this->algorithmID);
}

std::string Scheduler::logging() const{
    std::stringstream ss;
    ss << "Ticks Elapsed:     " << this->algorithm->getTicksElapsed() << "\nArrival Queue:     ";
    for(auto&c:arrivalQueue.getQueue()) ss << c->getPID() << "  ";
    ss << "\nReady Queue:      ";
    for(auto&c:readyQueue.getQueue()) ss << c->getPID() << "  ";
    ss << "\nWaiting Queue:  ";
    for(auto&c:waitingQueue.getQueue()) ss << c->getPID() << "  ";
    ss << "\nBlocked Queue:  ";
    for(auto&c:blockedQueue.getQueue()) ss << c->getPID() << "  ";
    ss << "\nDead Queue:       ";
    for(auto&c:deadQueue.getQueue()) ss << c->getPID() << "  ";
    ss << "\n\n";
    return ss.str();
}
