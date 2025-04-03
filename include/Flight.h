#pragma once
#include "Ticket.h"
#include "Constants.h"
#include "Menu.h"
#include <cstring>
#include <fstream>

struct Flight {
    char flight_id[LEN_FLIGHT_ID];
    struct date_departure {
        unsigned short day, month, year;

        friend std::ofstream &operator<<(std::ofstream &out, const date_departure &d) {
            out << d.day << "/" << d.month << "/" << d.year;
            return out; 
        }
    } date_dep;
    struct time_departure {
        unsigned short hour, minute;

        friend std::ofstream &operator<<(std::ofstream &out, const time_departure &t) {
            out << t.hour << ":" << t.minute;
            return out; 
        }
    } time_dep;
    
    char destination[LEN_DESTINATION]; 
    char *plane_id = nullptr;
    enum struct status {
        cancelled = 0,    // Hủy chuyến
        available = 1,    // Còn vé
        sold_out = 2,      // Hết vé
        completed = 3     // Hoàn tất
    } cur_status;

    Ticket *tickets; // khi khởi tạo chuyến bay list = new Ticket[số chỗ]

    // danh sách chuyến bay trỏ đến nhau
    Flight *next;


    Flight();
    ~Flight();

    void create_flight();
    void update_departure_time();
    void cancel_flight();

    void input_flight(Flight &other);
    void input_flight_update(Flight &other);

};
