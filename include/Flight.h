#pragma once
#include "Ticket.h"
#include "Constants.h"
#include <cstring>
#include <fstream>

struct Flight {
    char flight_id[LEN_FLIGHT_ID];
    struct date_departure {
        unsigned short day, month, year;
    } date_dep;
    struct time_departure {
        unsigned short hour, minute;
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
    unsigned int *total_seats;

    // danh sách chuyến bay trỏ đến nhau

    Flight *next;


    Flight();

};
