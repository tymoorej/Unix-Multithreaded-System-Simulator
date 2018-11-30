#include "includes.hpp"
#include "task.hpp"
#include "shared.hpp"
#include "resources.hpp"



Task::Task(string name, int busy_time, int idle_time, int total_number_of_iterations){
    this->state = WAIT;
    this->name = name;
    this->busy_time = busy_time;
    this->wait_time = 0;
    this->idle_time = idle_time;
    this->total_number_of_iterations = total_number_of_iterations;
    this->iterations_completed = 0;
    this->tid = -1;
}

void Task::print_final(){
    printf("%s (%s, runTime= %d msec, idleTime= %d msec):\n",
    this->name.c_str(), state_to_string(this->state).c_str(), this->busy_time, this->idle_time);
    cout << "\t(tid= " << this->tid << ")" << endl;

    for (int i = 0; i < needed_resources.size(); i++){
        cout << "\t";
        needed_resources[i].print();
    }

    printf("\t(RUN: %d times, WAIT: %d msec)\n", this->iterations_completed, this->wait_time);
}

void Task::print_after_iteration(){
    printf("task: %s (tid= ",this->name.c_str());
    cout << this->tid;
    printf(", iter= %d, time= %d msec)\n", this->iterations_completed, int(get_current_time() - start_time));

}

void Task::add_needed_resource(struct Needed_Resource needed_resource){
    this->needed_resources.push_back(needed_resource);
}

Needed_Resource::Needed_Resource(struct Resource *resource, int amount_needed){
    this->resource = resource;
    this->amount_needed = amount_needed;
    this->amount_held = 0;
}

Needed_Resource::Needed_Resource(){
    this->resource = new Resource();
    this->amount_needed = -1;
    this->amount_held = 0;
}

void Needed_Resource::print(){
    printf("%s: (needed= %d, held= %d)\n",
    this->resource->name.c_str(), this->amount_needed, this->amount_held);
}