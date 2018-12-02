#include "includes.hpp"
#include "shared.hpp"

long int get_current_time(){
    struct timeval t;
    gettimeofday(&t, NULL);
    long int milli = t.tv_sec * 1000 + t.tv_usec / 1000;
    return milli;
}

string state_to_string(enum State s){
    if (s == WAIT){
        return "WAIT";
    }
    if (s == RUN){
        return "RUN";
    }
    if (s == IDLE){
        return "IDLE";
    }
    return "";
}

void Mutexes::initialize_mutexes(){
    this->initalize_mutex(&this->state_change_mutex);
}

void Mutexes::initalize_mutex(pthread_mutex_t* mutex){
    int rval = pthread_mutex_init(mutex, NULL);
    if (rval){
        perror("mutex initiliazation failed");
        exit(1); 
    }
}

void Mutexes::lock_mutex(pthread_mutex_t* mutex){
    int rval = pthread_mutex_lock(mutex);
    if (rval){
        perror("mutex locking failed");
        exit(1); 
    }
}    

void Mutexes::unlock_mutex(pthread_mutex_t* mutex){
    int rval = pthread_mutex_unlock(mutex);
    if (rval){
        perror("mutex unlocking failed");
        exit(1); 
    }
}