#pragma once
#include "Plane.h"
#include "Flight.h"
#include "Passenger.h"
#include "AVL_TREE.h"
#include "Ticket.h"
#include "Menu.h"
#include "Constants.h"
#include <windows.h>


struct Console {
    Flight* list = nullptr;    // Khai báo extern
    Passenger* input = nullptr;
    AVL_TREE manager;
    Plane *list_planes[MAX_PLANE];



    // void buy_ticket(Passenger input, Flight *booking) {
    //     //in ra danh sách vé còn trống
    //     Ticket new_ticket;
        
    // }
    bool search_plane_id(char target[LEN_PLANE_ID]);
    unsigned int count_flights();
    void enter_available_tickets(Flight *flight);
    void enter_user_information();
    void enter_available_flights();

    void enter_plane_information(Plane &other);
    void enter_plane_update(Plane &other);
};



