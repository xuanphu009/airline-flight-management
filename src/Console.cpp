
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
        } else if(ch == ESC) return;
    }
}

void Console::enter_plane_statistics() {
    merge_sort();
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
        
        for(int j = 0; j < 3; ++j) {
            Menu::gotoxy(15 + 14, 6 + j*3);
            if(i == j) std::cout << ">>"; 
            else std::cout << "  ";                
        }
        Menu::gotoxy(0,0);
        ch = _getch();
        if(ch == TAB) {
            break;
        } else if(ch == UP && i > 0) --i;
        else if(ch == DOWN && i < 2) ++i;
        else if(ch == ENTER) {
            if(i == 1) enter_flight_id();
        } else if(ch == ESC) return;
    }   
}

void Console::enter_flight_id() {
    char ch;
    Flight *choosing = nullptr;
    char flight_id[LEN_FLIGHT_ID] = "/0"; int i = 0;
    while(true) {
        Menu::display_enter_flight_ID();
        Menu::gotoxy(25 + 35, 6);
        enter(flight_id, i, LEN_FLIGHT_ID, ch, [](char &c) {
            return true;
        });
        // ch = _getch();
        if(ch == ESC) return;
        else if(ch == ENTER) {
            //thieu dieu kien check flight id
            choosing = list;
            while(choosing) {
                if(strcmp(flight_id, choosing->flight_id) == 0) {
                    break;
                }
                choosing = choosing->next;
            }
            if(choosing == nullptr) {
                //in ra thoong bao
            } else {
                enter_passenger_list(choosing);
                strcpy(flight_id, "/0");
                i = 0;
                choosing = nullptr;
            }
        } 
    }
}   

void Console::count_passengers(Flight *flight, int &count) {
    for(int i = 0; i < *flight->total_seats; ++i) {
        if(flight->tickets[i].CMND != nullptr) ++count;
    }
}  
int* Console::list_passengers(Flight *flight, int &n) {
    // Đếm số vé có hành khách (sử dụng count_passengers)
    count_passengers(flight, n);
    // Cấp phát mảng động cho các chỉ số của vé có người đặt
    int* ans = new int[n];
    int index = 0;
    // Sử dụng biến j cho vòng lặp qua tổng số ghế
    for (int j = 0; j < *flight->total_seats; j++) {
        if (flight->tickets[j].CMND != nullptr) {
            ans[index++] = j;  // Lưu lại chỉ số của vé có người đặt
        }
    }
    return ans;
}


