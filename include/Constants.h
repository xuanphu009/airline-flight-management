#pragma once

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    char _getch() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif


extern const int LEN_FLIGHT_ID = 15, LEN_DESTINATION = 16;
extern const int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
extern const int LEN_PLANE_ID = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300; 
extern const int LEN_CMND = 15;
#if defined(_WIN32) || defined(_WIN64)
    extern const int UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 13, BACKSPACE = 8;
#else
    extern const int UP = 65, DOWN = 66, LEFT = 68, RIGHT = 67, ENTER = 10, BACKSPACE = 127, ESC = 27;
#endif

extern const int SEATS_PER_PAGE = 10;


template <typename... Conds>
void enter(char *str, int &index, int max_len, char &ch, Conds... conditions) {
    //char *str : nhập str            
    //int &index: nhập tại ví trị index của str
   //char &ch: nằm bên ngoài hàmm để kiểm soát nhập up/down/....      
   // auto... conditions: add điều kiện cho valid cho str
    while (true) {
        ch = _getch();

        // Xử lý phím mũi tên
#ifdef _WIN32
        if (ch == -32 || ch == 224) { // Phím mũi tên trên Windows có mã tiền tố
            ch = _getch(); 
            return; // Thoát ngay khi gặp UP/DOWN
        }
#else
        if (ch == ESC) { // Trên macOS, phím mũi tên bắt đầu với ESC
            if (_getch() == '[') { // Kiểm tra ký tự tiếp theo
                ch = _getch(); // Lấy mã thực tế của phím
                return; // Thoát ngay khi gặp UP/DOWN
            }
        }
#endif

        if (ch == ENTER || ch == '\n') return; // ENTER trên macOS là '\n'

        if (ch == BACKSPACE) {
            if (index > 0) {
                std::cout << "\b \b"; // Xóa ký tự trên màn hình
                str[--index] = '\0';
            }
        } else if (index < max_len - 1) { // Chưa vượt quá giới hạn
            if ((... && conditions(ch))) { // Fold expression kiểm tra nhiều điều kiện
                std::cout << ch;
                str[index++] = ch;
                str[index] = '\0';
            }
        }
    }
}

