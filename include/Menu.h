
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <windows.h>

class Menu {
public:
    void gotoxy(int x, int y);
    void show_flight_manager_menu2(); 
    void show_navigation_instructions();
    void show_list_instructions();
    void print_login_frame();
    void show_flight_manager_menu();

    // Aircraft Management

    void manage_aircrafts();
    void add_aircraft();
    void delete_aircraft();
    void edit_aircraft_details();
    void show_plane_list();

        // Flight Management
    void manage_flights();
    void search_flight();
    void create_new_flight();
    void edit_flight_schedule();
    void enter_flight_ID();

    // Ticket Management
    void book_ticket();
    void cancel_ticket();

    // Passenger Information
    void passenger_list();

    // Flight Queries
    void available_flights();
    void available_tickets();
    void display_aircraft_statistics();
    void show_flight_list();

        // User Information
    void enter_user_information();
    void identification_information();
    void enter_flight_details();
};

#endif 


