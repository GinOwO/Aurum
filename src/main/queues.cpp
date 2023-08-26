#include "queues.h"
#include "process.h"
#include "ctexceptions.h"

#include<vector>
#include<queue>
#include<algorithm>

Queue::Queue(){
    queue = std::vector<int>();
}

Queue::~Queue(){
    clear();
}

void Queue::push(int pid){
    queue.push_back(pid);
}

int Queue::pop(){
    if(empty()) throw ProcessDoesNotExistException();
    int pid = queue.front();
    queue.erase(queue.begin());
    return pid;
}

int Queue::front(){
    if(empty()) throw ProcessDoesNotExistException();
    return queue.front();
}

int Queue::size(){
    return queue.size();
}

bool Queue::empty(){
    return queue.empty();
}

void Queue::clear(){
    queue.clear();
}

std::vector<int> Queue::getQueue() const{
    return queue;
}
