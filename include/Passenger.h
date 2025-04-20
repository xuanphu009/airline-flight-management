#pragma once
#include"Ticket.h"
#include "Constants.h"
#include <cstring>

struct Passenger{
    char CMND[LEN_CMND];
    char last_name[LEN_LAST_NAME];
    char first_name[LEN_FIRST_NAME];
    bool *gender;
    int number_of_tickets;
    // Ticket *used;
    
    Passenger();
    bool valid_user();
    bool operator == (Passenger &other);
    friend std::ofstream& operator<<(std::ofstream &out, const Passenger &other);
    friend std::ostream& operator<<(std::ostream &out, const Passenger &other);
    friend std::ifstream& operator>>(std::ifstream &in, Passenger &other);
};
