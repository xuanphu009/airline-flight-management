#include <iostream>
#include <string>

// #include <conio.h>
// #include <windows.h>
#include "../include/Menu.h"

#ifdef _WIN32
    #include <windows.h>
    void Menu::gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
#else
    void Menu::gotoxy(int x, int y) {
        std::cout << "\033[" << y << ";" << x << "H";
    }
    
#endif

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

void Menu::notification(){
    gotoxy(60, 23);
    std::cout << "Press any key to continue...";
    _getch();
}
void Menu::print_login_frame() {
    system("clear");
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
    system("clear");
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
    system("clear");
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
    system("clear");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |            ADD NEW AIRCRAFT            |
                                       |________________________________________|
                                       |                                        |
                                       |   Aircraft ID:                         |
                                       |________________________________________|
                                       |                                        |
                                       |   Aircraft Type:                       |
                                       |________________________________________|
                                       |                                        |
                                       |   Number of Seats (>=20):              |
                                       |________________________________________|
                                       |                                        |
                                       |   Flights Performed:                   |
                                       |________________________________________|

    )";

    show_navigation_instructions(); 
}


void Menu::delete_aircraft() {
    system("clear");
    std::cout << R"(
                                        _______________________________________________
                                       |                                               |
                                       |                DELETE AIRCRAFT                |
                                       |_______________________________________________|
                                       |                                               |
                                       |  Enter Aircraft ID to delete:                 |
                                       |_______________________________________________|
                                       
    )";

    show_navigation_instructions(); 
}
void Menu::edit_aircraft_details() {
    system("clear");
    std::cout << R"(
                                        _____________________________________________
                                       |                                             |
                                       |           EDIT AIRCRAFT DETAILS             |
                                       |_____________________________________________|
                                       |                                             |
                                       |  Enter Aircraft ID to edit:                 |
                                       |_____________________________________________|
                                       |                                             |
                                       |  New Aircraft Type:                         |
                                       |_____________________________________________|
                                       |                                             |
                                       |  New Number of Seats (>=20):                |
                                       |_____________________________________________|
                                       |                                             |
                                       |  New Flights Performed:                     |
                                       |_____________________________________________|

    )";

    show_navigation_instructions();
}

void Menu::dispaly_plane_list(){
    std::cout << R"( 
                                ________________________________________________________________________________________________
                                |    PLANE ID    |              PlANE TYPE                  | NUMBER OF SEAT | FLIGHT PERFORMED |  
                                _________________|__________________________________________|________________|__________________|
    )";
    show_navigation_instructions();
}

void Menu::manage_flights() {//B
    system("clear");
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
    system("clear");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |          CREATE NEW FLIGHT             |
                                       |________________________________________|
                                       |                                        |
                                       |  Flight ID:                            |
                                       |________________________________________|
                                       |                                        |
                                       |  Departure Time:                       |
                                       |(dd/mm/yyyy hh:mm)                      |
                                       |________________________________________|
                                       |                                        |
                                       |  Destination:                          |
                                       |________________________________________|
                                       |                                        |
                                       |  Flight Status:                        |
                                       |(0: Canceled, 1: Ready)                 |
                                       |________________________________________|
    )";

    show_navigation_instructions(); 
}
void Menu::edit_flight_schedule() {
    system("clear");
    std::cout << R"(
                                        ________________________________________
                                       |                                        |
                                       |         EDIT FLIGHT SCHEDULE           |
                                       |________________________________________|
                                       |                                        |
                                       |  Enter Flight ID to:                   |
                                       |________________________________________|
                                       |                                        |
                                       |  New Departure Time:                   |
                                       |   (dd/mm/yyyy hh:mm)                   |
                                       |________________________________________|
    )";

    show_navigation_instructions(); 
    
}

void Menu::cancel_flight() {
    system("clear");
    std::cout << R"(
                                        ____________________________________________
                                       |                                            |
                                       |               CANCEL FLIGHT                |
                                       |____________________________________________|
                                       |                                            |
                                       |  Enter Flight ID to cancel:                |
                                       |____________________________________________|
                                      
    )";

    show_navigation_instructions(); 
}

void Menu::display_flight_list(){
    system("clear");
    
    std::cout << R"(
                                ____________________________________________________________________________________
                                |   Flight ID   |    Date    |  Time |    Destination   |    Plane ID     | Status |
                                ________________|____________|_______|__________________|_________________|________|
    )";
    show_navigation_instructions();
}



void Menu::display_enter_user_information() {
    system("clear");
    std::cout << R"(
                                        ___________________________________________
                                       |                                           |
                                       |         ENTER USER INFORMATION            |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter Last Name:                       |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter First Name:                      |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter Gender:                          |
                                       |(Male: 1, Female: 0):                      |
                                       |___________________________________________|
                                       |                                           |
                                       |    Enter CMND:                            |
                                       |___________________________________________|
    )";
    // show_navigation_instructions();
}

void Menu::identification_information() {    
    system("clear");
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
    system("clear"); 
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
    system("clear");
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
    system("clear");
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
    system("clear");
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
    system("clear");
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
void Menu::display_available_tickets() { 
    system("clear");
    std::cout << R"(
									 ____________________________________________________________________________
									|                                                                            |
									|                 AVAILABLE TICKETS FOR FLIGHT ID:                           |
									|____________________________________________________________________________|
									|               |                                                            |
									|  Seat Number  |  Status                                                    |
									|_______________|____________________________________________________________|
									)";

    // display_available_tickets(); //tu viet

    std::cout << R"(
									|____________________________________________________________________________|
									   )";

    // show_navigation_instructions(); 
}


void Menu::display_aircraft_statistics() {//h;
    system("clear");
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



