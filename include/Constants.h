#pragma once
extern const int LEN_FLIGHT_CODE = 15, LEN_DESTINATION = 16;
extern const int LEN_LAST_NAME = 12, LEN_FIRST_NAME = 12;
extern const int LEN_FLIGHT_NUMBER = 15, LEN_PLANE_TYPE = 40, MAX_PLANE = 300; 
extern const int LEN_CMND = 15;
extern const int UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 13;



template <typename... Conds>
void enter(char *str, int &index, int max_len, char &ch, auto... conditions) {
            //char *str : nhập str
            //int &index: nhập tại ví trị index của str
            //char &ch: nằm bên ngoài hàmm để kiểm soát nhập up/down/....
            // auto... conditions: add điều kiện cho valid cho str
    while (true) {
        ch = _getch();

        // Loại bỏ mã tiền tố của phím UP, DOWN
        if (ch == -32 || ch == 224) {
            ch = _getch(); // Bỏ qua mã tiền tố, lấy mã thực
            return; // Thoát nhập ngay khi gặp UP/DOWN
        }

        if (ch == ENTER) return;

        if (ch == BACKSPACE) { // Nhấn Backspace
            if (index > 0) {
                cout << "\b \b"; // Xóa ký tự trên màn hình
                str[--index] = '\0';
            }
        } else if (index < max_len - 1) { // Chưa vượt quá giới hạn
            if ((... && conditions(ch))) { // Fold expression kiểm tra nhiều điều kiện
                cout << ch;
                str[index++] = ch;
                str[index] = '\0';
            }
        }
    }
}