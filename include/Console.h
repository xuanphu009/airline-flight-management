#pragma once
#include "Flight.h"
#include "Passenger.h"
#include "AVL_tree.h"
#include <cstring>
#include <iostream>
#include <conio.h>
#include "Menu.h"

namespace Console {
    AVL_TREE manager;
    Flight *list;



    void buy_ticket(Passenger input, Flight *booking) {
        //in ra danh sách vé còn trống
        Ticket new_ticket;
        
    }


    void enter_user_information() {
        Passenger input;
        char tmp_gender[2] = "";
        int idx[4] = {};
        int column = 0;
        char ch;
    
        while (true) {
            Menu::display_enter_user_information();
    
            Menu::gotoxy(60, 6);
            std::cout << input.last_name;
            Menu::gotoxy(61, 9);
            std::cout << input.first_name;
            Menu::gotoxy(78, 12);
            std::cout << (tmp_gender);
            Menu::gotoxy(55, 15);
            std::cout << input.CMND;
    
            switch (column) {
                case 0:
                    Menu::gotoxy(60 + idx[column], 6);
                    enter(input.last_name, idx[column], LEN_LAST_NAME, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z');
                         });
                    break;
                case 1:
                    Menu::gotoxy(61 + idx[column], 9);
                    enter(input.first_name, idx[column], LEN_FIRST_NAME, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z');
                        });
                    break;
                case 2: {
                    Menu::gotoxy(78 + (input.gender != nullptr ? 1 : 0), 12);
                    enter(tmp_gender, idx[column], 2, ch, [](char &c) { return c == '0' || c == '1'; });
                    if (strlen(tmp_gender)) input.gender = new bool(tmp_gender[0] == '1');
                    else input.gender = nullptr;
                    break;
                }
                case 3:
                    Menu::gotoxy(55 + idx[column], 15);
                    enter(input.CMND, idx[column], LEN_CMND, ch);
                    break;
            }
    
            if (ch == UP && column > 0) {
                --column;
            } else if (ch == DOWN && column < 3) {
                ++column;
            } else if (ch == ENTER && input.valid_user()) {
                // thiếu điều kiện
                //in ra số lượng chuyến bay
                break;
            }
        }
    }

    // void buy_ticket(Passenger input) {


    //     // in ra danh sách chuyến bay
    //     // nhập p

    //     // if(!booking->valid_CMND(input.CMND)) return;

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
    //     // booking->tickets[new_seat] = new_ticket; 
    // }

    // void 

    void main() {

    }
}


