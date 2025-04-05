#pragma once
#include"Ticket.h"
#include "Constants.h"
#include <cstring>

struct Passenger{
    char CMND[LEN_CMND];
    char last_name[LEN_LAST_NAME];
    char first_name[LEN_FIRST_NAME];
    bool *gender;
    // Ticket *used;
    
    Passenger();
    bool valid_user();
    bool operator == (Passenger &other) {
        return strcmp(CMND, other.CMND) == 0 && strcmp(last_name, other.last_name) == 0 && strcmp(first_name, other.first_name) == 0 && *gender == *other.gender;

    }
};