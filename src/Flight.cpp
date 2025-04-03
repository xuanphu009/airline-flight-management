#include "../include/Flight.h"

Flight *head;

Flight::Flight() : next(nullptr) {}
Flight::~Flight(){
    while (head != nullptr){
        Flight *temp = head;
        head = head->next;
        delete temp;
    }
}

// void Flight::input_flight(Flight &other) {
//     Menu::create_new_flight();

//     Menu::gotoxy(54, 7);
//     char ch;
//     auto is_flight_id = [] (char c) {return isalnum(c) ;};
//     enter(other.flight_id, 0, LEN_FLIGHT_ID + 1, ch, is_flight_id);

//     Flight *temp = head;
//     while (temp != nullptr){
//         if (strcmp(temp->flight_id, other.flight_id) == 0){
//             system("clear");
//             std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    FLIGHT ID ALREALDY EXISTS     |
//                         |__________________________________|
//             )";
//             Menu::notification();

//             Menu::create_new_flight();
//             Menu::gotoxy(54, 7);
//             enter(other.flight_id, 0, LEN_FLIGHT_ID + 1, ch, is_flight_id);
//             temp = head;
//         }
//         else {
//             temp = temp->next;
//         }
//     }

    
// }

void Flight::create_flight(){
    Flight *new_flight = new Flight;
    input_flight(*new_flight);

    new_flight->next = head;
    head = new_flight;
    
    system("clear");
    std::cout << R"(
                         ___________________________________ 
                        |                                   |
                        |    FLIGHT CREATED SUCCESSFULLY    |
                        |___________________________________|
            )";
    Menu::notification();
}
// void Flight::input_flight_update(Flight &other){
//     Menu::edit_flight_schedule();

//     Menu::gotoxy(63, 7);
//     char ch;
//     auto is_flight_id = [] (char c) {return isalnum(c) ;};
//     enter(other.flight_id, 0, LEN_FLIGHT_ID + 1, ch, is_flight_id);

//     Flight *temp = head;
//     while (temp != nullptr){
//         if (strcmp(temp->flight_id, other.flight_id) == 0){

//             Menu::gotoxy(63, 10);

//             return;
//         }
//         temp = temp->next;
//     }

//     system("clear");
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    FLIGHT ID DOES NOT EXISTS     |
//                         |__________________________________|
//             )";
//          Menu::notification();
    
// }

void Flight::update_departure_time(){
    Flight other;
    input_flight_update(other);

    Flight *temp = head;
    while (temp != nullptr){
        if (strcmp(temp->flight_id, other.flight_id) == 0){

            strncpy(temp->flight_id, other.flight_id, LEN_FLIGHT_ID);


            system("clear");
            std::cout << R"(
                _____________________________________________________________________________ 
               |                                                                             |
               |    SUCCESSFULLY UPDATED THE FLIGHT WITH REGISTRATION NUMBER )"
                << other.flight_id << std::string(LEN_FLIGHT_ID - strlen(other.flight_id), ' ') << R"( |
               |_____________________________________________________________________________|
            )";
            Menu::notification();
        }
    }
}

// void Flight::cancel_flight(){
//     if (head == nullptr){
//         system("clear");
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    THE FLIGHT LIST IS EMPTY      |
//                         |__________________________________|
//             )";
//          Menu::notification();
//     }
//     Menu::cancel_flight();
//     Menu::gotoxy(70, 7);

//     char temp[LEN_FLIGHT_ID];
//     char ch;
//     auto is_flight_id = [] (char c) {return isalnum(c) ;};
//     enter(temp, 0, LEN_FLIGHT_ID + 1, ch, is_flight_id);

//     Flight *ptr = head;
//     while (ptr != nullptr){
//         if (strcmp(ptr->flight_id, temp) != 0){
//             system("clear");
//             std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    FLIGHT ID DOES NOT EXISTS     |
//                         |__________________________________|
//             )";
//             Menu::notification();

//             Menu::create_new_flight();
//             Menu::gotoxy(70, 7);
//             enter(temp, 0, LEN_FLIGHT_ID + 1, ch, is_flight_id);
//             ptr = head;
//         }
//         else {
//             ptr = ptr->next;
//         }
//     }
//     ptr = head;
//     while (ptr != nullptr && ptr->flight_id != temp){
//         ptr = ptr->next;
//     }
//     if (ptr->cur_status != status::completed){
//         ptr->cur_status = status::cancelled;
        
//         system("clear");
//             std::cout << R"(
//                          ____________________________________ 
//                         |                                    | 
//                         |    FLIGHT CANCELLED SUCCESSFULLY   |
//                         |____________________________________|
//             )";
//             Menu::notification();
//     }
//     else {
//         system("clear");
//             std::cout << R"(
//                          ____________________________________ 
//                         |                                    | 
//                         |    UNABLE TO CANCEL THE FLIGHT     |
//                         |____________________________________|
//             )";
//             Menu::notification();
//     }
// }

