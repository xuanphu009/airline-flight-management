#pragma once
#include "Flight.h"
#include "Passenger.h"
#include "AVL_tree.h"
#include <cstring>
#include <iostream>
namespace Console {
    AVL_TREE manager;
    Flight *list;
    void book_ticket(Flight *booking) {
        //buộc nhập CMND, còn lại thì không cần thiết
        //check CMND có trong chuyến bay chưa?

        char CMND[LEN_CMND];
        // std::cin >> CMND;
        if(booking->is_exist(CMND)) return;

        
        if(manager.search(manager.get_root(),CMND) == nullptr) {
            manager.insert(manager.get_root(), Passenger(CMND));
        }
        Passenger &cur = manager.search(manager.get_root(),CMND)->data;
        

        //nhập vé
        Ticket *selected = new Ticket();
        //in vé ra cho user chọn vé vào selected->seat
        strcpy(selected->CMND, cur.CMND);


        // cập nhập hành khách vào manager
       


        // update danh sách vé trong chuyến bay đang booking
        booking->tickets[selected->seat] = selected; // vé ở chuyến bay trỏ vào vé select
        cur.insert(selected); //update vé đang có của user
        selected->prev = booking->tickets[selected->seat]; // trỏ lại vé của user đang đặt vào danh sách vé của chuyến bay

        //in ra mua vé thành công
    }

    // void cancel_ticket() {
    //     char CMND[LEN_CMND];
    //     //nhập vào  
        
    //     Passenger &cur = manager.search(manager.get_root(), CMND)->data;
        

    //     //in ra flight_code để chọn vé xóa
    //     char flight_code[LEN_FLIGHT_CODE];
    //     //tìm vé có flight_code
    //     Ticket *x;

    //     strcpy(flight_code, cur.used)

    // }
}