void Console::enter_passenger_list(Flight *flight) {
    int n = 0;
    // Lấy danh sách chỉ số vé có người đặt (mảng được cấp phát động)
    int *seat_indices = list_passengers(flight, n);  

    int cur_row = 0, cur_page = 0;
    int max_page = (n + PASSENGERS_PER_PAGE - 1) / PASSENGERS_PER_PAGE - 1;

    while (true) {
        int start_idx = cur_page * PASSENGERS_PER_PAGE;
        int end_idx = std::min(start_idx + PASSENGERS_PER_PAGE, n);

        Menu::display_passenger_list(cur_page, max_page);

        // Hiển thị thông tin chuyến bay
        Menu::gotoxy(80, 3);
        std::cout << flight->flight_id;
        Menu::gotoxy(38, 5);
        std::cout << flight->plane_id;
        Menu::gotoxy(81, 5);
        std::cout << flight->destination;
        Menu::gotoxy(44, 7);
        std::cout << flight->date_dep; 
        Menu::gotoxy(74, 7);
        std::cout << flight->time_dep;
        Menu::gotoxy(36, 9);
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

        // Hiển thị danh sách các hành khách trên trang hiện tại
        for (int i = start_idx; i < end_idx; i++) {
            int row = 13 + (i - start_idx);
            
            // In con trỏ đánh dấu dòng được chọn
            if ((i - start_idx) == cur_row) {
                Menu::gotoxy(22, row);
                std::cout << ">>";
            } else {
                Menu::gotoxy(22, row);
                std::cout << "  ";
            }
            
            // Sử dụng chỉ số từ mảng seat_indices để biết vé cụ thể trong flight->tickets
            int ticketIndex = seat_indices[i];
            Node *node = manager.search(manager.root, flight->tickets[ticketIndex].CMND);
            Passenger *passenger = (node ? &node->data : nullptr);
            Menu::gotoxy(24, row);
            // std::cout << std::string(90, ' ');
            // In Last Name
            Menu::gotoxy(24 + 3, row);
            std::cout << passenger->last_name;
            // In First Name
            Menu::gotoxy(45, row);
            std::cout << passenger->first_name;
            // In CMND
            Menu::gotoxy(56 + 8, row);
            std::cout << passenger->CMND;
            // In Gender
            Menu::gotoxy(72 + 11, row);
            std::cout << (*passenger->gender == 1 ? "Male" : "Female");
            // Bạn có thể in thêm Seat No. nếu cần, ví dụ:
            Menu::gotoxy(72 + 22, row);
            std::cout << ticketIndex + 1;

        }

        char key = _getch();

        // Xử lý các phím điều hướng
        if (key == ESC) break;
        else if (key == LEFT && cur_page > 0) {
            cur_page--;
            cur_row = 0;
        }
        else if (key == RIGHT && cur_page < max_page) {
            cur_page++;
            cur_row = 0;
        }
        else if (key == UP && cur_row > 0)
            cur_row--;
        else if (key == DOWN && cur_row < PASSENGERS_PER_PAGE - 1)
            cur_row++;
        // Trong hàm enter_passenger_list (Console.cpp)
        else if (key == ENTER) {
            int selected = start_idx + cur_row;
            int ticketIndex = seat_indices[selected]; // Sửa ở đây
            Node *test = manager.search(manager.root, flight->tickets[ticketIndex].CMND);
            if (test != nullptr) { // Kiểm tra test khác nullptr
                test->data.number_of_tickets--;
                if (test->data.number_of_tickets == 0) {
                    manager.root = manager.erase(manager.root, test->data); // Cập nhật root
                }
                flight->tickets[ticketIndex].CMND = nullptr; // Sửa chỉ số ở đây
            }
            break;
        }
    }

    // Giải phóng bộ nhớ đã cấp phát cho mảng seat_indices
    delete[] seat_indices;
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
            // ++number_of_tickets;
            // Node *test1 = manager.search(manager.root, nullptr);
            // Sleep(2000);
            Node *test = manager.search(manager.root, input->CMND);
            // Node *test1 = manager.search(manager.root, nullptr);
            // std::ofstream of("E:\\Repos\\DSA\\data\\Passenger\\hehe.txt");
            // of 
            if(test == nullptr) {
                manager.root = manager.insert(manager.root, *input);
            } 

            //in ra mua thành công
            input->number_of_tickets++;
            Console::input = nullptr;
            // for(int i = 0; i < 100; ++i) std::cout <<( manager.root == nullptr ? "hehe" : "cc") << std::endl; 
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
        else if(ch == ENTER) {
            if(i == 0) {
                enter_plane_information();
            } else if(i == 1) {
                enter_plane_delete();
            } else if(i == 2) {
                enter_plane_update();
            }
            continue;
        } else if(ch == ESC) {
            return;
        }
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
        } else if(ch == ESC) return;
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
        }\
        // Menu::gotoxy(35, 6 + FLIGHTS_PER_PAGE);  
        Menu::display_enter_flight_details();
        
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
void Console::enter_plane_information() {

    if (get_plane_count() == MAX_PLANE) {
        // Nếu danh sách máy bay đầy, không thể thêm
        Menu::display_full_aircraft_list();
        return;
    }

    Plane other;
    char ch;
    int idx[4] = {0}; // Chỉ số con trỏ cho từng trường nhập (cột)
    int column = 0;

    while (true) {
        Menu::display_add_aircraft();

        // Hiển thị thông tin đã nhập
        Menu::gotoxy(56, 6);
        std::cout << other.plane_id;
        Menu::gotoxy(58, 9);
        std::cout << other.plane_type;
        Menu::gotoxy(67, 12);
        if (other.number_of_seats > 0) {
            std::cout << other.number_of_seats;
        }
        Menu::gotoxy(62, 15);
        if (other.number_flights_performed > 0) {
            std::cout << other.number_flights_performed;
        }

        // Nhập liệu theo các trường (cột)
        switch (column) {
            case 0:
                Menu::gotoxy(56 + idx[column], 6);
                enter(other.plane_id, idx[column], LEN_PLANE_ID + 1, ch,
                    [&](char &c) { 
                        // Chuyển ký tự thường thành chữ hoa
                        if (c >= 'a' && c <= 'z')
                            c -= 32;
                        // Cho phép chữ cái và số
                        return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
                    });
                break;
            case 1:
                Menu::gotoxy(58 + idx[column], 9);
                enter(other.plane_type, idx[column], LEN_PLANE_TYPE + 1, ch,
                    [&](char &c) { 
                        if (c >= 'a' && c <= 'z')
                            c -= 32;
                        return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ';
                    });
                break;
            case 2: {
                Menu::gotoxy(67 + idx[column], 12);
                char num_str[5] = {0};
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return (c >= '0' && c <= '9'); });
                other.number_of_seats = atoi(num_str);
                break;
            }
            case 3:
                Menu::gotoxy(62 + idx[column], 15);
                char num_str[5] = {0};
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return (c >= '0' && c <= '9'); });
                other.number_flights_performed = atoi(num_str);
                break;
        }

        // Xử lý các phím di chuyển và phím chức năng
        if (ch == UP || ch == 'A') {
            if (column > 0) {
                --column;
            }
        } 
        else if (ch == DOWN || ch == 'B') {
            if (column < 3) {
                ++column;
            }
        } 
        else if (ch == ENTER) {
            if (column == 0) {
                // Kiểm tra mã máy bay khi nhấn ENTER ở trường mã máy bay
                if (search_plane_id(other.plane_id)) {
                    // Nếu đã tồn tại mã máy bay, thông báo lỗi và reset lại trường mã
                    Menu::display_aircraft_exist();
                    memset(other.plane_id, 0, sizeof(other.plane_id));
                    idx[0] = 0;
                    column = 0;
                    continue;
                } else {
                    column++;
                }
            }
            else if (column < 3) {
                // Chưa hoàn tất nhập liệu cho các trường, chuyển sang trường tiếp theo
                ++column;
                continue;
            }
            else {
                // Đã nhập xong tất cả các trường, tiến hành thêm máy bay
                add_plane(other);
                Menu::display_success_add_aircraft();
                return;
            }
        }
        else if (ch == ESC) {
            // Nếu nhấn ESC, thoát khỏi hàm nhập liệu
            return;
        }
    }
}

