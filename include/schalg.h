#ifndef _AURUM_SCHEDULING_ALGORITHMS_H
#define _AURUM_SCHEDULING_ALGORITHMS_H 1

#include "basealg.h"
#include "lrjt.h"
#include "srjt.h"
#include "rr.h"

#include<set>
#include<map>
#include<string>

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
