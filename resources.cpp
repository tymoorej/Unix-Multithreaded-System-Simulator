#include "includes.hpp"
#include "resources.hpp"

Resource::Resource(string name, int max_available){
    this->name = name;
    this->max_available = max_available;
    this->currently_available = max_available;
}

Resource::Resource(){
    this->name = "";
    this->max_available = -1;
    this->currently_available = -1;
}

void Resource::print(){
    printf("%s: (MaxAvail= %d, held= %d)\n",
    this->name.c_str(), this->max_available, this->max_available - this->currently_available);
}