void Console::enter_plane_update() {
    if (get_plane_count() == 0) {
        // Nếu danh sách máy bay rỗng, không thể sửa
        Menu::display_empty_aircraft_list();
        return;
    }

    Plane other;
    char ch;
    int idx[4] = {0, 0, 0, 0};
    int column = 0;
    bool planeIdValidated = false; // Cờ xác nhận mã máy bay đã được kiểm tra

    while (true) {
        Menu::display_edit_aircraft_details();

        // Hiển thị thông tin đã nhập
        Menu::gotoxy(70, 6);
        std::cout << other.plane_id;
        Menu::gotoxy(58, 9);
        std::cout << other.plane_type;
        Menu::gotoxy(67, 12);
        if (other.number_of_seats > 0) {
            std::cout << other.number_of_seats;
        }
        Menu::gotoxy(62, 15);
        if (other.number_flights_performed > 0) {
            std::cout << other.number_flights_performed;
        }

        // Nhập liệu theo các trường (cột)
        switch (column) {
            case 0:
                Menu::gotoxy(70 + idx[column], 6);
                enter(other.plane_id, idx[column], LEN_PLANE_ID + 1, ch,
                    [&](char &c) { 
                        if (c >= 'a' && c <= 'z')
                            c -= 32;
                        return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
                    });
                break;
            case 1:
                Menu::gotoxy(58 + idx[column], 9);
                enter(other.plane_type, idx[column], LEN_PLANE_TYPE + 1, ch,
                    [&](char &c) { 
                        if (c >= 'a' && c <= 'z')
                            c -= 32;
                        return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ');
                    });
                break;
            case 2: {
                Menu::gotoxy(67 + idx[column], 12);
                char num_str[5] = {0};
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return (c >= '0' && c <= '9'); });
                other.number_of_seats = atoi(num_str);
                break;
            }
            case 3:
                Menu::gotoxy(62 + idx[column], 15);
                char num_str[5] = {0};
                enter(num_str, idx[column], 6, ch,
                    [&](char &c) { return (c >= '0' && c <= '9'); });
                other.number_flights_performed = atoi(num_str);
                break;
        }

        // Xử lý các phím di chuyển và phím chức năng
        if (ch == UP || ch == 'A') {
            if (column > 0)
                --column;
        } 
        else if (ch == DOWN || ch == 'B') {
            if (column < 3)
                ++column;
        } 
        else if (ch == ENTER) {
            // Ở trường mã máy bay (column 0) thì cần kiểm tra xác nhận nếu chưa được xác thực
            if (column == 0 && !planeIdValidated) {
                if (!search_plane_id(other.plane_id)) {
                    // Nếu không tìm thấy mã máy bay, thông báo lỗi và reset lại trường mã
                    Menu::display_aircraft_not_found();
                    memset(other.plane_id, 0, sizeof(other.plane_id));
                    idx[0] = 0;
                    // Giữ nguyên column = 0 để nhập lại mã máy bay
                    continue;
                } else {
                    planeIdValidated = true;
                    ++column; // Chuyển sang trường tiếp theo
                    continue;
                }
            } 
            else if (column < 3) {
                ++column;
                continue;
            }
            else {
                // Khi đã nhập đủ thông tin, tiến hành cập nhật
                Console::update_plane(other);
                Menu::display_success_update_aircraft();
                return;
            }
        } 
        else if (ch == ESC) {
            // Nếu nhấn ESC, thoát khỏi chế độ sửa
            return;
        }
    }
}


