#include "include/Flight.h"

Flight::Flight() : next(nullptr) {}

bool Flight::is_exist(char *CMND) {
    for(int i = 0; i < this->number_of_seats; ++i) {
        if(strcmp(tickets[i]->CMND, CMND) == 0) return true;
    }
    return false;
}