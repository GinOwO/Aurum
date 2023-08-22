#include<iostream>
#include "scheduler.h"

int main(int argc, char const *argv[]){
    Scheduler a{1,10};
    a.load("./test.txt");
    return 0;
}
