#ifndef AURUM_SCHEDULING_ALGORITHMS_H
#define AURUM_SCHEDULING_ALGORITHMS_H

#include "basealg.h"
#include "lrjf.h"
#include "srjf.h"
#include "fcfs.h"
#include "priority.h"
#include "rr.h"
#include "mlfq.h"

#include <set>
#include <map>
#include <string>

const std::map<int,std::string> availableAlgorithmsMap = {
    {1,"Longest Remaining Job First"},
    {2,"Shortest Remaining Job First"},
    {3,"First Come First Serve"},
    {4,"Round Robin"},
    {5,"Priority Algorithm"},
    {6,"Multi Level Feedback Queue"}
};

const std::set<std::string> availableAlgorithms = [](){
    std::set<std::string> st;
    for(auto&[_,b]:availableAlgorithmsMap) st.insert(b);
    return st;
}();

#endif
