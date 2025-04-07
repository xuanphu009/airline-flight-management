#pragma once

#include <iostream>
#include <windows.h>

class Menu {
public:
    void gotoxy(int x, int y);
    void display_flight_manager_menu2(); 
    void display_navigation_instructions();
    void display_list_instructions();
    void display_login_frame();
    void display_flight_manager_menu();

    // Aircraft Management

    void display_manage_aircrafts();
    void display_add_aircraft();
    void display_delete_aircraft();
    void display_edit_aircraft_details();
    void display_plane_list();

        // Flight Management
    void display_manage_flights();
    void display_search_flight();
    void display_create_new_flight();
    void display_edit_flight_schedule();
    void display_enter_flight_ID();

    // Ticket Management
    void display_book_ticket();
    void display_cancel_ticket();

    // Passenger Information
    void display_passenger_list();

    // Flight Queries
    void display_available_flights();
    void display_available_tickets(int current_page, int max_pages);
    void display_aircraft_statistics();
    void display_flight_list(int current_page, int max_pages);

        // User Information
    void display_enter_user_information();
    void display_identification_information();
    void display_enter_flight_details();
};



