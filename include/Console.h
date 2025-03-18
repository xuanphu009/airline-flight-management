#pragma once
#include "Flight.h"
#include "Passenger.h"
#include "AVL_tree.h"
#include <cstring>
#include <iostream>
#include <conio.h>

namespace Console {
    AVL_TREE manager;
    Flight *list;
    void book_ticket(Flight *booking) {
 


        // Ticket new_ticket(new_seat, CMND);


        // if(!booking->valid_ticket_for_new_input(new_seat, CMND)) {
        //     return;
        // }



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


    // void buy_ticket() {
    //     Passenger input;
    //     int idx[4] = {}; // Mảng lưu vị trí nhập từng trường
    //     int column = 0;
    //     char ch;
    //     while (true) {
    //         // display(input, column); // Hiển thị lại dữ liệu trước khi nhập
    
    //         // Nhập dữ liệu tương ứng với dòng hiện tại
    //         switch (column) {
    //             case 0:
    //                 enter(input.CMND, idx[column], LEN_CMND, ch);
    //                 break;
    //             case 1:
    //                 enter(input.last_name, idx[column], LEN_LAST_NAME, ch, 
    //                     [&](char &c) {
    //                         if(c >= 'a' && c <= 'z') c -= 32;
    //                         return c >= 'A' && c <= 'Z';
    //                     }
    //                 );
    //                 break;
    //             case 2:
    //                 enter(input.first_name, idx[column], LEN_FIRST_NAME, ch, 
    //                     [&](char &c) {
    //                         if(c >= 'a' && c <= 'z') c -= 32;
    //                         return c >= 'A' && c <= 'Z';
    //                     }
    //                 );
    //                 break;
    //             case 3: {
    //                 char tmp = '\0';
    //                 enter(&tmp, idx[column], 2, ch, 
    //                     [&](char &c) {
    //                         return c <= '1' && c >= '0';
    //                     }
    //                 ); // 2 để có '\0'
    //                 if (tmp) input.gender = new bool(tmp - '0');
    //                 break;
    //             }
    //         }
    
    //         // Nếu nhấn UP hoặc DOWN, xử lý luôn ngoài vòng lặp chính
    //         if (ch == UP && column > 0) {
    //             --column;
    //         } else if (ch == DOWN && column < 3) {
    //             ++column;
    //         } else if (ch == ENTER && input.valid_user()) {

    //             continue; // Xử lý sau nếu cần
    //         } //nhấn esc để out
    //     }

    //     //in ra danh sách chuyến bay
    //     // nhập p

    //     if(!booking->valid_CMND(input.CMND)) return;

    //     int new_seat; 
    //     while(std::cin >> new_seat) {
    //         if(booking->valid_seat(new_seat)) break;
    //     }

    //     Node *user = manager.search(manager.get_root() ,input.CMND);
    //     if(user == nullptr) {
    //         manager.insert(manager.get_root(), input);
    //     } else {
    //         if(!(user->data == input)) {
    //             //lỗi
    //         } 
    //     }

    //     Ticket new_ticket(new_seat, input.CMND);
    //     booking->tickets[new_seat] = new_ticket; 
    // }

    // void 
}


