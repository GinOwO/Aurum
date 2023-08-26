#ifndef _SCHV_PROGRAM_H
#define _SCHV_PROGRAM_H 1

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

public:
    Program(int, const std::string);
    ~Program();
    Program* clone(const Program*);
    void load(int, int);

    int getStartTime();
    std::string getName();    
    std::pair<int, int> next();
    std::pair<int, int> get(const size_t &);
    std::pair<int, int> peek();

    size_t tell();
    void seek(const int &, const int &);
};

#endif