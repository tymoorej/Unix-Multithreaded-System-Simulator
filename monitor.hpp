#ifndef MONITOR_HEADER
#define MONITOR_HEADER

#include "includes.hpp"
#include "shared.hpp"

class Monitor{
    vector<class Task*> tasks;

    public:
    Monitor();
    void add_task(class Task* task);
    void print();

};

#endif