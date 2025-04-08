
#include "../include/Console.h"
#include <algorithm>

// Plane* Console::list_planes[MAX_PLANE] = {};
// Flight* Console::list = nullptr;
// Passenger* Console::input = nullptr;
// AVL_TREE Console::manager = AVL_TREE();



unsigned int Console::count_flights() {
    int count = 0;
    for(Flight *i = Console::list; i != nullptr; i = i->next, ++count);
    return count;
}

void Console::start_program() {
    int i = 0;
    char ch;
    while(true) {
        Menu::display_login_frame();
        Menu::gotoxy(25 + 29, 7 + i);
        // ch = _getch();
        if(i == 0) {
            Menu::gotoxy(25 + 29, 7);
            std::cout << ">>";
            Menu::gotoxy(25 + 29, 10);
            std::cout << "  ";
        } else {    
            Menu::gotoxy(25 + 29, 7);
            std::cout << "  ";
            Menu::gotoxy(25 + 29, 10);
            std::cout << ">>";
        }
        // std::cout << ">>";
        Menu::gotoxy(0, 0);
        ch = _getch();
        if(ch == UP && i > 0) --i;
        else if(ch == DOWN && i < 1) ++i; 
        else if(ch == ENTER) {
            if(i == 0) {
                enter_user_information();
                input = nullptr;
                continue;
            } else {
                enter_manager_menu();
            }
        }
    }
}
void Console::enter_manager_menu() {
    int i = 0;
    char ch;
    while(true) {
        Menu::display_manager_menu();
        Menu::gotoxy(25 + 29, 7 + i);
        // ch = _getch();
        if(i == 0) {
            Menu::gotoxy(29, 6);
            std::cout << ">>";
            Menu::gotoxy(29, 9);
            std::cout << "  ";
            Menu::gotoxy(29, 12);
            std::cout << "  ";
        } else if (i == 1){    
            Menu::gotoxy(29, 6);
            std::cout << "  ";
            Menu::gotoxy(29, 9);
            std::cout << ">>";
            Menu::gotoxy(29, 12);
            std::cout << "  ";
        } else if(i == 2) {
            Menu::gotoxy(29, 6);
            std::cout << "  ";
            Menu::gotoxy(29, 9);
            std::cout << "  ";
            Menu::gotoxy(29, 12);
            std::cout << ">>";
        }
        // std::cout << ">>";
        Menu::gotoxy(0, 0);
        ch = _getch();
        if(ch == UP && i > 0) --i;
        else if(ch == DOWN && i < 2) ++i; 
        else if(ch == ENTER) {
            if(i == 0) {
                enter_plane_list();
            } else if(i == 1) {
                enter_available_flights();
            } else if(i == 2) {
                enter_plane_statistics();
            }
        }
    }
}

void Console::enter_plane_statistics() {
    
    char ch;
    int number_of_planes = get_plane_count();
    //merge sort
    int cur_page = 0, max_page = (number_of_planes + PLANES_PER_PAGE - 1)/PLANES_PER_PAGE - 1;
    int cur_row = 0;
    while(true) {
        Menu::display_plane_statistics(cur_page, max_page);
        
        for(int i = 0; i < PLANES_PER_PAGE; ++i) {
            if(cur_row == i) {
                Menu::gotoxy(24, 7 + i);
                std::cout << ">>";
            }
            int cur_i = i + cur_page*PLANES_PER_PAGE;
            if(cur_i < number_of_planes) {
                Menu::gotoxy(27, 7 + i);
                std::cout << list_planes[cur_i]->plane_id;
                Menu::gotoxy(27 + 23, 7 + i);
                std::cout << list_planes[cur_i]->plane_type;
                Menu::gotoxy(27 + 23 + 43, 7 + i);
                std::cout << list_planes[cur_i]->number_flights_performed;
            } else {
                Menu::gotoxy(27, 7 + i);
                std::cout << "                                                                     ";
            }

        }
        Menu::gotoxy(0, 0);
        std::cout << "number_of_planes:" << number_of_planes;
        ch = _getch();
        
        if(ch == UP && cur_row > 0) --cur_row;
        else if(ch == DOWN && cur_row + cur_page*PLANES_PER_PAGE < number_of_planes - 1) ++cur_row;
        else if(ch == RIGHT && cur_page < max_page) {
            cur_row = 0;
            ++cur_page;
        } else if(ch == LEFT && cur_page > 0) {
            cur_row = 0;
            --cur_page; 
        } 
    }
    
}
void Console::enter_flight_manager_menu() {
    char ch;
    int i = 0;
    while (true)
    {
        Menu::display_flight_manager_menu();
        
        for(int j = 0; j < 4; ++j) {
            Menu::gotoxy(15 + 14, 6 + j*3);
            if(i == j) std::cout << ">>"; 
            else std::cout << "  ";                
        }
        Menu::gotoxy(0,0);
        ch = _getch();
        if(ch == TAB) {
            break;
        } else if(ch == UP && i > 0) --i;
        else if(ch == DOWN && i < 3) ++i;
        else if(ch == ENTER && i == 3) {
            
        } 
    }   
}

