#pragma once
#include "Constants.h"
#include "Console.h"
#include "Menu.h"


struct Plane {
    char plane_id[LEN_FLIGHT_ID];
    char plane_type[LEN_PLANE_TYPE];
    unsigned int number_of_seats;
    unsigned int number_flights_performed;

    Plane();

    enum delete_plane_result{
        DELETE_SUCCESS,
        DELETE_NOT_FOUND,
        DELETE_LIST_EMPTY,
    };
    enum add_plane_result{
        ADD_SUCCESS,
        ADD_PLANE_EXIST,
        ADD_LIST_FULL,
    };
    enum update_plane_result{
        UPDATE_SUCCESS,
        UPDATE_NOT_FOUND,
        UPDATE_LIST_EMPTY,
    };
    
    // static add_plane_result add_plane(const Plane &other);
    // static delete_plane_result delete_plane(const char plane_id[LEN_PLANE_ID]);
    // static update_plane_result update_plane(const Plane &other);
    

    // static bool search_plane_id(const char target[LEN_PLANE_ID]);  


};

