#pragma once
#include "Constants.h"
#include <iostream>
<<<<<<< HEAD

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
#else
    #include <cstdlib>

#endif
=======
#include <windows.h>
#include "Flight.h"
>>>>>>> origin/dev

namespace Menu {
    void gotoxy(int x, int y);
    void notification();
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
    void display_enter_user_information();
    void identification_information();
    void display_flight_list();
    void book_ticket();
    void cancel_ticket();
    void passenger_list();
    void available_flights();
    void display_available_tickets(Flight *flight, int current_page, int max_pages, int start_idx, int end_idx, int current_column);
    void display_aircraft_statistics();
    void display_flight_statistics();

    void print_main_menu();
    void print_manage_planes();
    void print_manage_flights();
    void print_ticket_booking();
    void print_cancel_ticket();
    void print_passenger_list();
    void print_available_flights();


    void display_flight_list();
    void dispaly_plane_list();

    // void display_booked_flights();
    // void display_passenger_list();
    // void display_available_flights();
    // void display_available_tickets();
    // void function();
};


