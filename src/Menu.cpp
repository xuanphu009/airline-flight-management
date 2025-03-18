#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Menu.h"

void Menu::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;    // col
    coord.Y = y;    // row
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Menu::show_navigation_instructions() {
    gotoxy(0, 20); // Move cursor to the bottom of the screen
    std::cout << R"(
    ----------------------------------------
   |                                        |
   |  Use UP/DOWN to navigate fields        |
   |  Press ENTER to confirm input          |
   |  Press TAB to go back                  |
   |________________________________________|
    )";
}

void Menu::print_login_frame() {
    system("cls");
    std::cout << R"(
                                        _________________________________________
                                       |                                         |
                                       |           WELCOME TO OUR AIRLINE        |
                                       |               WHO ARE YOU ?             |
                                       |_________________________________________|
                                       |                                         | 
                                       |                [ USER ]                 |                       	  
                                       |_________________________________________|
                                       |                                         |  
                                       |               [ MANAGER ]               |      
                                       |_________________________________________|                                      
    )";
    show_navigation_instructions();
}

void Menu::print_manager_menu() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |              MANAGER MENU              |
                                       |________________________________________|
                                       |                                        |
                                       |         [ UPDATE AIRCRAFT ]            |
                                       |________________________________________|
                                       |                                        |
                                       |         [ UPDATE FLIGHTS ]             |
                                       |________________________________________|

    )";
    show_navigation_instructions();
}
void Menu::manage_aircrafts() {//A
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |          AIRCRAFT MANAGEMENT           |
                                       |________________________________________|
                                       |                                        |
                                       |          > Add Aircraft                |
                                       |________________________________________|
                                       |                                        |
                                       |            Delete Aircraft             |
                                       |________________________________________|
                                       |                                        |
                                       |            Edit Aircraft Details       |
                                       |________________________________________|

    )";
    
    show_navigation_instructions();
}
void Menu::add_aircraft() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |            ADD NEW AIRCRAFT            |
                                       |________________________________________|
                                       |                                        |
                                       |   Aircraft ID:                         |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |   Aircraft Type:                       |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |   Number of Seats (>=20):              |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |   Flights Performed:                   |
                                       |     ________________________           |
                                       |________________________________________|

    )";

    show_navigation_instructions(); 
}


void Menu::delete_aircraft() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |            DELETE AIRCRAFT             |
                                       |________________________________________|
                                       |                                        |
                                       |  Enter Aircraft ID to delete:          |
                                       |     ________________________           |
                                       |________________________________________|
                                       
    )";

    show_navigation_instructions(); 
}
void Menu::edit_aircraft_details() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |         EDIT AIRCRAFT DETAILS          |
                                       |________________________________________|
                                       |                                        |
                                       |  Enter Aircraft ID to edit:            |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |   Aircraft Type:                       |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  Number of Seats (>=20):               |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  Flights Performed:                    |
                                       |     ________________________           |
                                       |________________________________________|

    )";

    show_navigation_instructions();
}
void Menu::manage_flights() {//B
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |            FLIGHT MANAGEMENT           |
                                       |________________________________________|
                                       |                                        |
                                       |         > Create New Flight            |
                                       |________________________________________|
                                       |                                        |
                                       |        Edit Flight Departure Time      |
                                       |________________________________________|
                                       |                                        |
                                       |             Cancel Flight              |
                                       |________________________________________|

    )";
    show_navigation_instructions();
}
void Menu::create_new_flight() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |          CREATE NEW FLIGHT             |
                                       |________________________________________|
                                       |                                        |
                                       |  Flight ID:                            |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  Departure Time (dd/mm/yyyy hh:mm):    |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  Destination:                          |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  Flight Status (0: Canceled, 1: Ready) |
                                       |     ________________________           |
                                       |________________________________________|
    )";

    show_navigation_instructions(); 
}
void Menu::edit_flight_schedule() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |         EDIT FLIGHT SCHEDULE           |
                                       |________________________________________|
                                       |                                        |
                                       |  Enter Flight ID:                      |
                                       |     ________________________           |
                                       |________________________________________|
                                       |                                        |
                                       |  New Departure Time (dd/mm/yyyy hh:mm):|
                                       |     ________________________           |
                                       |________________________________________|
    )";

    show_navigation_instructions(); 
    
}

void Menu::cancel_flight() {
    system("cls");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |            CANCEL FLIGHT               |
                                       |________________________________________|
                                       |                                        |
                                       |  Enter Flight ID to cancel:            |
                                       |     ________________________           |
                                       |________________________________________|
                                      
    )";

    show_navigation_instructions(); 
}





void Menu::enter_user_information() {
    system("cls");
    std::cout << R"(
                                        ___________________________________________
                                       |                                           |
                                       |         ENTER USER INFORMATION            |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter Last Name: ______________________|
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter First Name: _____________________|
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter Gender (Male: 1, Female: 0)      |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter ID Card Number: _________________|
                                       |___________________________________________|

    )";
    show_navigation_instructions();
}

