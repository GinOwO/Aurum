#ifndef _AURUM_SCHEDULING_ALGORITHMS_H
#define _AURUM_SCHEDULING_ALGORITHMS_H 1

#include "basealg.h"
#include "lrjt.h"
#include "srjt.h"
#include "rr.h"

#include<set>
#include<string>

const std::set<std::string> availableAlgorithms = {
    "Longest Remaining Job First", // id: 1
    "Shortest Remaining Job First", // id: 2
    "Round Robin", // id: 4
};

#endif