void Console::enter_plane_delete() {

    if (get_plane_count() == 0) {
        // Nếu danh sách máy bay rỗng, không thể xoá
        Menu::display_empty_aircraft_list();
        return;
    }

    char plane_id[LEN_PLANE_ID + 1] = {'\0'};
    char ch;
    int idx = 0;
    while (true) {

        // Hiển thị giao diện nhập xoá máy bay
        Menu::display_delete_aircraft();
        Menu::gotoxy(73, 6);
        std::cout << plane_id;

        // Vòng lặp nhập mã máy bay
        while (true) {
            enter(plane_id, idx, LEN_PLANE_ID + 1, ch,
                  [&](char &c) {
                      if (c >= 'a' && c <= 'z')
                          c -= 32;
                      return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
                  });

            // Trường hợp nhận được phím đặc biệt (arrow keys) trả về -32
            if (ch == -32) {
                _getch(); // Bỏ qua ký tự của phím mũi tên
                continue;
            }
            break; // Nếu không phải arrow key thì thoát vòng lặp nhập
        }

        // Nếu nhấn ESC thì thoát luôn
        if (ch == ESC)
            return;
            
        // Nếu nhấn ENTER, tiến hành kiểm tra và xử lý xoá
        if (ch == ENTER) {
            if (!search_plane_id(plane_id)) {
                // Nếu không tìm thấy mã máy bay, hiển thị thông báo và cho phép nhập lại
                Menu::display_aircraft_not_found();
                continue;
            }
            else {
                // Đã tìm thấy mã, tiến hành xoá và hiển thị thông báo thành công
                delete_plane(plane_id);
                Menu::display_success_delete_aircraft();
                return;
            }
        }
    }   
}



void Console::merge_sort() {
    int n = get_plane_count();
    auto merge = [&](int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Plane* L[n1], *R[n2];

        for (int i = 0; i < n1; i++)
            L[i] = list_planes[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = list_planes[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i]->number_flights_performed <= R[j]->number_flights_performed)
                list_planes[k++] = L[i++];
            else
                list_planes[k++] = R[j++];
        }

        while (i < n1) list_planes[k++] = L[i++];
        while (j < n2) list_planes[k++] = R[j++];
    };

    for (int len = 1; len < n; len *= 2) {
        for (int left = 0; left < n - len; left += 2 * len) {
            int right = std::min(left + 2 * len - 1, n - 1);
            int mid = left + len - 1;
            merge(left, mid, right);
        }
    }
    for(int i = 0; i < n/2; ++i) {
        int j = n - i - 1;
        Plane *tmp = list_planes[j];
        list_planes[j] = list_planes[i];
        list_planes[i] = tmp;
    }
}

