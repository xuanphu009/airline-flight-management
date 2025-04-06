
#include "../include/Console.h"
#include <algorithm>


void Console::enter_available_tickets(Flight *flight) {
    int current_page = 0, current_column = 0;
    int max_pages = (*flight->total_seats) / SEATS_PER_PAGE + !!(*flight->total_seats % SEATS_PER_PAGE) - 1; // Số trang

    while (true) {
        int start_idx = current_page * SEATS_PER_PAGE + SEATS_PER_PAGE;
        int end_idx = std::min(static_cast<int>(start_idx), static_cast<int>(*flight->total_seats));
        Menu::display_available_tickets();

        char key = _getch(); // Nhận phím nhập vào
        if (key == 27) break;  // ESC để thoát
        else if (key == 75 && current_page > 0)
            current_page--;  // Phím mũi tên trái để chuyển trang về trước
        else if (key == 77 && current_page < max_pages)
            current_page++;  // Phím mũi tên phải để chuyển trang tiếp theo
        else if (key == 72 && current_column > 0)
            current_column--;  // Phím mũi tên lên để chọn vé ở vị trí trước đó
        else if (key == 80 && current_column < (end_idx - start_idx - 1))
            current_column++;  // Phím mũi tên xuống để chọn vé ở vị trí sau đó
        else if (key == 13) { // Phím ENTER
            int selected = start_idx + current_column + 1;
            flight->tickets[selected].seat = selected;
            flight->tickets[selected].CMND = input->CMND;
            //in ra mua thành công
            break;
        }
    }
}
void Console::enter_user_information() {
    //khởi tạo input = neu passenger
    Console::input = new Passenger;
    char tmp_gender[2] = "", ch;
    int idx[4] = {}, column = 0;
    
    while (true) {
        Menu::display_enter_user_information();

        Menu::gotoxy(60, 6);
        std::cout << input->last_name;
        Menu::gotoxy(61, 9);
        std::cout << input->first_name;
        Menu::gotoxy(78, 12);
        std::cout << (tmp_gender);
        Menu::gotoxy(55, 15);
        std::cout << input->CMND;

        switch (column) {
            case 0:
                Menu::gotoxy(60 + idx[column], 6);
                enter(input->last_name, idx[column], LEN_LAST_NAME, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z');
                    });
                break;
            case 1:
                Menu::gotoxy(61 + idx[column], 9);
                enter(input->first_name, idx[column], LEN_FIRST_NAME, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z');
                    });
                break;
            case 2: {
                Menu::gotoxy(78 + (input->gender != nullptr ? 1 : 0), 12);
                enter(tmp_gender, idx[column], 2, ch, [](char &c) { return c == '0' || c == '1'; });
                if (strlen(tmp_gender)) input->gender = new bool(tmp_gender[0] == '1');
                else input->gender = nullptr;
                break;
            }
            case 3:
                Menu::gotoxy(55 + idx[column], 15);
                enter(input->CMND, idx[column], LEN_CMND, ch);
                break;
        }
        // if (ch == UP && column > 0) {
        //     --column;
        // } else if (ch == DOWN && column < 3) {
        //     ++column;
        // } else if (ch == ENTER && input->valid_user()) {
        //     // thiếu điều kiện
        //     //in ra số lượng chuyến bay
        //     break;
        // }
        // thêm dòng lệnh này vào mỗi hàm nhập
        #ifdef __APPLE__
            if (ch == 27 && _getch() == '[') { // Nếu là ESC [
                ch = _getch(); // Lấy ký tự tiếp theo
            }
        #endif

            if (ch == UP || ch == 'A') {
                if (column > 0) --column;
            } else if (ch == DOWN || ch == 'B') {
                if (column < 3) ++column;
            } else if (ch == ENTER && input->valid_user()) {
                break;
            }
    
    }
}