void Console::enter_available_tickets(Flight *flight) {
    int current_page = 0, current_column = 0;
    int max_pages = (*flight->total_seats) / SEATS_PER_PAGE + !!(*flight->total_seats % SEATS_PER_PAGE) - 1; // Số trang

    while (true) {
        int start_idx = current_page * SEATS_PER_PAGE;

        int end_idx = std::min(start_idx + SEATS_PER_PAGE, static_cast<int>(*flight->total_seats));

        Menu::display_available_tickets(current_page, max_pages);
        // 📌 Hiển thị thông tin chuyến bay
        Menu::gotoxy(75, 3);  // Mã chuyến bay
        std::cout << flight->flight_id;

        Menu::gotoxy(38, 5);  // Số hiệu chuyến bay
        std::cout << flight->plane_id;

        Menu::gotoxy(81, 5);  // Điểm đến (Destination)
        std::cout << flight->destination;

        Menu::gotoxy(44, 7);  // Ngày khởi hành
        std::cout << flight->date_dep; 

        Menu::gotoxy(74, 7);  // Giờ khởi hành
        std::cout << flight->time_dep;

        Menu::gotoxy(36, 9);  // Trạng thái chuyến bay
        switch (flight->cur_status) {
            case status::cancelled:
                std::cout << "Cancelled";
                break;
            case status::available:
                std::cout << "Available";
                break;
            case status::sold_out:
                std::cout << "Sold Out";
                break;
            case status::completed:
                std::cout << "Completed";
                break;
        }

        for (int i = start_idx; i < end_idx; i++) {
            int row = 13 + (i - start_idx);
            // Nếu đây là vé được chọn (current_column) thì in con trỏ ">>"
            if ((i - start_idx) == current_column) {
                Menu::gotoxy(26, row); // Vị trí in con trỏ, ví dụ cột 30
                std::cout << ">>";
            } else {
                // Nếu không phải vé được chọn, in khoảng trắng để giữ định dạng
                Menu::gotoxy(26, row);
                std::cout << "  ";
            }
            Menu::gotoxy(30, row);  // Cột hiển thị số ghế
            std::cout << i + 1;
            Menu::gotoxy(69, row);  // Cột hiển thị trạng thái ghế
            std::cout << (flight->tickets[i].CMND != nullptr ? "SOLD OUT" : "AVAILABLE");
        }
        char key = _getch(); // Nhận phím nhập vào

        if (key == ESC) break;  // ESC để thoát
        else if (key == LEFT && current_page > 0)
            current_page--;  // Phím mũi tên trái để chuyển trang về trước
        else if (key == RIGHT && current_page < max_pages)
            current_page++;  // Phím mũi tên phải để chuyển trang tiếp theo
        else if (key == UP && current_column > 0)
            current_column--;  // Phím mũi tên lên để chọn vé ở vị trí trước đó
        else if (key == DOWN && current_column < (end_idx - start_idx - 1))
            current_column++;  // Phím mũi tên xuống để chọn vé ở vị trí sau đó
        else if (key == ENTER) { // Phím ENTER
            int selected = start_idx + current_column;
            if(flight->tickets[selected].CMND != nullptr){
                //hiện thông báo đã có người đăng kí
                continue;
            }
            flight->tickets[selected].CMND = input->CMND;

            flight->tickets[selected].seat = selected;
            // Node *test1 = manager.search(manager.root, nullptr);
            // Sleep(2000);
            Node *test = manager.search(manager.root, input->CMND);
            // Node *test1 = manager.search(manager.root, nullptr);
            // std::ofstream of("E:\\Repos\\DSA\\data\\Passenger\\hehe.txt");
            // of 
            if(test == nullptr) {
                if(manager.root == nullptr) manager.root = manager.insert(manager.root, *input);
                else manager.insert(manager.root, *input);
            }
            //in ra mua thành công
            Console::input = nullptr;
            for(int i = 0; i < 100; ++i) std::cout <<( manager.root == nullptr ? "hehe" : "cc") << std::endl; 
            // Sleep(10000 );
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
                        return (c >= 'A' && c <= 'Z') || c == ' ';
                    });
                break;
            case 1:
                Menu::gotoxy(61 + idx[column], 9);
                enter(input->first_name, idx[column], LEN_FIRST_NAME, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z') || c == ' ';
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
        // thêm dòng lệnh này vào mỗi hàm nhập
        
        if (ch == UP && column > 0) {
            --column;
        } else if (ch == DOWN && column < 3) {
            ++column;
        } else if (ch == ENTER && input->valid_user()) {
            // thiếu điều kiện
            // std::cout << input->CMND << std::endl;
            // Sleep(6000);
        
            enter_available_flights();
            return;
        }
        // #ifdef __APPLE__
        //     if (ch == 27 && _getch() == '[') { // Nếu là ESC [
        //         ch = _getch(); // Lấy ký tự tiếp theo
        //     }
        // #endif
        // if (ch == UP || ch == 'A') {
        // if (column > 0) --column;
        // } else if (ch == DOWN || ch == 'B') {
        //     if (column < 3) ++column;
        // } else if (ch == ENTER && input->valid_user()) {
        //     break;
        // }
    
    }
}
void Console::enter_manage_plane() {
    char ch;
    int i = 0;
    while(true) {
        Menu::display_manage_plane();
        for(int j = 0; j < 3; ++j) { 
            if(j == i) {
                Menu::gotoxy(27 + 27 - 3, 6 + j*3);
                std::cout << ">>";
            } else {
                Menu::gotoxy(27 + 27 - 3, 6 + j*3);
                std::cout << "  ";
            }

        }
        ch = _getch();
        if(ch == TAB) {
            return;
        } else if(ch == UP && i > 0) --i;
        else if(ch == DOWN && i < 2) ++i;
    }
}
void Console::enter_plane_list() {
    char ch;
    int number_of_planes = get_plane_count();
    int cur_page = 0, max_page = (number_of_planes + PLANES_PER_PAGE - 1)/PLANES_PER_PAGE - 1;
    int cur_row = 0;
    while(true) {
        Menu::display_plane_list(cur_page, max_page);
        
        for(int i = 0; i < PLANES_PER_PAGE; ++i) {
            if(cur_row == i) {
                Menu::gotoxy(24, 7 + i);
                std::cout << ">>";
            }
            int cur_i = i + cur_page*PLANES_PER_PAGE;
            if(cur_i < number_of_planes) {
                Menu::gotoxy(27, 7 + i);
                std::cout << list_planes[cur_i]->plane_id;
                Menu::gotoxy(27 + 23, 7 + i);
                std::cout << list_planes[cur_i]->plane_type;
                Menu::gotoxy(27 + 23 + 43, 7 + i);
                std::cout << list_planes[cur_i]->number_of_seats;
            } else {
                Menu::gotoxy(27, 7 + i);
                std::cout << "                                                                     ";
            }

        }
        Menu::gotoxy(0, 0);
        // std::cout << "number_of_planes:" << number_of_planes;
        ch = _getch();
        
        if(ch == UP && cur_row > 0) --cur_row;
        else if(ch == DOWN && cur_row + cur_page*PLANES_PER_PAGE < number_of_planes - 1) ++cur_row;
        else if(ch == RIGHT && cur_page < max_page) {
            cur_row = 0;
            ++cur_page;
        } else if(ch == LEFT && cur_page > 0) {
            cur_row = 0;
            --cur_page; 
        } else if(ch == TAB) {
            enter_manage_plane();
        }
    }
}



