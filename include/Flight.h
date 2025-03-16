#pragma once
#include "Ticket.h"
#include "Constants.h"
#include <cstring>

struct Flight {
    char flight_code[LEN_FLIGHT_CODE];
    //thiếu ngày giờ
    char departure[LEN_DEPARTURE]; 
    char flight_number[LEN_FLIGHT_NUMBER];
    enum struct Status {
        cancelled = 0,    // Hủy chuyến
        available = 1,    // Còn vé
        sold_out = 2,      // Hết vé
        completed = 3     // Hoàn tất
    } cur_status;

    Ticket *tickets; // khi khởi tạo chuyến bay list = new Ticket[số chỗ]

    // danh sách chuyến bay trỏ đến nhau
    Flight *next;
    Flight();

};