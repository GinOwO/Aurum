#ifndef AURUM_PROCESS_TABLE_H
#define AURUM_PROCESS_TABLE_H

#include "process.h"

#include <unordered_map>
#include <string>

class ProcessTable{
    std::unordered_map<int, Process*> table;
public:
    ProcessTable();
    ~ProcessTable();
    void insert(int, Process*);
    void kill(int);
    bool exists(int);
    void clear();
    Process* getProcess(int);

    ProcessTable fork();

    std::string viewProcess(int);
    std::vector<int> listProcesses();
};

#endif
