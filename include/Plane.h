#pragma once
#include "Constants.h"
#include "Menu.h"


struct Plane {
    char plane_id[LEN_PLANE_ID];
    char plane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    unsigned int number_of_flights_performed;
    
    Plane();

    void add_plane();
    void delete_plane();
    void update_plane();
    
    void input_plane(Plane &other);
    void input_plane_update(Plane &other);

    int my_lower_bound(char target[LEN_PLANE_ID]);
    bool binary_search_plane_id(char target[LEN_PLANE_ID]);

};

extern Plane *list_planes[MAX_PLANE]; //sô máy bay nội địa có
extern int size_plane;