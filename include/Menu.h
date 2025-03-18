#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <windows.h>

class Menu {
public:
    void gotoxy(int x, int y);
    void show_navigation_instructions();
    void print_login_frame();
    void print_manager_menu();
    void manage_aircrafts();
    void add_aircraft();
    void delete_aircraft();
    void edit_aircraft_details();
    void manage_flights();
    void create_new_flight();
    void edit_flight_schedule();
    void cancel_flight();
    void enter_user_information();
    void identification_information();
    void flight_list();
    void book_ticket();
    void cancel_ticket();
    void passenger_list();
    void available_flights();
    void available_tickets();
    void display_aircraft_statistics();
    
   //cac ham ben duoi can viet them
    void display_flight_list();
    void display_booked_flights();
    void display_passenger_list();
    void display_available_flights();
    void display_available_tickets();
    void function();
};

#endif 