void Console::enter_available_flights() {
    
    char ch = '\0';
    // Tính tổng số chuyến bay
    unsigned int total_flights = count_flights();
    // Tính số trang, làm tròn lên nếu cần
    unsigned int number_of_pages = (total_flights + FLIGHTS_PER_PAGE - 1) / FLIGHTS_PER_PAGE;
    
    // Tạo mảng lưu các con trỏ đầu trang
    Flight *pages[number_of_pages];
    pages[0] = list;
    
    // Lưu các con trỏ đầu của các trang tiếp theo
    for (unsigned int i = 1; i < number_of_pages; ++i) {
        Flight *j = pages[i - 1];
        for (int count = 0; j != nullptr && count < FLIGHTS_PER_PAGE; j = j->next, ++count);
        pages[i] = j;
    }
    
    unsigned int cur_page = 0, cur_row = 0;
    
    while (true) {
        Menu::display_flight_list(cur_page, number_of_pages - 1);
        
        // Xác định điểm bắt đầu và kết thúc của trang hiện tại
        Flight *page_start = pages[cur_page];
        Flight *page_end = (cur_page + 1 < number_of_pages) ? pages[cur_page + 1] : nullptr;
        
        // Đếm số chuyến bay trên trang hiện tại
        unsigned int count_on_page = 0;
        for (Flight *tmp = page_start; tmp != page_end && tmp != nullptr; tmp = tmp->next) {
            ++count_on_page;
        }
        
        // Đảm bảo cur_row không vượt quá số dòng hiện có
        // if (cur_row >= count_on_page && count_on_page > 0) {
        //     cur_row = count_on_page - 1;
        // }
        
        // Hiển thị các chuyến bay của trang hiện tại
        Flight *tmp = page_start;
        int i = 0;
        while (tmp != page_end && tmp != nullptr) {
            if (i == cur_row) {
                Menu::gotoxy(22, 6 + i);
                std::cout << ">>";
            }
            Menu::gotoxy(26, 6 + i);
            std::cout << tmp->flight_id;
            Menu::gotoxy(43, 6 + i);
            std::cout << tmp->plane_id;
            Menu::gotoxy(62, 6 + i);
            std::cout << tmp->date_dep << "|" << tmp->time_dep;
            Menu::gotoxy(80, 6 + i);
            std::cout << tmp->destination;
            Menu::gotoxy(99, 6 + i);
            switch (tmp->cur_status) {
                case status::cancelled:
                    std::cout << "cancelled";
                    break;
                case status::available:
                    std::cout << "available";
                    break;
                case status::sold_out:
                    std::cout << "sold out";
                    break;
                case status::completed:
                    std::cout << "completed";
                    break;
            }
            ++i;
            tmp = tmp->next;
        }
        
        // Nhận phím từ bàn phím
        ch = _getch();
        if (ch == UP && cur_row > 0) {
            --cur_row;
        } else if (ch == DOWN && cur_row + 1 < count_on_page) {
            ++cur_row;
        } else if (ch == RIGHT && cur_page < number_of_pages - 1) {
            ++cur_page;
            cur_row = 0;  // Reset chỉ số dòng khi chuyển trang
        } else if (ch == LEFT && cur_page > 0) {
            --cur_page;
            cur_row = 0;  // Reset chỉ số dòng khi chuyển trang
        } else if(ch == ESC) {
            return;
        } else if (ch == ENTER) {
            Flight *selected_flight = page_start;
            for (unsigned int j = 0; j < cur_row && selected_flight != nullptr; ++j) {
                selected_flight = selected_flight->next;
            }
            if(input == nullptr) {

            } else {
                if(selected_flight->valid_user(input->CMND)) {
                    enter_available_tickets(selected_flight);
                    break;
                } else {
                    break;
                }   
            }
        }  else if(ch == TAB && input == nullptr) {
            enter_flight_manager_menu();
        }
    }
}

