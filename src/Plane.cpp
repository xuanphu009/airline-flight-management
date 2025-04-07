#include "../include/Plane.h"
#include <cstring>
#include <iostream>

Plane *list_planes[MAX_PLANE];
int size_plane = 0;

Plane::Plane(){
    plane_id[0] = '\0';
    plane_type[0] = '\0';
    number_of_seats = 0;
    number_flights_performed = 0;
}

bool Plane::search_plane_id(const char target[LEN_PLANE_ID]){
    for (int i = 0; i < size_plane; i++){
        if (strcmp(list_planes[i]->plane_id, target) == 0) return true;
    }
    return false;
}

Plane::add_plane_result Plane::add_plane(const Plane &other){
    if (size_plane >= MAX_PLANE){
        return Plane::ADD_LIST_FULL;
    }
    else if (search_plane_id(other.plane_id)){
        return Plane::ADD_PLANE_EXIST;
    }
    else {

        list_planes[size_plane] = new Plane();
        strncpy(list_planes[size_plane]->plane_id, other.plane_id, LEN_PLANE_ID);
        strncpy(list_planes[size_plane]->plane_type, other.plane_type, LEN_PLANE_TYPE);
        list_planes[size_plane]->number_of_seats = other.number_of_seats;
        list_planes[size_plane]->number_flights_performed = other.number_flights_performed;

        size_plane++;
        return Plane::ADD_SUCCESS;

    }
}
Plane::delete_plane_result Plane::delete_plane(const char plane_id[LEN_PLANE_ID]){
    if (size_plane == 0) {                                          
        return Plane::DELETE_LIST_EMPTY;
    }
    else {

        for (int i = 0; i < size_plane; i++) {

            if (strcmp(list_planes[i]->plane_id, plane_id) == 0) {
                delete list_planes[i];
                list_planes[i] = nullptr;
                for (int j = i; j < size_plane - 1; j++) {
                    list_planes[j] = list_planes[j + 1];
                }
                list_planes[size_plane - 1] = nullptr;
                size_plane--;
                return Plane::DELETE_SUCCESS;
            }
            
        }
        return Plane::DELETE_NOT_FOUND;                        
    }
}

Plane::update_plane_result Plane::update_plane(const Plane &other) {

    if (size_plane == 0) {
        return Plane::UPDATE_LIST_EMPTY;
    }

    else {

        for (int i = 0; i < size_plane; i++) {
            if (strcmp(list_planes[i]->plane_id, other.plane_id) == 0) {

                strncpy(list_planes[i]->plane_type, other.plane_type, LEN_PLANE_TYPE);
                list_planes[i]->number_of_seats = other.number_of_seats;
                list_planes[i]->number_flights_performed = other.number_flights_performed;

                return Plane::UPDATE_SUCCESS;
            }
        }
        return Plane::UPDATE_NOT_FOUND;
    }

}





