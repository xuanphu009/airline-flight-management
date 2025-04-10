#include "../include/Passenger.h"



Passenger::Passenger() {number_of_tickets = 0;}
bool Passenger::valid_user() {
    return strcmp(CMND, "\0") != 0 && strcmp(last_name, "\0") != 0 && strcmp(first_name, "\0") != 0 && (gender) != nullptr;
}