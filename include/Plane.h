#pragma once
#include "Constants.h"



struct Plane {
    char flight_number[LEN_FLIGHT_NUMBER];
    char airplane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    
    Plane();

};

extern Plane *domestic[MAX_PLANE];