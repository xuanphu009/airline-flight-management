#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cctype>

#define ENTER 13
#define BACKSPACE 8

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void enter(char *str, int &index, int max_len, char &ch, auto... conditions)
{
    while (true)
    {
        ch = _getch();

        if (ch == -32 || ch == 224) // Phím di?u hu?ng
        {
            _getch();
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

struct date_departure
{
    char day[3]{}, month[3]{}, year[5]{};

    friend std::ofstream &operator<<(std::ofstream &out, const date_departure &d)
    {
        out << d.day << "/" << d.month << "/" << d.year;
        return out;
    }
};

void input_date(date_departure &date_dep)
{
    int index_day = 0, index_month = 0, index_year = 0;
    char ch;

    gotoxy(30, 3); // Nh?p ngày
    enter(date_dep.day, index_day, 3, ch, [](char c)
          { return isdigit(c); });

    gotoxy(33, 3); // D?u "/"
    std::cout << "/";

    gotoxy(34, 3); // Nh?p tháng
    enter(date_dep.month, index_month, 3, ch, [](char c)
          { return isdigit(c); });

    gotoxy(37, 3); // D?u "/"
    std::cout << "/";

    gotoxy(38, 3); // Nh?p nam
    enter(date_dep.year, index_year, 5, ch, [](char c)
          { return isdigit(c); });
}

int main()
{
    system("cls");
    std::cout << "=======================================\n";
    std::cout << "   ENTER FLIGHT SEARCH DETAILS\n";
    std::cout << "=======================================\n";
    std::cout << "  Date of Departure (dd/mm/yyyy): \n";
    std::cout << "=======================================\n";

    date_departure date_dep;
    input_date(date_dep);

    std::cout << "\n\nB?n dã nh?p ngày: " << date_dep.day << "/" << date_dep.month << "/" << date_dep.year << std::endl;

    return 0;
}
