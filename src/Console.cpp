#include "include/Console.h"



void Console::enter_available_tickets(Flight *flight) {
    int current_page = 0, current_column = 0;
    int max_pages = (flight.total_seats) / SEATS_PER_PAGE + !!(flight.total_seats % SEATS_PER_PAGE) - 1; // Số trang

    while (true) {
        int start_idx = current_page * SEATS_PER_PAGE;
        int end_idx = std::min(start_idx + SEATS_PER_PAGE, flight.total_seats);
        Menu::display_available_tickets(flight, current_page, max_pages, start_idx, end_idx, current_column);

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