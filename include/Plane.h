#pragma once
#include "Constants.h"
#include "Menu.h"
#include <fstream>


struct Plane {
    char plane_id[LEN_PLANE_ID];
    char plane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    unsigned int number_flights_performed;

    Plane();

    unsigned int get_total_seats();
    friend std::ofstream& operator<<(std::ofstream &out, const Plane &other);
    friend std::ifstream& operator>>(std::ifstream &in, Plane &other);
};

