#pragma once
#include "Flight.h"
#include "Passenger.h"
#include "Menu.h"
#include "AVL_tree.h"
#include <cstring>
#include <iostream>
#include <conio.h>
#include "Menu.h"

struct Console {
    static Flight* list;    // Khai báo extern
    static Passenger* input;
    static AVL_TREE manager;



    // void buy_ticket(Passenger input, Flight *booking) {
    //     //in ra danh sách vé còn trống
    //     Ticket new_ticket;
        
    // }
    unsigned int count_flights();
    void enter_available_tickets(Flight *flight);
    void enter_user_information();
    void enter_available_flights();

    // void flight_statistics() {

    // }
    // void buy_ticket(Passenger input) {


    //     // in ra danh sách chuyến bay
    //     // nhập p

    //     // if(!booking->valid_CMND(input->CMND)) return;

    //     int new_seat; 
    //     while(std::cin >> new_seat) {
    //         if(booking->valid_seat(new_seat)) break;
    //     }

    //     Node *user = manager.search(manager.get_root() ,input->CMND);
    //     if(user == nullptr) {
    //         manager.insert(manager.get_root(), input);
    //     } else {
    //         if(!(user->data == input)) {
    //             //lỗi
    //         } 
    //     }

    //     Ticket new_ticket(new_seat, input->CMND);
    //     // booking->tickets[new_seat] = new_ticket; 
    // }

    // void 

};


