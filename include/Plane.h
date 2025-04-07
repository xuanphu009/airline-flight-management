#pragma once
#include "Constants.h"


struct Plane
{
    char flight_number[LEN_FLIGHT_NUMBER];
    char airplane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    unsigned int number_flights_performed;
    Plane();
};

extern Plane *list_planes[MAX_PLANE]; // sô máy bay nội địa có

