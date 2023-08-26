#include<iostream>
#include "scheduler.h"

int main(int argc, char const *argv[]){
    Scheduler a{100,1};
    a.load("./test.txt");
    a.selectAlgorithm("Longest Remaining Job First");
    a.simulate();
    return 0;
}
