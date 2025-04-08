#pragma once
#include "Constants.h"
#include "Menu.h"


struct Plane {
    char plane_id[LEN_FLIGHT_ID];
    char plane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    unsigned int number_flights_performed;

    Plane();

    
};

