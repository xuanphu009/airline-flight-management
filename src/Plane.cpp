#include "../include/Plane.h"
#include <cstring>
#include <iostream>


Plane::Plane(){
    plane_id[0] = '\0';
    plane_type[0] = '\0';
    number_of_seats = 0;
    number_of_flights_performed = 0;
}

// int Plane::my_lower_bound(char target[LEN_PLANE_ID]){
//     // tim vi tri de chen ma du nguyen thu tu
//     int left = 0, right = size_plane;// neu chen vao cuoi
//     while (left < right){
//         int mid = (left + right) / 2;
//         if (strcmp(list_planes[mid]->plane_id, target) < 0){
//             left = mid + 1;
//         }
//         else {
//             right = mid;
//         }
//     }
//     return left;
// }
// bool Plane::binary_search_plane_id(char target[LEN_PLANE_ID]){
//     if (size_plane == 0) return false;
//     int left = 0, right = size_plane - 1;
//     while (left < right){
//         int mid = (left + right) / 2;
//         if (strcmp(list_planes[mid]->plane_id, target) == 0){
//             return true;
//         }
//         else if (strcmp(list_planes[mid]->plane_id, target) < 0){
//             left = mid + 1;
//         }
//         else {
//             right = mid - 1;
//         }
//     }
//     return false;
// }
// void Plane::input_plane(Plane &other){

//     Menu::add_aircraft();

//     Menu::gotoxy(57, 7);
//     char ch;
//     auto is_plane_id = [] (char c) {return isalnum(c) ;};
//     enter(other.plane_id, 0, LEN_PLANE_ID + 1, ch, is_plane_id);

//     while (binary_search_plane_id(other.plane_id)){
//         system("clear");
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    AIRCRAFT ID ALREALDY EXISTS   |
//                         |__________________________________|
//         )";
//         Menu::notification();

//         Menu::add_aircraft();
//         Menu::gotoxy(57, 7);
//         enter(other.plane_id, 0, LEN_PLANE_ID + 1, ch, is_plane_id);

//     }

//     Menu::gotoxy(59, 10);
//     auto is_plane_type = [] (char c) {return isalnum(c) || c == ' ' ;};
//     enter(other.plane_type, 0, LEN_PLANE_TYPE + 1, ch, is_plane_type);

//     char temp[5];
//     Menu::gotoxy(68, 13);
//     auto is_number = [] (char c) {return isdigit(c) ;};
//     enter(temp, 0, 6, ch, is_number);
//     other.number_of_seats = atoi(temp);

//     char temp1[5];
//     Menu::gotoxy(63, 16);
//     enter(temp1, 0, 6, ch, is_number);
//     other.number_of_flights_performed = atoi(temp1);

// }
// void Plane::add_plane(){
//     if (size_plane >= MAX_PLANE){
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    THE AIRCRAFT LIST IS FULL     |
//                         |__________________________________|
//         )";                                            
//         return;
//     }
//     else {
//         Plane other;
//         input_plane(other);
//         system("clear");
//         int index = my_lower_bound(other.plane_id);
//         for (int i = size_plane; i > index; i--){
//             list_planes[i] = list_planes[i - 1];
//         }
//         list_planes[index] = new Plane(other);
//         size_plane++;
//         std::cout << R"(
//                      ____________________________________________________________ 
//                     |                                                            |
//                     |    THE AIRCRAFT HAS BEEN SUCCESSFULLY ADDED TO THE LIST    |
//                     |____________________________________________________________|
//         )";
//         Menu::notification();                                            
//     }
// }
// void Plane::delete_plane() {
//     if (size_plane == 0) {
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    THE AIRCRAFT LIST IS EMPTY    |
//                         |__________________________________|
//         )";
//         Menu::notification();                                           
//         return;
//     }
//     else {
//         Menu::delete_aircraft();
        
//         Menu::gotoxy(72, 7);
//         char temp[LEN_PLANE_ID];
//         char ch;
//         auto is_plane_id = [] (char c) {return isalnum(c) ;};
//         enter(temp, 0, LEN_PLANE_ID + 1, ch, is_plane_id);

