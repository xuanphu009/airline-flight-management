#pragma once
#include "Ticket.h"
#include "Constants.h"

struct Flight {
    char flight_code[LEN_FLIGHT_CODE];
    char departure[LEN_DEPARTURE];
    enum struct Status {
        cancelled = 0,    // Hủy chuyến
        available = 1,    // Còn vé
        sold_out = 2,      // Hết vé
        completed = 3     // Hoàn tất
    } cur_status;
    char flight_code[LEN_FLIGHT_CODE];

    Ticket *list; // khi khởi tạo chuyến bay list = new Ticket[số chỗ]

    // danh sách chuyến bay trỏ đến nhau
    Flight *next;
    Flight();
};