// Handle flight
bool Console::search_flight_id(const char *flight_id){
    Flight *curr = list;
    while (curr != nullptr){
        if (strcmp(curr->flight_id, flight_id) == 0) return true;
        curr = curr->next;
    }
    return false;
}
Plane* Console::get_plane_by_id(const char* plane_id) {
    for (int i = 0; i < MAX_PLANE && list_planes[i] != nullptr; i++) {
        if (strcmp(list_planes[i]->plane_id, plane_id) == 0) {
            return list_planes[i];
        }
    }
    return nullptr;
}
void Console::create_flight(const Flight &other) {
    // Khởi tạo node mới
    Flight *new_node = new Flight();

    strncpy(new_node->flight_id, other.flight_id, LEN_FLIGHT_ID);
    strncpy(new_node->destination, other.destination, LEN_DESTINATION);
    strncpy(new_node->plane_id, other.plane_id, LEN_PLANE_ID);
    new_node->cur_status = other.cur_status;
    new_node->date_dep = other.date_dep;
    new_node->time_dep = other.time_dep;

    // Đảm bảo không có vùng nhớ cũ trước khi cấp phát
    new_node->total_seats = nullptr;  
    new_node->tickets = nullptr;  

    // Lấy thông tin máy bay
    Plane* plane = get_plane_by_id(new_node->plane_id);
    if (plane != nullptr) {
        new_node->total_seats = new unsigned int(plane->get_total_seats());
    } else {
        new_node->total_seats = new unsigned int(0); // Nếu không tìm thấy máy bay, đặt số ghế là 0
    }

    // Kiểm tra và cấp phát vé nếu có ghế
    if (*new_node->total_seats > 0) {
        new_node->tickets = new Ticket[*new_node->total_seats];
        if (other.tickets != nullptr) {
            for (unsigned int i = 0; i < *new_node->total_seats; i++) {
                new_node->tickets[i] = other.tickets[i]; // Sao chép vé nếu có
            }
        }
    }

    // Chèn vào danh sách liên kết theo thứ tự
    if (list == nullptr || strcmp(new_node->flight_id, list->flight_id) < 0) {
        new_node->next = list;
        list = new_node;
        return;
    }

    Flight* prev = list;
    Flight* curr = list->next;
    
    while (curr != nullptr && strcmp(new_node->flight_id, curr->flight_id) > 0) {
        prev = curr;
        curr = curr->next;
    }
    new_node->next = curr;
    prev->next = new_node;   
}




void Console::update_flight(const char *flight_id, const date_departure &new_date, const time_departure &new_time){
    Flight *curr = list;

    while (curr != nullptr) {
        if (strcmp(curr->flight_id, flight_id) == 0){

            curr->date_dep = new_date;
            curr->time_dep = new_time;

            return;
        }
        curr = curr->next;
    }
}
bool Console::cancel_flight(const char *flight_id){
    Flight *curr = list;

    while (curr != nullptr){
        if (strcmp(curr->flight_id, flight_id) == 0){
            if (curr->cur_status != status::completed){
                // Neu chua hoan tat thi huy ve
                curr->cur_status = status::cancelled;
                return true;
            }
        }
        curr = curr->next;
    }
    return false;
}

