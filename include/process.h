#include <string>
#include <vector>
#include <cstdint>

#ifndef _SCHV_PROCESS_H
#define _SCHV_PROCESS_H 1

class Process{
private:
    std::vector<std::string>* content;
    size_t ptr;
    int pid;

public:
    Process(int);
    ~Process();
    Process* fork(const Process*);
    static Process* load(const std::string&);
    
    std::string next();
    std::string get(const size_t &);

    size_t tell();
    void seek(const int &, const int &);
    void setPID(const int&);
    int getPID();

};

// TODO

class ProcessBlock{
private:
    Process* pid;
};

#endif