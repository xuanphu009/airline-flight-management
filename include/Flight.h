#pragma once
#include "Ticket.h"
#include "Constants.h"
#include <cstring>
#include <fstream>
struct date_departure {
    int day, month, year;

    char* to_string();

    // Overload for std::ofstream
    friend std::ofstream& operator<<(std::ofstream &out, const date_departure &x);

    bool operator == (const date_departure &x);
    // Overload for std::ostream (e.g., std::cout)
    friend std::ostream& operator<<(std::ostream &out, const date_departure &x);

    // Overload for std::istream
    friend std::istream& operator>>(std::istream &in, date_departure &x);

};
struct time_departure {
    int hour, minute;
    char* to_string();
    // Overload for std::ofstream
    friend std::ofstream& operator<<(std::ofstream &out, const time_departure &t);
    friend std::ostream& operator<<(std::ostream &out, const time_departure &t);
    friend std::istream& operator>>(std::istream &in, time_departure &t);
};

enum struct status {
    cancelled = 0,    // Hủy chuyến
    available = 1,    // Còn vé
    sold_out = 2,      // Hết vé
    completed = 3     // Hoàn tất
};

struct Flight {
    char flight_id[LEN_FLIGHT_ID];
    char destination[LEN_DESTINATION]; 
    char *plane_id = nullptr;

    date_departure date_dep;
    time_departure time_dep;
    
    status cur_status;

    Ticket *tickets; // khi khởi tạo chuyến bay list = new Ticket[số chỗ]
    unsigned int *total_seats;

    // danh sách chuyến bay trỏ đến nhau

    Flight *next;

    Flight(); // Constructor mặc định
    Flight(const Flight &other); // Copy constructor
    // ~Flight();

    bool valid_user(char *CMND);
    bool valid_time(int hour, int minute);
    bool valid_date(int day, int month, int year);
    int* list_passengers(int &n);
    int* list_available_seats(int &n);
    void set_status(status x);
    friend std::ostream& operator<<(std::ostream &out, const Flight &other);
    friend std::ofstream& operator<<(std::ofstream &out, const Flight &other);
    friend std::ifstream& operator>>(std::ifstream &in, Flight &other);
};