//         while (! binary_search_plane_id(temp)){
//             system("clear");
//             std::cout << R"(
//                 __________________________________ 
//                |                                  |
//                |    AIRCRAFT ID DOES NOT EXISTS   |
//                |__________________________________|
//             )";

//             Menu::notification();

//             Menu::delete_aircraft();
    
//             Menu::gotoxy(72, 7);

//             enter(temp, 0, LEN_PLANE_ID + 1, ch, is_plane_id);
//         }

//         for (int i = 0; i < size_plane; i++) {

//             if (strcmp(list_planes[i]->plane_id, temp) == 0) {
//                 delete list_planes[i];
//                 list_planes[i] = nullptr;
//                 for (int j = i; j < size_plane - 1; j++) {
//                     list_planes[j] = list_planes[j + 1];
//                 }
//                 list_planes[size_plane - 1] = nullptr;
//                 size_plane--;
//                 system("clear");
//                 std::cout << R"(
//                     ___________________________________________________________________________ 
//                    |                                                                           |
//                    |    SUCCESSFULLY DELETED AIRCRAFT WITH REGISTRATION NUMBER )"
//                     << temp << std::string(LEN_PLANE_ID - strlen(temp), ' ') << R"( |
//                    |___________________________________________________________________________|
//                 )";

//                 Menu::notification();
//                 return;
//             }
            
//         }
                                         
//     }
// }

// void Plane::input_plane_update(Plane &other){
//     Menu::edit_aircraft_details();

//     Menu::gotoxy(70, 7);
//     char ch;
//     auto is_plane_id = [] (char c) {return isalnum(c) ;};
//     enter(other.plane_id, 0, LEN_PLANE_ID + 1, ch, is_plane_id);

//     while (! binary_search_plane_id(other.plane_id)){ // neu khong ton tai
//         system("clear");
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    AIRCRAFT ID DOES NOT EXISTS   |
//                         |__________________________________|
//         )";

//         Menu::notification();

//         Menu::edit_aircraft_details();
//         Menu::gotoxy(70, 7);
//         enter(other.plane_id, 0, LEN_PLANE_ID + 1, ch, is_plane_id);

//     }

//     Menu::gotoxy(62, 10);
//     auto is_plane_type = [] (char c) {return isalnum(c) || c == ' ' ;};
//     enter(other.plane_type, 0, LEN_PLANE_TYPE + 1, ch, is_plane_type);

//     char temp[5];
//     Menu::gotoxy(71, 13);
//     auto is_number = [] (char c) {return isdigit(c) ;};
//     enter(temp, 0, 6, ch, is_number);
//     other.number_of_seats = atoi(temp);

//     char temp1[5];
//     Menu::gotoxy(66, 16);
//     enter(temp1, 0, 6, ch, is_number);
//     other.number_of_flights_performed = atoi(temp1);
// }
// void Plane::update_plane() {

//     if (size_plane == 0) {
//         std::cout << R"(
//                          __________________________________ 
//                         |                                  |
//                         |    THE AIRCRAFT LIST IS EMPTY    |
//                         |__________________________________|
//         )";
//         Menu::notification();                                           
//         return;
//     }
//     else {

//         Plane other;
//         input_plane_update(other);
        
//         for (int i = 0; i < size_plane; i++) {
//             if (strcmp(list_planes[i]->plane_id, other.plane_id) == 0) {

//                 strncpy(list_planes[i]->plane_type, other.plane_type, LEN_PLANE_TYPE);
//                 list_planes[i]->number_of_seats = other.number_of_seats;
//                 list_planes[i]->number_of_flights_performed = other.number_of_flights_performed;

//                 system("clear");
//                 std::cout << R"(
//                     ___________________________________________________________________________ 
//                    |                                                                           |
//                    |    SUCCESSFULLY UPDATED AIRCRAFT WITH REGISTRATION NUMBER )"
//                     << other.plane_id << std::string(LEN_PLANE_ID - strlen(other.plane_id), ' ') << R"( |
//                    |___________________________________________________________________________|
//                 )";
//                 Menu::notification();
//                 return;
//             }
//         }
//     }
                                                

// }

