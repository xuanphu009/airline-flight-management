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
char* time_departure::to_string() {
    char* ans = new char[6]; // Cấp phát động
    snprintf(ans, 6, "%02d:%02d", hour, minute);
    return ans;
}

char* date_departure::to_string() {
    char* ans = new char[11]; // Cấp phát động
    snprintf(ans, 11, "%02d/%02d/%04d", day, month, year);
    return ans;
}

std::ostream& operator<<(std::ostream &out, const date_departure &x) {
    if (x.day < 10) out << "0";
    out << x.day << "/";
    if (x.month < 10) out << "0";
    out << x.month << "/";
    out << x.year;
    return out;
}

// Overload for std::istream
std::istream& operator>>(std::istream &in, date_departure &x) {
    char delimiter1, delimiter2;
    in >> x.day >> delimiter1 >> x.month >> delimiter2 >> x.year;
    return in;
}
std::ofstream& operator<<(std::ofstream &out, const date_departure &x) {
    if (x.day < 10) out << "0";
    out << x.day << " / ";
    if (x.month < 10) out << "0";
    out << x.month << " / ";
    out << x.year;
    return out;
}

bool date_departure::operator == (const date_departure &x) {
    return this->day == x.day && this->month == x.month && this->year == x.year;
} 


std::ofstream& operator<<(std::ofstream &out, const time_departure &t) {
    if (t.hour < 10) out << "0";
    out << t.hour << " : ";
    if (t.minute < 10) out << "0";
    out << t.minute;
    return out;
}
std::ostream& operator<<(std::ostream &out, const time_departure &t) {
    if (t.hour < 10) out << "0";
    out << t.hour << ":";
    if (t.minute < 10) out << "0";
    out << t.minute;
    return out;
}
std::istream& operator>>(std::istream &in, time_departure &t) {
    char delimiter;
    in >> t.hour >> delimiter >> t.minute;
    return in;
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

// void Flight::set_status(status x);
std::ostream& operator<<(std::ostream &out, const Flight &other) {
    out << other.flight_id << std::endl
    << other.plane_id << std::endl
    << other.destination << std::endl
    << other.date_dep << std::endl
    << other.time_dep << std::endl
    << *other.total_seats << std::endl;
    switch (other.cur_status) {
        case status::cancelled:
            out << "cancelled";
            break;
        case status::available:
            out << "available";
            break;
        case status::sold_out:
            out << "sold out";
            break;
        case status::completed:
            out << "completed";
            break;
    }
    out << std::endl;

    for(int i = 0; i < *other.total_seats; ++i) {
        if(other.tickets[i].CMND != nullptr) {
            out << i << " " << other.tickets[i].CMND << std::endl;
        }
    }
    return out;
}
std::ofstream& operator<<(std::ofstream &out, const Flight &other) {
    out << other.flight_id << std::endl
    << other.plane_id << std::endl
    << other.destination << std::endl
    << other.date_dep << std::endl
    << other.time_dep << std::endl
    << *other.total_seats << std::endl;
    switch (other.cur_status) {
        case status::cancelled:
            out << "cancelled";
            break;
        case status::available:
            out << "available";
            break;
        case status::sold_out:
            out << "sold out";
            break;
        case status::completed:
            out << "completed";
            break;
    }
    out << std::endl;

    for(int i = 0; i < *other.total_seats; ++i) {
        if(other.tickets[i].CMND != nullptr) {
            out << i << " " << other.tickets[i].CMND << std::endl;
        }
    }
    return out;
}
std::ifstream& operator>>(std::ifstream &in, Flight &other) {
    other.plane_id = new char[LEN_FLIGHT_ID];
    other.total_seats = new unsigned int;
    in >> other.flight_id
       >> other.plane_id;
    in.ignore();
    in.getline(other.destination, LEN_DESTINATION);
    in   >> other.date_dep
       >> other.time_dep
       >> *other.total_seats;

    std::string st;
    in >> st;
    if (st == "cancelled")     other.cur_status = status::cancelled;
    else if (st == "available") other.cur_status = status::available;
    else if (st == "sold")     other.cur_status = status::sold_out, in.ignore();
    else if (st == "completed") other.cur_status = status::completed;

    // Allocate memory for tickets array
    other.tickets = new Ticket[*other.total_seats];
    for (unsigned int i = 0; i < *other.total_seats; ++i) {
        other.tickets[i].CMND = nullptr; // Initialize all tickets to nullptr
    }

    // Read ticket data (seat index and CMND)
    int idx;
    char CMND[LEN_CMND];
    while (in >> idx >> CMND) {
        other.tickets[idx].CMND = new char[LEN_CMND];
        strcpy(other.tickets[idx].CMND, CMND); // Copy CMND into the ticket
    }

    return in;
}