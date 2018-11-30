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