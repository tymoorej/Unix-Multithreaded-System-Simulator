#ifndef TASK_HEADER
#define TASK_HEADER

#include "includes.hpp"
#include "resources.hpp"
#include "shared.hpp"

struct Needed_Resource{
    struct Resource *resource;
    int amount_needed;
    int amount_held;

    Needed_Resource(struct Resource *resource, int amount_needed);
    Needed_Resource();
    void print();
};

class Task{
    public:
    enum State state;
    string name;
    int busy_time;
    int wait_time;
    int idle_time;
    int total_number_of_iterations;
    int iterations_completed;
    pthread_t tid;
    vector<struct Needed_Resource> needed_resources;

    Task(string name, int busy_time, int idle_time, int total_number_of_iterations);
    void print_final();
    void print_after_iteration();
};

#endif