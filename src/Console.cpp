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
            if(i == 1) enter_flight_id(1);
            else if(i == 2) enter_flight_id(2);
            else if(i == 0) {
                
            }
        } else if(ch == ESC) return;
    }   
}

void Console::enter_flight_id(int choice) {
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
                if(choice == 1) enter_passenger_list(choosing);
                else if(choice == 2)  enter_available_tickets(choosing);
                strcpy(flight_id, "/0");
                i = 0;
                choosing = nullptr;
            }
        } 
    }
}   



void Console::enter_passenger_list(Flight *flight) {
    int n = 0;
    // Lấy danh sách chỉ số vé có người đặt (mảng được cấp phát động)
    int *seat_indices = flight->list_passengers(n);  

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
    
    int n = 0;
    // Lấy danh sách chỉ số vé có người đặt (mảng được cấp phát động)
    int *seat_indices = flight->list_available_seats(n);  
    
    int current_page = 0, current_column = 0;
    int max_pages = (n) / SEATS_PER_PAGE + !!(n % SEATS_PER_PAGE) - 1; // Số trang

    while (true) {
        int start_idx = current_page * SEATS_PER_PAGE;

        int end_idx = std::min(start_idx + SEATS_PER_PAGE, static_cast<int>(n));

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
            int ticketIndex = seat_indices[i];
            Menu::gotoxy(30, row);  // Cột hiển thị số ghế
            std::cout << ticketIndex + 1;
            Menu::gotoxy(69, row);  // Cột hiển thị trạng thái ghế
            std::cout << (flight->tickets[ticketIndex].CMND != nullptr ? "SOLD OUT" : "AVAILABLE");
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
        else if (key == ENTER && input != nullptr) { // Phím ENTER
            int selected = start_idx + current_column;
            int seat_index = seat_indices[selected]; // Lấy chỉ số ghế thực
            if (flight->tickets[seat_index].CMND != nullptr) {
                continue; // Ghế đã được đặt
            }
            
            // Đặt vé
            flight->tickets[seat_index].CMND = input->CMND;
            input->number_of_tickets++;
            
            // Cập nhật AVL tree
            Node *test = manager.search(manager.root, input->CMND);
            if (test == nullptr) {
                manager.root = manager.insert(manager.root, *input);
            }
            //in ra mua thành công
            // input->number_of_tickets++;
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

Flight* Console::find_info_next(Flight *cur, char *date_dep, char *destination) {
    while(cur != nullptr && !((date_dep != nullptr && strcmp(cur->date_dep.to_string(), date_dep) == 0) && (destination != nullptr && cur->destination == destination))) {
        cur = cur->next;
    } 
    return cur;
}

void Console::enter_available_flights() {
    char ch = '\0';
    unsigned int total_flights = count_flights();
    unsigned int number_of_pages = (total_flights + FLIGHTS_PER_PAGE - 1) / FLIGHTS_PER_PAGE;

    Flight **pages = new Flight*[number_of_pages];
    pages[0] = list;

    for (unsigned int i = 1; i < number_of_pages; ++i) {
        Flight *j = pages[i - 1];
        for (int count = 0; j != nullptr && count < FLIGHTS_PER_PAGE; j = j->next, ++count);
        pages[i] = j;
    }

    unsigned int cur_page = 0, cur_row = 0;
    int idx[2] = {};
    char dep_date[11] = "\0";
    char destination[LEN_DESTINATION] = "\0";

    while (true) {
        Menu::display_flight_list(cur_page, number_of_pages - 1);

        Flight *page_start = pages[cur_page];
        Flight *page_end = (cur_page + 1 < number_of_pages) ? pages[cur_page + 1] : nullptr;

        unsigned int count_on_page = 0;
        Flight *tmp = page_start;
        while (tmp != page_end && tmp != nullptr) {
            if ((strlen(dep_date) == 0 || strcmp(tmp->date_dep.to_string(), dep_date) == 0) &&
                (strlen(destination) == 0 || strcmp(tmp->destination, destination) == 0)) {
                count_on_page++;
            }
            tmp = tmp->next;
        }

        tmp = page_start;
        int i = 0;
        while (tmp != page_end && tmp != nullptr) {
            if ((strlen(dep_date) == 0 || strcmp(tmp->date_dep.to_string(), dep_date) == 0) &&
                (strlen(destination) == 0 || strcmp(tmp->destination, destination) == 0)) {
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
            }
            tmp = tmp->next;
        }

        Menu::display_enter_flight_details();
        if (cur_row >= count_on_page && cur_row <= count_on_page + 1) {
            if (cur_row == count_on_page) {
                Menu::gotoxy(70, 6 + count_on_page + 1);
                std::cout << dep_date;
                enter(dep_date, idx[0], 11, ch, [](char c) { return true; });
            } else if (cur_row == count_on_page + 1) {
                Menu::gotoxy(74, 6 + count_on_page + 1 + 2);
                std::cout << destination;
                enter(destination, idx[1], LEN_DESTINATION, ch, [](char c) { return true; });
            }
        } else {
            Menu::gotoxy(0, 0);
            ch = _getch();
        }

        if (ch == UP && cur_row > 0) {
            --cur_row;
        } else if (ch == DOWN && cur_row + 1 < count_on_page + 2) {
            ++cur_row;
        } else if (ch == RIGHT && cur_page < number_of_pages - 1) {
            ++cur_page;
            cur_row = 0;
        } else if (ch == LEFT && cur_page > 0) {
            --cur_page;
            cur_row = 0;
        } else if (ch == ESC) {
            delete[] pages;
            return;
        } else if (ch == ENTER) {
            if (cur_row >= count_on_page && cur_row <= count_on_page + 1) {
                Flight *filtered_list = nullptr;
                Flight **filtered_pages = nullptr;
                unsigned int filtered_total = 0;

                Flight *tmp = list;
                while (tmp != nullptr) {
                    if ((strlen(dep_date) == 0 || strcmp(tmp->date_dep.to_string(), dep_date) == 0) &&
                        (strlen(destination) == 0 || strcmp(tmp->destination, destination) == 0)) {
                        if (filtered_list == nullptr) {
                            filtered_list = tmp;
                        }
                        ++filtered_total;
                    }
                    tmp = tmp->next;
                }

                unsigned int filtered_pages_count = (filtered_total + FLIGHTS_PER_PAGE - 1) / FLIGHTS_PER_PAGE;
                filtered_pages = new Flight*[filtered_pages_count];
                filtered_pages[0] = filtered_list;

                tmp = filtered_list;
                for (unsigned int i = 1; i < filtered_pages_count; ++i) {
                    for (int count = 0; tmp != nullptr && count < FLIGHTS_PER_PAGE; tmp = tmp->next, ++count);
                    filtered_pages[i] = tmp;
                }

                delete[] pages;
                pages = filtered_pages;
                number_of_pages = filtered_pages_count;
                cur_page = 0;
                cur_row = 0;
                continue;
            } else {
                Flight *selected_flight = page_start;
                for (unsigned int j = 0; j < cur_row && selected_flight != nullptr; ++j) {
                
                    selected_flight = selected_flight->next;
                }
                if (input == nullptr) {
                    enter_available_tickets(selected_flight);
                } else {
                    if (selected_flight->valid_user(input->CMND)) {
                        enter_available_tickets(selected_flight);
                    }
                }
                break;
            }
        } else if (ch == TAB && input == nullptr) {
            enter_flight_manager_menu();
        }
    }

    delete[] pages;
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