int Console::get_plane_count() {
    int count = 0;
    while (count < MAX_PLANE && Console::list_planes[count] != nullptr) {
        count++;
    }
    return count;
}

bool Console::search_plane_id(char *target) {
    for (int i = 0; i < MAX_PLANE && list_planes[i] != nullptr; i++) {
        if (strcmp(list_planes[i]->plane_id, target) == 0) return true;
    }
    return false;
}

void Console::add_plane(const Plane &other) {

    int i = 0;
    while (i < MAX_PLANE && list_planes[i] != nullptr) i++;


    list_planes[i] = new Plane();
    strncpy(list_planes[i]->plane_id, other.plane_id, LEN_PLANE_ID);
    strncpy(list_planes[i]->plane_type, other.plane_type, LEN_PLANE_TYPE);
    list_planes[i]->number_of_seats = other.number_of_seats;
    list_planes[i]->number_flights_performed = other.number_flights_performed;

}

void Console::delete_plane(const char *plane_id) {
    for (int i = 0; i < MAX_PLANE && list_planes[i] != nullptr; i++) {
        if (strcmp(list_planes[i]->plane_id, plane_id) == 0) {
            delete list_planes[i];
            for (int j = i; j < MAX_PLANE - 1 && list_planes[j + 1] != nullptr; j++) {
                list_planes[j] = list_planes[j + 1];
            }
            return;
        }
    }

}

