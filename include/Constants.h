#pragma once

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    char _getch();
#endif


const int LEN_FLIGHT_ID = 15;
const int LEN_DESTINATION = 16;
const int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
const int LEN_PLANE_ID = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300;
const int LEN_CMND = 15;
const int SEATS_PER_PAGE = 10;

// extern const int LEN_FLIGHT_ID = 15, LEN_DESTINATION = 16;
// extern const int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
// extern const int LEN_PLANE_ID = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300; 
// extern const int LEN_CMND = 15;
// //extern const int UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 13;
// extern const int SEATS_PER_PAGE = 10;
// //extern const int BACKSPACE = 8; // Thêm dòng này

// template <typename... Conds>
// void enter(char *str, int &index, int max_len, char &ch, Conds... conditions) {
//             //char *str : nhập str
//             //int &index: nhập tại ví trị index của str
//             //char &ch: nằm bên ngoài hàmm để kiểm soát nhập up/down/....
//             // auto... conditions: add điều kiện cho valid cho str
//     while (true) {
//         ch = _getch();

//         // Loại bỏ mã tiền tố của phím UP, DOWN
//         if (ch == -32 || ch == 224) {
//             ch = _getch(); // Bỏ qua mã tiền tố, lấy mã thực
//             return; // Thoát nhập ngay khi gặp UP/DOWN
//         }

//         if (ch == ENTER) return;

//         if (ch == BACKSPACE) { // Nhấn Backspace
//             if (index > 0) {
//                 std::cout << "\b \b"; // Xóa ký tự trên màn hình
//                 str[--index] = '\0';
//             }
//         } else if (index < max_len - 1) { // Chưa vượt quá giới hạn
//             if ((... && conditions(ch))) { // Fold expression kiểm tra nhiều điều kiện
//                 std::cout << ch;
//                 str[index++] = ch;
//                 str[index] = '\0';
//             }
//         }
//     }
// }
template <typename... Conds>
void enter(char *str, int index, int max_len, char &ch, Conds... conditions) {
            //char *str : nhập str
            //int &index: nhập tại ví trị index của str
            //char &ch: nằm bên ngoài hàmm để kiểm soát nhập up/down/....
            // auto... conditions: add điều kiện cho valid cho str
    while (true) {
        ch = _getch();

        if (ch == '\x1B') { // phím mũi tên (ESC = 0x1B), bỏ 2 ký tự tiếp theo
            _getch();
            _getch();
            continue;
        }
        if (ch == '[' || ch == ']') { // chặn phím `[` và `]`
            continue;
        }
        if (ch == '\n' || ch == '\r') break; // enter, kết thúc


        if ((ch == '\b' || ch == 127) && index > 0) { // Nhấn Backspace
            std::cout << "\b \b" << std::flush; // Xóa ký tự trên màn hình
            str[--index] = '\0';
            continue;
        }
       
        else if (index < max_len - 1) { // Chưa vượt quá giới hạn
            if ((... && conditions(ch))) { // Fold expression kiểm tra nhiều điều kiện
                std::cout << ch;
                str[index++] = ch;
                str[index] = '\0';
            }
        }
    }
}


