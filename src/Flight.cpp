#include "../include/Flight.h"


Flight::Flight() : next(nullptr) {}

bool Flight::valid_user(char *CMND) {
    for(int i = 0; i < *total_seats; ++i) {
        if(tickets[i].CMND != nullptr && strcmp(tickets[i].CMND, CMND) == 0) return false;
    }
    return true;
}
