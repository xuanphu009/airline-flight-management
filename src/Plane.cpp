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

std::ofstream& operator<<(std::ofstream &out, const Plane &other) {
    out << other.plane_id << std::endl
    << other.plane_type << std::endl
    << other.number_of_seats << std::endl
    << other.number_flights_performed << std::endl;
    return out;
}
std::ifstream& operator>>(std::ifstream &in, Plane &other) {
    in >> other.plane_id;
    in.ignore();
    in.getline(other.plane_type, LEN_PLANE_TYPE);
    in >> other.number_of_seats;
    in.ignore();
    in >> other.number_flights_performed;
    return in;
}