void Console::update_plane(const Plane &other) {
    for (int i = 0; i < MAX_PLANE && list_planes[i] != nullptr; i++) {
        if (strcmp(list_planes[i]->plane_id, other.plane_id) == 0) {
            strncpy(list_planes[i]->plane_type, other.plane_type, LEN_PLANE_TYPE);
            list_planes[i]->number_of_seats = other.number_of_seats;
            list_planes[i]->number_flights_performed = other.number_flights_performed;

            return;
        }
    }

}
void Console::enter_plane_information(){

    if (get_plane_count() == MAX_PLANE){
        // Nếu danh sách máy bay đầy, không thể thêm
        Menu::display_full_aircraft_list();
        return;
    }

    Plane other;
    char ch;
    int idx[4] = {}, column = 0;

    while (true) {
        Menu::display_add_aircraft();

        Menu::gotoxy(56, 7);
        std::cout << other.plane_id;
        Menu::gotoxy(58, 10);
        std::cout << other.plane_type;
        Menu::gotoxy(67, 13);
        if (other.number_of_seats > 0){
            std::cout << other.number_of_seats;
        }
        Menu::gotoxy(62, 16);
        if (other.number_flights_performed > 0){
            std::cout << other.number_flights_performed;
        }
        
        switch (column) {
            case 0:
                Menu::gotoxy(56 + idx[column], 7);
                enter(other.plane_id, idx[column], LEN_PLANE_ID + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57);
                    });
                break;
            case 1:
                Menu::gotoxy(58 + idx[column], 10);
                enter(other.plane_type, idx[column], LEN_PLANE_TYPE + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57 || c == ' ');
                    });
                break;
            case 2: {
                Menu::gotoxy(67 + idx[column], 13);
                char num_str[5];
                enter(num_str, idx[column], 6, ch,
                     [&](char &c) { return c >= 48 && c <= 57; });
                other.number_of_seats = atoi(num_str);
                break;
            }
            case 3:
                Menu::gotoxy(62 + idx[column], 16);
                char num_str[5];
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return c >= 48 && c <= 57; });
                other.number_flights_performed = atoi(num_str);
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

            if (column == 0){
                if (search_plane_id(other.plane_id)){
                    // Nếu đã tồn tại mã hiệu máy bay này, yêu cầu nhập lại
                    Menu::display_aircraft_exist();
                    other = Plane();
                    return enter_plane_information();
                }
                else column++;
            }
            else if (column < 3) ++column;
        } 
        else if (ch == ENTER) {
            
            if (column == 0){
                if (search_plane_id(other.plane_id)){
                    // Nếu đã tồn tại mã hiệu máy bay này, yêu cầu nhập lại
                    Menu::display_aircraft_exist();
                    other = Plane();
                    return enter_plane_information();
                }
                else column++;
            }
            else if (column < 3){
                column++;
                continue;
            }
            else {
                
                add_plane(other);
                Menu::display_success_add_aircraft();
                // Thêm thành công máy bay vào danh sách
                return;
            }
        }
    }
}
void Console::enter_plane_update(){

    if (get_plane_count() == 0){
        // Nếu danh sach máy bay rỗng, không thể sửa
        Menu::display_empty_aircraft_list();
        return;
    }

    Plane other;
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
        if (other.number_flights_performed > 0){
            std::cout << other.number_flights_performed;
        }
        
        switch (column) {
            case 0:
                
                Menu::gotoxy(70 + idx[column], 7);
                enter(other.plane_id, idx[column], LEN_PLANE_ID + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57);
                    });
                break;
            case 1:
                Menu::gotoxy(58 + idx[column], 10);
                enter(other.plane_type, idx[column], LEN_PLANE_TYPE + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57 || c == ' ');
                    });
                break;
            case 2: {
                Menu::gotoxy(67 + idx[column], 13);
                char num_str[5];
                enter(num_str, idx[column], 6, ch,
                     [&](char &c) { return c >= 48 && c <= 57; });
                other.number_of_seats = atoi(num_str);
                break;
            }
            case 3:
                Menu::gotoxy(62 + idx[column], 16);
                char num_str[5];
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return c >= 48 && c <= 57; });
                other.number_flights_performed = atoi(num_str);
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
                    if (!search_plane_id(other.plane_id)){
                        // Nếu không tìm thấy mã hiệu máy bay, yêu cầu nhập lại
                        Menu::display_aircraft_not_found();         
                        other = Plane();
                        return enter_plane_update();
                    }
                    else if (column < 3) ++column;
                } 
                else if (ch == ENTER) {
                    
                    if (!search_plane_id(other.plane_id)){
                        // Nếu không tìm thấy mã hiệu máy bay, yêu cầu nhập lại
                        Menu::display_aircraft_not_found();         
                        other = Plane();
                        return enter_plane_update();
                    }
                    else if (column < 3){
                        column++;
                        continue;
                    }
                    else {
                        
                        Console::update_plane(other);
                        Menu::display_success_update_aircraft();
                        // Update thành công máy bay
                        return;
                    }
                        
                }
        }
    
}
void Console::enter_plane_delete(){

    if (get_plane_count() == 0){
        // Nếu danh sach máy bay rỗng, không thể xoá
        Menu::display_empty_aircraft_list();
        return;
    }

    char plane_id[LEN_PLANE_ID + 1] = {'\0'};
    char ch;
    int idx = 0;

    while (true) {
        Menu::display_delete_aircraft();
        Menu::gotoxy(73, 7);
        std::cout << plane_id;

        do {
            enter(plane_id, idx, LEN_PLANE_ID + 1, ch,
                [&](char &c) { 
                    if (c >= 'a' && c <= 'z') c -= 32;
                    return (c >= 'A' && c <= 'Z' || c >= '0' && c <= '9');
                });

            // Kiểm tra nếu là phím mũi tên, không làm gì
        #ifdef __APPLE__
                    if (ch == '\x1B') {
                        char next = _getch();
                        if (next == '[') {
                            char arrow = _getch(); // A, B, C, D
                            continue; // Bỏ qua mũi tên
                        }
                    }
        #else
                    if (ch == -32) {
                        _getch(); // Bỏ phím mũi tên
                        continue;
                    }
        #endif

            break; // Không phải mũi tên thì thoát vòng lặp
        } while (true);

                if (ch == ENTER) {
                    if (!search_plane_id(plane_id)){
                        // Nếu không tìm thấy mã hiệu máy bay, yêu cầu nhập lại
                        Menu::display_aircraft_not_found();
                        return enter_plane_delete();
                    }
                    else {
            
                        // Đã tìm thấy mã hiệu máy bay, cho phép xoá
                        delete_plane(plane_id);
                        // Xoá thành công
                        Menu::display_success_delete_aircraft();
                        return;
                    }       
                        
                }
        }
}