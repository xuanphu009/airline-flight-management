#include "../include/Flight.h"

Flight::Flight() {
    // Khởi tạo chuỗi ký tự rỗng để tránh trỏ lung tung gây crash
    flight_id[0] = '\0';
    destination[0] = '\0';

    plane_id = new char[LEN_PLANE_ID];
    plane_id[0] = '\0';

    date_dep = {0, 0, 0};
    time_dep = {-1, -1};

    cur_status = status::available;

    tickets = nullptr;
    total_seats = nullptr;

    next = nullptr;
}

Flight::Flight(const Flight &other) {
    // Sao chép flight_id và destination
    strncpy(this->flight_id, other.flight_id, LEN_FLIGHT_ID);
    this->flight_id[LEN_FLIGHT_ID - 1] = '\0'; // Đảm bảo null-terminated

    strncpy(this->destination, other.destination, LEN_DESTINATION);
    this->destination[LEN_DESTINATION - 1] = '\0';

    // Cấp phát và sao chép plane_id
    if (other.plane_id != nullptr) {
        this->plane_id = new char[LEN_PLANE_ID];
        strncpy(this->plane_id, other.plane_id, LEN_PLANE_ID);
        this->plane_id[LEN_PLANE_ID - 1] = '\0';
    } else {
        this->plane_id = nullptr;
    }

    // Sao chép các trường còn lại
    this->cur_status = other.cur_status;
    this->date_dep = other.date_dep;
    this->time_dep = other.time_dep;

    this->total_seats = nullptr;
    this->tickets = nullptr;


    this->next = nullptr; // Không sao chép con trỏ liên kết
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
    if (year <= 1900) // Máy bay ra đời vào khoảng thế kỉ XIX - XX
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

int* Flight::list_passengers(int &n) {
    n = 0;
    // Đếm số vé đã đặt
    for (int j = 0; j < *total_seats; j++) {
        if (tickets[j].CMND != nullptr) n++;
    }
    if (n == 0) return nullptr;
    int* ans = new int[n];
    int index = 0;
    for (int j = 0; j < *total_seats; j++) {
        if (tickets[j].CMND != nullptr) {
            ans[index++] = j;
        }
    }
    return ans;
}

int* Flight::list_available_seats(int &n) {
    n = 0;
    // Đếm số ghế trống
    for (int i = 0; i < *total_seats; i++) {
        if (tickets[i].CMND == nullptr) n++;
    }
    if (n == 0) return nullptr;

    // Cấp phát mảng đúng kích thước
    int* ans = new int[n];
    int index = 0;

    // Lưu chỉ số các ghế trống
    for (int i = 0; i < *total_seats; i++) {
        if (tickets[i].CMND == nullptr) {
            ans[index++] = i;
        }
    }
    return ans;
}