void Menu::identification_information() {    
    system("cls");
    std::cout << R"(
                                        ___________________________________________
                                       |                                           |
                                       |       IDENTIFICATION INFORMATION          |
                                       |___________________________________________|
                                       |                                           |
                                       |   Full Name:                              |
                                       |___________________________________________|
                                       |                                           |
                                       |   Gender:                                 |
                                       |___________________________________________|
                                       |                                           |
                                       |   ID Card Number:                         |
                                       |___________________________________________|

    )";
    
    show_navigation_instructions();
}

void Menu::flight_list() {
    system("cls"); 
    std::cout << R"(
								____________________________________________________________________________
							   |                                                                            |
							   |  Destination: ___________________       Departure Date & Time: __________  |
							   |____________________________________________________________________________|
							   |                                                                            |
							   |                            AVAILABLE FLIGHTS                               |
							   |____________________________________________________________________________|
							   |                                                                            |
							   |    
								)";                                                                        
    // display_flight_list(); //tu viet them
    std:: cout << R"(
								|                                                                            |
							    |                                                                            |
								|                                                                            |
								|____________________________________________________________________________|
									   )";
    show_navigation_instructions();
}
void Menu::book_ticket() { //C
    system("cls");
    std::cout << R"(
									    ____________________________________________________________________________
									   |                                                                            |
									   |                               BOOK A TICKET                                |
									   |____________________________________________________________________________|
									   |  Enter Flight Date (dd/mm/yyyy):  [____________]                           |
									   |____________________________________________________________________________|
									   |                                                                            |
									   |                               AVAILABLE FLIGHTS                            |
									   |____________________________________________________________________________|
									   |  Flight ID  |  Departure Time  |  Destination  |      Available Seats      |
									   | ------------|------------------|---------------|---------------------------|
									   )";

    // display_flight_list(); //tu viet them

    std::cout << R"(
									   |____________________________________________________________________________|
									   |  Enter Flight ID to book:  [____________]                                  |
									   |____________________________________________________________________________|
									   |  Enter Passenger CMND:  [____________]                                     |
									   |____________________________________________________________________________|
									   )";

   show_navigation_instructions();  
}

void Menu::cancel_ticket() { //D
    system("cls");
    std::cout << R"(
									    ____________________________________________________________________________
									   |                                                                            |
									   |                               CANCEL TICKET                                |
									   |____________________________________________________________________________|
									   |  Enter Passenger CCCD:  [____________]                                     |
									   |____________________________________________________________________________|
									   |                                                                            |
									   |                           BOOKED FLIGHTS                                   |
									   |____________________________________________________________________________|
									   |  Flight ID       |  Departure Time    |  Destination                       |
									   |------------------|--------------------|------------------------------------|
									   )";

    // display_booked_flights(); //tu viet them

    std::cout << R"(
										|____________________________________________________________________________|
										|  Enter Flight ID to cancel:  [____________]                                |
										|____________________________________________________________________________|
										)";

    show_navigation_instructions(); 
}

void Menu::passenger_list() {//E
    system("cls");
    std::cout << R"(
									    ____________________________________________________________________________
									   |                                                                            |
									   |              PASSENGER LIST FOR FLIGHT ######                              |
									   |____________________________________________________________________________|
									   |  Departure Time: dd/mm/yyyy hh:mm.   Destination: xxxxxxxxxxxx             |
									   |____________________________________________________________________________|                                                                           |
									   | No.     | Ticket No.  | ID Number       | Full Name             | Gender   |
									   |_________|____________ |_________________|_______________________|__________|
									   )";

    // display_passenger_list(); //tu viet them

    std::cout << R"(
									   |____________________________________________________________________________|
									   )";

    show_navigation_instructions(); 
}

void Menu::available_flights() {//F
    system("cls");
    std::cout << R"(
									    ______________________________________________________
									   |                                                      |
									   |     AVAILABLE FLIGHTS ON [dd/mm/yyyy] TO [XXXX]      |
									   |______________________________________________________|
									   |  Flight ID   |  Departure Time |   Available Seats   |
									   |______________|_________________|_____________________|                  
									   )";

    // display_available_flights(); //tu viet

    std::cout << R"(
									   |______________________________________________________|
									  
									   )";

    show_navigation_instructions();
}
void Menu::available_tickets() { 
    system("cls");
    std::cout << R"(
									 ____________________________________________________________________________
									|                                                                           |
									|                 AVAILABLE TICKETS FOR FLIGHT ID: [XXXXXX]                  |
									|____________________________________________________________________________|
									|               |                                                             |
									|  Seat Number  |  Status                                                    |
									|_______________|____________________________________________________________|
									)";

    // display_available_tickets(); //tu viet

    std::cout << R"(
									|____________________________________________________________________________|
									   )";

    show_navigation_instructions(); 
}


void Menu::display_aircraft_statistics() {//h;
    system("cls");
    std::cout << R"(
									 _________________________________________________
									|                                                 |
									|        AIRCRAFT FLIGHT PERFORMANCE STATS        |
									|_________________________________________________|
									| Aircraft ID   | Flights Performed               |
									|---------------|---------------------------------|
									)";

    // function();//tu viet;

    std::cout << R"(
									|_________________________________________________|
									   )";

    show_navigation_instructions(); 
}



