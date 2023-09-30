#ifndef AURUM_SCHEDULING_ALGORITHMS_H
#define AURUM_SCHEDULING_ALGORITHMS_H

#include "basealg.h"
#include "lrjf.h"
#include "srjf.h"
#include "rr.h"

#include <set>
#include <map>
#include <string>

const std::map<int,std::string> availableAlgorithmsMap = {
    {1,"Longest Remaining Job First"},
    {2,"Shortest Remaining Job First"},
    {4,"Round Robin"},
};

const std::set<std::string> availableAlgorithms = [](){
    std::set<std::string> st;
    for(auto&[_,b]:availableAlgorithmsMap) st.insert(b);
    return st;
}();

#endif
