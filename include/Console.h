#pragma once
#include "Flight.h"
#include "Passenger.h"
#include "Menu.h"
#include "AVL_TREE.h"
#include "Plane.h"
#include <cstring>
#include <iostream>


struct Console {
    AVL_TREE manager;
    Flight *list;
    Passenger *input;




    void enter_available_tickets(Flight *flight);
    void enter_user_information();
    void enter_available_flights();

    void enter_plane_information(Plane &other);
    void enter_plane_update(Plane &other);
};



