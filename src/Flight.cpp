#include "../include/Flight.h"


Flight::Flight() : next(nullptr) {}

bool Flight::valid_user(char *CMND) {
    int cnt = 0;
    for(int i = 0; i < *total_seats; ++i) {
        if(tickets[i].CMND != nullptr && strcmp(tickets[i].CMND, CMND) == 0) {
            cnt += (tickets[i].CMND != nullptr);
            return false;
        }
    }
    if(cnt == *total_seats) return false;
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