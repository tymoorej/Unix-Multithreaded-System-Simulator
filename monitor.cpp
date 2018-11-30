#include "includes.hpp"
#include "shared.hpp"
#include "monitor.hpp"
#include "task.hpp"


Monitor::Monitor(vector<class Task> tasks){
    for (int i = 0; i < tasks.size(); i++){
        this->tasks.push_back(&tasks[i]);
    }
}

Monitor::Monitor(){}