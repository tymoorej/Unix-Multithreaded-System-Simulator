#ifndef SHARED_HEADER
#define SHARED_HEADER

#include "includes.hpp"

enum State {WAIT, RUN, IDLE};

extern long int start_time;

long int get_current_time();

string state_to_string(enum State s);

#endif