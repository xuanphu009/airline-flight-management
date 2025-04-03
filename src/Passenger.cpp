#include "../include/Passenger.h"


Passenger::Passenger() : CMND({'\0'}), last_name({'\0'}), first_name({'\0'}), gender(nullptr) {}
bool Passenger::valid_user() {
    return strcmp(CMND, "") != 0 && 
           strcmp(last_name, "") != 0 && 
           strcmp(first_name, "") != 0 && 
           gender != nullptr;
}