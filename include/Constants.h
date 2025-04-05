#pragma once
#include "Console.h"
extern const int LEN_FLIGHT_CODE = 15, LEN_DESTINATION = 16;
extern const int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
extern const int LEN_FLIGHT_NUMBER = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300;
extern const int LEN_CMND = 15;
extern const int UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 13;

template <typename... Conds>
void enter(char *str, int &index, int max_len, char &ch, auto... conditions)
{
    while (true)
    {
        ch = _getch(); 

        if (ch == -32 || ch == 224)
        {
            ch = _getch();
            return; 
        }

        if (ch == ENTER)
            return; 

        if (ch == BACKSPACE)
        { 
            if (index > 0)
            {
                std::cout << "\b \b"; 
                str[--index] = '\0';
            }
        }
        else if (index < max_len - 1)
        { 
            if ((... && conditions(ch)))
            { 
                std::cout << ch;
                str[index++] = ch;
                str[index] = '\0';
            }
        }
    }
}