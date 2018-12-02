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

void Task::execute(){
    int rval = pthread_create(&this->tid, NULL, this->task_handler, this);
    if (rval) {
          perror("pthread_create failed");
          exit(1);
    }
}

bool Task::can_aquire_resources_needed(){
    for (int i = 0; i < needed_resources.size(); i++){
        struct Needed_Resource *needed_resource = &needed_resources[i];
        struct Resource *resource = needed_resource->resource;
        if (resource->currently_available < needed_resource->amount_needed){
            return false;
        }
    }
    return true;
}

void Task::aquire_resources_needed(){
    for (int i = 0; i < needed_resources.size(); i++){
        struct Needed_Resource *needed_resource = &needed_resources[i];
        struct Resource *resource = needed_resource->resource;
        if (resource->currently_available < needed_resource->amount_needed){
            cout << "Error: Resource vanished unexpectidley" << endl;
            exit(0);
        }
        needed_resource->amount_held += needed_resource->amount_needed;
        resource->currently_available -= needed_resource->amount_needed;
    }
}

void Task::release_resources(){
    for (int i = 0; i < needed_resources.size(); i++){
        struct Needed_Resource *needed_resource = &needed_resources[i];
        struct Resource *resource = needed_resource->resource;
        resource->currently_available += needed_resource->amount_held;
        needed_resource->amount_held = 0;
    }
}

void Task::run(){
    usleep(this->busy_time * 1000);

    mutexes.lock_mutex(&mutexes.resources_mutex);
    this->release_resources();
    mutexes.unlock_mutex(&mutexes.resources_mutex);

    mutexes.lock_mutex(&mutexes.printing_mutex);
    this->print_after_iteration();
    this->state = IDLE;
    mutexes.unlock_mutex(&mutexes.printing_mutex);
}

void *Task::task_handler(void *arg){
    class Task *task = (Task *) arg;
    while(1){
        mutexes.lock_mutex(&mutexes.resources_mutex);
        if (!task->can_aquire_resources_needed()){
            mutexes.unlock_mutex(&mutexes.resources_mutex);

            mutexes.lock_mutex(&mutexes.printing_mutex);
            task->state = WAIT;
            mutexes.unlock_mutex(&mutexes.printing_mutex);
            task->wait_time += 10;
            usleep(10 * 1000); // 10ms
            continue;
        }
        
        task->aquire_resources_needed();
        mutexes.unlock_mutex(&mutexes.resources_mutex);

        mutexes.lock_mutex(&mutexes.printing_mutex);
        task->state = RUN;
        mutexes.unlock_mutex(&mutexes.printing_mutex);

        task->run();

        usleep(task->idle_time * 1000);
        task->iterations_completed++;

        if (task->iterations_completed >= task->total_number_of_iterations){
            void * value_pointer;
            pthread_exit(value_pointer);
        }
    }
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