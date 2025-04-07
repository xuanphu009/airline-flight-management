#pragma once
#include "Plane.h"
#include "Flight.h"
#include "Passenger.h"
#include "AVL_TREE.h"
#include "Ticket.h"
#include "Menu.h"
#include "Constants.h"



struct Console {
    Flight* list = nullptr;    // Khai báo extern
    Passenger* input = nullptr;
    AVL_TREE manager;
    Plane *list_planes[MAX_PLANE];




    // void buy_ticket(Passenger input, Flight *booking) {
    //     //in ra danh sách vé còn trống
    //     Ticket new_ticket;
        
    // }

    unsigned int count_flights();
    void enter_available_tickets(Flight *flight);
    void enter_user_information();
    void enter_available_flights();

    void enter_plane_information();
    void enter_plane_update();
    void enter_plane_delete();
};



