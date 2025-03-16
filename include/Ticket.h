#pragma once
#include "Constants.h"

struct Ticket {
    unsigned int seat;
    char CMND[LEN_CMND];
    // Ticket *next;
    // Ticket *prev;
    Ticket();
};