
#include "../include/Console.h"
#include <algorithm>


// Flight* Console::list = nullptr;
// Passenger* Console::input = nullptr;
// AVL_TREE Console::manager = AVL_TREE();


bool Console::search_plane_id(char target[LEN_PLANE_ID]){
    for (int i = 0; i < MAX_PLANE; i++){
        if (strcmp(list_planes[i]->plane_id, target) == 0) return true;
    }
    return false;
}

unsigned int Console::count_flights() {
    int count = 0;
    for(Flight *i = Console::list; i != nullptr; i = i->next, ++count);
    return count;
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
            int selected = start_idx + current_column + 1;
            flight->tickets[selected].seat = selected;
            flight->tickets[selected].CMND = input->CMND;
            Node *test = manager.search(manager.get_root(), input->CMND);
            if(test != nullptr) manager.insert(manager.get_root(), *input);
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
        
        if (ch == UP && column > 0) {
            --column;
        } else if (ch == DOWN && column < 3) {
            ++column;
        } else if (ch == ENTER && input->valid_user()) {
            // thiếu điều kiện
            enter_available_flights();
            break;
        }
        // #ifdef __APPLE__
        //     if (ch == 27 && _getch() == '[') { // Nếu là ESC [
        //         ch = _getch(); // Lấy ký tự tiếp theo
        //     }
        // #endif
        // if (ch == UP || ch == 'A') {
            //     if (column > 0) --column;
            // } else if (ch == DOWN || ch == 'B') {
            //     if (column < 3) ++column;
            // } else if (ch == ENTER && input->valid_user()) {
            //     break;
            // }
    
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
        Menu::display_flight_list(cur_page, number_of_pages);
        
        // Xác định điểm bắt đầu và kết thúc của trang hiện tại
        Flight *page_start = pages[cur_page];
        Flight *page_end = (cur_page + 1 < number_of_pages) ? pages[cur_page + 1] : nullptr;
        
        // Đếm số chuyến bay trên trang hiện tại
        unsigned int count_on_page = 0;
        for (Flight *tmp = page_start; tmp != page_end && tmp != nullptr; tmp = tmp->next) {
            ++count_on_page;
        }
        
        // Đảm bảo cur_row không vượt quá số dòng hiện có
        if (cur_row >= count_on_page && count_on_page > 0) {
            cur_row = count_on_page - 1;
        }
        
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
        } else if (ch == RIGHT && cur_page + 1 < number_of_pages) {
            ++cur_page;
            cur_row = 0;  // Reset chỉ số dòng khi chuyển trang
        } else if (ch == LEFT && cur_page > 0) {
            --cur_page;
            cur_row = 0;  // Reset chỉ số dòng khi chuyển trang
        } else if (ch == ENTER) {
            if(page_start->valid_user(input->CMND)) {
                enter_available_tickets(page_start);
                break;
            } else {
                //in thống váo không hợp lệ
            }
            
        }
    }
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
        if (other.number_flights_performed > 0){
            std::cout << other.number_flights_performed;
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
        if (other.number_flights_performed > 0){
            std::cout << other.number_flights_performed;
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
                    if (column < 3) ++column;
                } 
                else if (ch == ENTER) {
                    break;
                }
    }
}