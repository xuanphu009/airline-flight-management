#pragma once
#include"Ticket.h"
#include "Constants.h"
#include <cstring>

struct Passenger{
    char CMND[LEN_CMND];
    char last_name[LEN_LAST_NAME];
    char first_name[LEN_FIRST_NAME];
    bool gender;
    Ticket *used;
    
    Passenger();
    Passenger(char *_CMND) {strcpy(CMND, _CMND);}
    void insert(Ticket *x);
    
};

