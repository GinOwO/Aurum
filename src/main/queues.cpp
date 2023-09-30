#include "queues.h"
#include "process.h"
#include "ctexceptions.h"

#include <vector>
#include <queue>
#include <algorithm>

Queue::Queue(){
    queue = std::vector<Process*>();
}

Queue::~Queue(){
    clear();
}

void Queue::push(Process* pid){
    queue.push_back(pid);
}

Process* Queue::pop(){
    if(empty()) throw ProcessDoesNotExistException();
    Process* pid = queue.front();
    queue.erase(queue.begin());
    return pid;
}

Process* Queue::front(){
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

std::vector<Process*> Queue::getQueue() const{
    return queue;
}

Queue Queue::cloneQueue(){
    Queue q;
    for(auto&c:queue) q.push(c->fork());
    return q;
}

void Queue::sort(bool (*cmp)(Process*, Process*)){
    std::sort(queue.begin(), queue.end(), cmp);
}
