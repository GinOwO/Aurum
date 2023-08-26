#ifndef _AURUM_PROGRAM_H
#define _AURUM_PROGRAM_H 1

#include <string>
#include <vector>
#include <cstdint>
#include <utility>

class Program{
private:
    std::string name;
    std::vector<std::pair<int,int>>* content;
    
    size_t ptr;
    int startTime;
    int priority;

public:
    Program(int=0, const std::string="", int=5);
    ~Program();
    Program* clone(const Program*);
    void load(int, int);

    int getStartTime();
    int getPriority();
    std::string getName();    
    std::pair<int, int> next();
    std::pair<int, int> get(const size_t &);
    std::pair<int, int> peek();

    size_t tell();
    void seek(const int &, const int &);
};

#endif