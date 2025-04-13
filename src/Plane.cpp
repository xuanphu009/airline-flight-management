#include "../include/Plane.h"
#include <cstring>
#include <iostream>


Plane::Plane(){
    memset(plane_id, 0, LEN_PLANE_ID);
    memset(plane_type, 0, LEN_PLANE_TYPE);
    number_of_seats = 0;
    number_flights_performed = 0;
}

unsigned int Plane::get_total_seats(){
    return (unsigned int ) number_of_seats;
}






