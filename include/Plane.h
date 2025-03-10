#pragma once
#include "Constants.h"


struct Flight;

struct Plane {
    char flight_number[LEN_FLIGHT_NUMBER];
    char airplane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    
    Flight *used; // trỏ đến chuyến bay đang sử dụng máy bay

    Plane *next;  
    Plane *prev;
    Plane();

};

extern Plane *inland[MAX_PLANE];