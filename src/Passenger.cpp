#include "../include/Passenger.h"



Passenger::Passenger() {}
bool Passenger::valid_user() {
    return strcmp(CMND, "\0") != 0 && strcmp(last_name, "\0") != 0 && strcmp(first_name, "\0") != 0 && (gender) != nullptr;
}