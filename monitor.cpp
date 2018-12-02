#include "includes.hpp"
#include "shared.hpp"
#include "monitor.hpp"
#include "task.hpp"


void Monitor::add_task(class Task* task){
    this->tasks.push_back(task);
}

void Monitor::set_monitor_time(int monitor_time){
    this->monitor_time = monitor_time;
}

void Monitor::print_state(enum State state){
    printf("monitor: [%s] ", state_to_string(state).c_str());
    for (int i = 0; i < this->tasks.size(); i++){
        class Task task = *this->tasks[i];

        if (task.state == state){
            printf("%s ", task.name.c_str());
        }
    }
    printf("\n");
}

void *Monitor::print(void *arg){
    class Monitor *monitor = (Monitor *) arg;
    while(1){
        mutexes.lock_mutex(&mutexes.state_change_mutex);
        monitor->print_state(WAIT);
        monitor->print_state(RUN);
        monitor->print_state(IDLE);
        mutexes.unlock_mutex(&mutexes.state_change_mutex);
        usleep(monitor->monitor_time * 1000);
    }
}

void Monitor::execute(){
    int rval = pthread_create(&this->tid, NULL, this->print, this);
    if (rval) {
          perror("pthread_create failed");
          exit(1);
    }
}