void Console::enter_flight_information(){

    Flight other;
    char ch;
    int idx[5] = {0, 0, 0, 0, 0}, column = 0;

    while (true) {
        Menu::display_create_new_flight();

        Menu::gotoxy(54, 7);
        std::cout << other.flight_id;
        Menu::gotoxy(53, 10);
        std::cout << other.plane_id;
        Menu::gotoxy(72, 13);
        if (other.date_dep.day != 0 && other.date_dep.month != 0 && other.date_dep.year != 0){
            // kiểm tra ngày đã nhập
            std::cout << other.date_dep;
        } 
        Menu::gotoxy(67, 16);
        if (other.time_dep.hour >= 0 || other.time_dep.minute >= 0){
            // kiểm tra thời gian
            std::cout << other.time_dep;
        } 
        Menu::gotoxy(56, 19);
        std::cout << other.destination;


        switch (column) {
            case 0:
                Menu::gotoxy(54 + idx[column], 7);
                enter(other.flight_id, idx[column], LEN_FLIGHT_ID + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57);
                    });
                break;
            case 1:
                Menu::gotoxy(53 + idx[column], 10);
                enter(other.plane_id, idx[column], LEN_PLANE_ID + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57);
                    });
                break;
                case 2: {
                    char dateStr[11] = {}; // Mảng chứa chuỗi nhập ngày dd/mm/yyyy
                    int day, month, year;
                    int read = 0;
                    bool validInput = false; // Biến kiểm tra đầu vào hợp lệ
                
                    do {
                        Menu::gotoxy(72, 13);
                        std::cout << "          "; // Xóa nội dung cũ trước khi nhập mới
                        idx[column] = 0; // Reset chỉ số nhập
                
                        Menu::gotoxy(72 + idx[column], 13);
                        enter(dateStr, idx[column], 11, ch,
                            [&](char &c) {
                                return ((c >= '0' && c <= '9') || c == '/');
                        });
                
                        read = sscanf(dateStr, "%d/%d/%d", &day, &month, &year);
                        validInput = (read == 3 && other.valid_date(day, month, year));
                
                        if (validInput) {
                            other.date_dep.day = day;
                            other.date_dep.month = month;
                            other.date_dep.year = year;
                        }
                    } while (!validInput); // Lặp lại khi nhập sai
                    break;
                }
                
                case 3: {
                    char timeStr[6] = {}; // Mảng chứa chuỗi nhập thời gian hh:mm
                    int hour, minute;
                    int read = 0;
                    bool validInput = false; // Biến kiểm tra đầu vào hợp lệ
                
                    do {
                        Menu::gotoxy(67, 16);
                        std::cout << "     "; // Xóa nội dung cũ trước khi nhập mới
                        idx[column] = 0; // Reset chỉ số nhập
                
                        Menu::gotoxy(67 + idx[column], 16);
                        enter(timeStr, idx[column], 6, ch,
                            [&](char &c) {
                                return ((c >= '0' && c <= '9') || c == ':');
                        });
                
                        read = sscanf(timeStr, "%d:%d", &hour, &minute);
                        validInput = (read == 2 && other.valid_time(hour, minute));
                
                        if (validInput) {
                            other.time_dep.hour = hour;
                            other.time_dep.minute = minute;
                        }
                    } while (!validInput); // Lặp lại khi nhập sai
                    break;
                }
                
                
            case 4:
                Menu::gotoxy(56 + idx[column], 19);
                enter(other.destination, idx[column], LEN_DESTINATION, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z' || c == ' ');
                    });
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
                        if (search_flight_id(other.flight_id)){
                            // Nếu đã tồn tại mã chuyến bay này, yêu cầu nhập lại
                            Menu::display_flight_exist();
                            other = Flight();
                            return enter_flight_information();
                        }
                        else column++;
                    }
                    else if (column < 4) ++column;
                } 
                else if (ch == ENTER) {
                    
                    if (column == 0){
                        if (search_flight_id(other.flight_id)){
                            // Nếu đã tồn tại mã chuyến bay này, yêu cầu nhập lại
                            Menu::display_flight_exist();
                            other = Flight();
                            return enter_flight_information();
                        }
                        else column++;
                    }
                    else if (column < 4){
                        column++;
                        continue;
                    }
                    else {
                        
                        create_flight(other);
                        Menu::display_success_create_flight();
                        // Tạo thành công chuyến bay
                        return;
                    }
                }
    }
}
void Console::enter_flight_update(){
    if (count_flights() == 0){
        // Nếu danh sach chuyến bay rỗng, không thể sửa
        Menu::display_empty_flight_list();
        return;
    }

    char flight_id[LEN_FLIGHT_ID + 1] = {'\0'};
    date_departure new_date = {0, 0, 0};
    time_departure new_time = {-1, -1};

    char ch;
    int idx[3] = {0, 0, 0}, column = 0;

    while (true) {
        Menu::display_edit_flight_schedule();

        Menu::gotoxy(60, 7);
        std::cout << flight_id;
        Menu::gotoxy(76, 10);
        if (new_date.day != 0 && new_date.month != 0 && new_date.year != 0){
            // kiểm tra ngày đã nhập
            std::cout << new_date;
        } 
        Menu::gotoxy(71, 13);
        if (new_time.hour >= 0 || new_time.minute >= 0){
            // kiểm tra thời gian
            std::cout << new_time;
        }
        
        switch (column) {
            case 0: {
                Menu::gotoxy(60 + idx[column], 7);
                enter(flight_id, idx[column], LEN_FLIGHT_ID + 1, ch,
                    [&](char &c) { 
                        if(c >= 'a' && c <= 'z') c -= 32;
                        return (c >= 'A' && c <= 'Z'
                            || c >= 48 && c <= 57);
                    });
                break;
            }
                
            case 1: {
                    char dateStr[11] = {}; // Mảng chứa chuỗi nhập ngày dd/mm/yyyy
                    int day, month, year;
                    int read = 0;
                    bool validInput = false; // Biến kiểm tra đầu vào hợp lệ
                
                    do {
                        Menu::gotoxy(76, 10);
                        std::cout << "          "; // Xóa nội dung cũ trước khi nhập mới
                        idx[column] = 0; // Reset chỉ số nhập
                
                        Menu::gotoxy(76 + idx[column], 10);
                        enter(dateStr, idx[column], 11, ch,
                            [&](char &c) {
                                return ((c >= '0' && c <= '9') || c == '/');
                        });
                        Flight temp;
                        read = sscanf(dateStr, "%d/%d/%d", &day, &month, &year);
                        validInput = (read == 3 && temp.valid_date(day, month, year));
                
                        if (validInput) {
                            new_date.day = day;
                            new_date.month = month;
                            new_date.year = year;
                        }
                    } while (!validInput); // Lặp lại khi nhập sai
                    break;
                }
                
            case 2: {
                    char timeStr[6] = {}; // Mảng chứa chuỗi nhập thời gian hh:mm
                    int hour, minute;
                    int read = 0;
                    bool validInput = false; // Biến kiểm tra đầu vào hợp lệ
                
                    do {
                        Menu::gotoxy(71, 13);
                        std::cout << "     "; // Xóa nội dung cũ trước khi nhập mới
                        idx[column] = 0; // Reset chỉ số nhập
                
                        Menu::gotoxy(71 + idx[column], 13);
                        enter(timeStr, idx[column], 6, ch,
                            [&](char &c) {
                                return ((c >= '0' && c <= '9') || c == ':');
                        });
                        Flight temp;
                        read = sscanf(timeStr, "%d:%d", &hour, &minute);
                        validInput = (read == 2 && temp.valid_time(hour, minute));
                
                        if (validInput) {
                            new_time.hour = hour;
                            new_time.minute = minute;
                        }
                    } while (!validInput); // Lặp lại khi nhập sai
                    break;
                }

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
                        if (! search_flight_id(flight_id)){
                            // Nếu không tìm thấy mã chuyến bay, yêu cầu nhập lại
                            Menu::display_flight_not_found();         
                            return enter_flight_update();
                        }
                        else column++;
                    }
                    else if (column < 2) ++column;
                } 
                else if (ch == ENTER) {
                    if (column == 0){
                        if (! search_flight_id(flight_id)){
                            // Nếu không tìm thấy mã chuyến bay, yêu cầu nhập lại
                            Menu::display_flight_not_found();         
                            return enter_flight_update();
                        }
                        else column++;
                    }
                    
                    else if (column < 2){
                        column++;
                        continue;
                    }
                    else {
                        // Nhập liệu thành công
                        update_flight(flight_id, new_date, new_time);
                        Menu::display_success_update_flight();
                        // Update thành công ngày, giờ chuyến bay
                        return;
                    }
                        
                }
        
    }
}
void Console::enter_flight_cancel(){
    if (count_flights() == 0){
        // Nếu danh sach chuyến bay rỗng, không thể xoá
        Menu::display_empty_flight_list();
        return;
    }

    char flight_id[LEN_FLIGHT_ID + 1] = {'\0'};
    char ch;
    int idx = 0;

    while (true) {
        Menu::display_cancel_flight();
        Menu::gotoxy(60, 7);
        std::cout << flight_id;

        do {
            enter(flight_id, idx, LEN_FLIGHT_ID + 1, ch,
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
                    if (! search_flight_id(flight_id)){
                        // Nếu không tìm thấy mã chuyến bay, yêu cầu nhập lại
                        Menu::display_flight_not_found();
                        return enter_flight_cancel();
                    }
                    else {
                        // Đã tìm thấy mã hiệu máy bay
                        if (cancel_flight(flight_id)){
                            //Huỷ thành công
                            Menu::display_success_cancel_flight();
                        }
                        else {
                            // Không thể huỷ vì chuyến bay đã hoàn tất
                            Menu::display_cannot_cancel_flight();
                        }
                        return;
                    }       
                        
                }
        }
}