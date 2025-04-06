// Constants.h
#pragma once

#include <iostream>
#include <cstring>

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

constexpr int LEN_FLIGHT_ID = 15, LEN_DESTINATION = 16;
constexpr int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
constexpr int LEN_PLANE_ID = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300;
constexpr int LEN_CMND = 15;
constexpr int UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 13;
constexpr int SEATS_PER_PAGE = 10, FLIGHTS_PER_PAGE = 10;
constexpr int BACKSPACE = 8;

template <typename... Conds>
void enter(char *str, int &index, int max_len, char &ch, Conds... conditions) {
    while (true) {
        ch = _getch();

        // Xử lý phím mũi tên
#ifdef _WIN32
        if (ch == -32 || ch == 224) { 
            ch = _getch(); 
            return; 
        }
#else
        if (ch == 27) { // ESC
            if (_getch() == '[') {
                ch = _getch();
                return;
            }
        }
        if (ch == ENTER || ch == '\n') return;
#endif

        if (ch == BACKSPACE || ch == 127) {
            if (index > 0) {
                std::cout << "\b \b";
                str[--index] = '\0';
            }
        } else if (index < max_len - 1) {
            // Sử dụng fold expression để kiểm tra tất cả điều kiện
            if ((conditions(ch) && ...)) {
                std::cout << ch;
                str[index++] = ch;
                str[index] = '\0';
            }
        }
    }
}