void Console::enter_available_flights() {
    Menu::display_flight_list();

}
void Console::enter_plane_information(Plane &other){
    
        char ch;
        int idx[4] = {}, column = 0;
    
        while (true) {
            Menu::display_add_aircraft();
    
            Menu::gotoxy(57, 7);
            std::cout << other.plane_id;
            Menu::gotoxy(59, 10);
            std::cout << other.plane_type;
            Menu::gotoxy(68, 13);
            if (other.number_of_seats > 0){
                std::cout << other.number_of_seats;
            }
            Menu::gotoxy(63, 16);
            if (other.number_of_flights_performed > 0){
                std::cout << other.number_of_flights_performed;
            }
            
            switch (column) {
                case 0:
                    Menu::gotoxy(57 + idx[column], 7);
                    enter(other.plane_id, idx[column], LEN_PLANE_ID, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z'
                                || c >= 48 && c <= 57);
                        });
                    break;
                case 1:
                    Menu::gotoxy(59 + idx[column], 10);
                    enter(other.plane_type, idx[column], LEN_PLANE_TYPE, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z'
                                || c >= 48 && c <= 57 || c == ' ');
                        });
                    break;
                case 2: {
                    Menu::gotoxy(68 + idx[column], 13);
                    char num_str[5];
                    enter(num_str, idx[column], 5, ch,
                         [&](char &c) { return c >= 48 && c <= 57; });
                    other.number_of_seats = atoi(num_str);
                    break;
                }
                case 3:
                    Menu::gotoxy(63 + idx[column], 16);
                    char num_str[5];
                    enter(num_str, idx[column], 5, ch,
                        [&](char &c) { return c >= 48 && c <= 57; });
                    other.number_of_flights_performed = atoi(num_str);
                    break;
            }
    
            #ifdef __APPLE__
                    if (ch == '\x1B' && _getch() == '[') { // Nếu là ESC [
                        ch = _getch(); // Lấy ký tự tiếp theo
                    }
                #endif
    
                    if (ch == UP || ch == 'A') {
                        if (column > 0) --column;
                    } 
                    else if (ch == DOWN || ch == 'B') {
                        if (column < 3) ++column;
                    } 
                    else if (ch == ENTER) {
                        break;
                    }
        }
}
void Console::enter_plane_update(Plane &other){
        char ch;
        int idx[4] = {}, column = 0;
    
        while (true) {
            Menu::display_edit_aircraft_details();
    
            Menu::gotoxy(70, 7);
            std::cout << other.plane_id;
            Menu::gotoxy(58, 10);
            std::cout << other.plane_type;
            Menu::gotoxy(67, 13);
            if (other.number_of_seats > 0){
                std::cout << other.number_of_seats;
            }
            Menu::gotoxy(62, 16);
            if (other.number_of_flights_performed > 0){
                std::cout << other.number_of_flights_performed;
            }
            
            switch (column) {
                case 0:
                    Menu::gotoxy(70 + idx[column], 7);
                    enter(other.plane_id, idx[column], LEN_PLANE_ID, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z'
                                || c >= 48 && c <= 57);
                        });
                    break;
                case 1:
                    Menu::gotoxy(58 + idx[column], 10);
                    enter(other.plane_type, idx[column], LEN_PLANE_TYPE, ch,
                        [&](char &c) { 
                            if(c >= 'a' && c <= 'z') c -= 32;
                            return (c >= 'A' && c <= 'Z'
                                || c >= 48 && c <= 57 || c == ' ');
                        });
                    break;
                case 2: {
                    Menu::gotoxy(67 + idx[column], 13);
                    char num_str[5];
                    enter(num_str, idx[column], 5, ch,
                         [&](char &c) { return c >= 48 && c <= 57; });
                    other.number_of_seats = atoi(num_str);
                    break;
                }
                case 3:
                    Menu::gotoxy(62 + idx[column], 16);
                    char num_str[5];
                    enter(num_str, idx[column], 5, ch,
                        [&](char &c) { return c >= 48 && c <= 57; });
                    other.number_of_flights_performed = atoi(num_str);
                    break;
            }
    
            #ifdef __APPLE__
                    if (ch == '\x1B' && _getch() == '[') { // Nếu là ESC [
                        ch = _getch(); // Lấy ký tự tiếp theo
                    }
                #endif
    
                    if (ch == UP || ch == 'A') {
                        if (column > 0) --column;
                    } 
                    else if (ch == DOWN || ch == 'B') {
                        if (column < 3) ++column;
                    } 
                    else if (ch == ENTER) {
                        break;
                    }
        }
}