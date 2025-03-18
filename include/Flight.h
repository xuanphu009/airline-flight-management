#pragma once
#include "Ticket.h"
#include "Constants.h"
#include <cstring>

struct Flight {
    char flight_code[LEN_FLIGHT_CODE];
    struct date_departure {
        char day[3], month[3], year[5];
    } date_dep;
    struct time_departure {
        char hour[3], minute[3];
    } time_dep;
    
    char destination[LEN_DESTINATION]; 
    char flight_number[LEN_FLIGHT_NUMBER];
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
    bool valid_CMND(char *CMND) {
        for(int i = 1; i < sizeof(tickets)/sizeof(tickets[0]); ++i) {
            if(strcmp(tickets[i].CMND, CMND) == 0) return false;
        }
        return true;
    }
    bool valid_seat(unsigned int seat) {
        for(int i = 1; i < sizeof(tickets)/sizeof(tickets[0]); ++i) {
            if(tickets[i].seat == seat && tickets[i].CMND != '\0') return false;
        }
        return true;
    }
};