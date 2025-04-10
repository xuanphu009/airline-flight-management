#include "../include/Flight.h"


Flight::Flight() {
    // Khởi tạo chuỗi ký tự rỗng để tránh trỏ lung tung gây crash
    flight_id[0] = '\0';
    destination[0] = '\0';

    plane_id = new char[LEN_PLANE_ID];
    plane_id[0] = '\0';

    date_dep = {0, 0, 0}; // hoặc ngày nào đó hợp lệ
    time_dep = {0, 0};

    cur_status = status::available;

    tickets = nullptr;
    total_seats = nullptr;

    next = nullptr;
}
Flight::~Flight() {
    if (total_seats) {  // Kiểm tra NULL trước khi delete
        delete total_seats;
        total_seats = nullptr;
    }
    
    if (tickets) {  // Kiểm tra NULL trước khi delete[]
        delete[] tickets;
        tickets = nullptr;
    }
}


bool Flight::valid_user(char *CMND) {
    for(int i = 0; i < *total_seats; ++i) {
        if(tickets[i].CMND != nullptr && strcmp(tickets[i].CMND, CMND) == 0) return false;
    }
    return true;
}
bool Flight::valid_time(int hour, int minute) {
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}
bool Flight::valid_date(int day, int month, int year) {
    if (year < 1)
        return false;

    if (month < 1 || month > 12)
        return false;

    // số ngày của từng tháng
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 
                            31, 31, 30, 31, 30, 31 };

    // năm nhuận
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap && month == 2)
        days_in_month[1] = 29;

    // kiểm tra ngày
    if (day < 1 || day > days_in_month[month - 1])
        return false;

    return true;
}
