#ifndef MONITOR_HEADER
#define MONITOR_HEADER

#include "includes.hpp"
#include "shared.hpp"

class Monitor{
    vector<class Task*> tasks;

    public:
    Monitor(vector<class Task> tasks);
    Monitor();
};

#endif