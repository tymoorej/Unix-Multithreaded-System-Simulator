#include "includes.hpp"
#include "shared.hpp"
#include "monitor.hpp"
#include "task.hpp"


Monitor::Monitor(){}
void Monitor::add_task(class Task* task){
    this->tasks.push_back(task);
}

void Monitor::print(){
    printf("monitor: [WAIT] ");
    for (int i = 0; i < this->tasks.size(); i++){
        class Task task = *tasks[i];

        if (task.state == WAIT){
            printf("%s ", task.name.c_str());
        }
    }
    printf("\n");
}