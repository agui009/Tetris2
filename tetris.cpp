// tetris.cpp
// Դ�ļ����������ֶ���˹������Ϸ�ĺ����Ķ���

#include "tetris.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;
extern const int COLS; // ���������

// ������ɫ����
Color colors[NUMS] = {
    RED, // 0
    GREEN, // 1
    YELLOW, // 2
    BLUE, // 3
    PURPLE, // 4
    CYAN, // 5
    WHITE, // 6
    BLACK, // 7
    RED, // 8
    GREEN // 9
};
// �������������
int area[ROWS][COLS] = { 0 };

// ���嵱ǰ���ֵ�����
int cur_num = 0; // ��ǰ���ֵ�����
int cur_shape = 0; // ��ǰ���ֵ���̬
int cur_row = 0; // ��ǰ���ֵ�������
int cur_col = 0; // ��ǰ���ֵ�������

// ������һ�����ֵ�����
int next_num = 0; // ��һ�����ֵ�����
int next_shape = 0; // ��һ�����ֵ���̬

// ������Ϸ������
int score = 0; // ��ǰ�÷�
int delay = DELAY; // ��ǰ�����ӳ�
bool pause = false; // �Ƿ���ͣ
bool over = false; // �Ƿ����

// ��ȡ�û�����
int get_key()
{
    if (_kbhit()) { // ����а�������
        int key = _getch(); // ��ȡ����
        return key;
    }
    else {
        return -1;
    }
}

// �ӳ�
void delay_ms(int milliseconds)
{
    Sleep(milliseconds);
}

// ���ÿ���̨����λ��
void set_cursor(int x, int y) {
    // ֱ��ʹ��SHORT���͵ı�����Ϊ����
    COORD pos = { (SHORT)x,(SHORT)y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

// ���ÿ���̨�ı�����ɫ
void set_color(Color color) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, color);
}

// ���ؿ���̨���
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hOut, &cursor_info);
}

// ��ʾ����̨���
void show_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hOut, &cursor_info);
}

// ��ȡ��һ�����ֵ�����
int get_next_num(const bool new_seed, const unsigned int seed) {
    if (new_seed)
        srand(seed);

    return rand() % 10;
}

// ������һ������
void generate_next_num() {
    next_num = get_next_num(true, 12345);
    next_shape = rand() % SHAPES;
}

// ���ɵ�ǰ����
void generate_cur_num() {
    cur_num = next_num;
    cur_shape = next_shape;
    cur_row = 0;
    cur_col = (COLS - MY_SIZE) / 2;
    generate_next_num();
}

// ����һ��С����
void draw_block(int x, int y, Color color)
{
    set_cursor(x, y);
    set_color(color);
    if (color == GREEN) {
        cout << "��"; // �����ɫ��С����
    }
    else {
        cout << " "; // �����ɫ��С����
    }
}


// ����һ��С����
void erase_block(int x, int y) {
    set_cursor(x, y);
    set_color(BLACK);
    cout << " "; // ����ո�
}

// ����һ������
void draw_num(int num, int row, int col, Color color)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                draw_block(x * 2, y, color); // ������ɫ��С����
            }
            else {
                draw_block(x * 2, y, BLACK); // ���ƺ�ɫ��С����
            }
        }
    }
}


// ����һ������
void erase_num(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                erase_block(x * 2, y); // ����С����
            }
        }
    }
}

// ��������
void draw_area() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] > 0) {
                draw_block(j * 2, i, colors[area[i][j] - 1]);
            }
        }
    }
}

// ��������
void erase_area() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] > 0) {
                erase_block(j * 2, i);
            }
        }
    }
}

// ���Ʊ߿�
void draw_border() {
    set_color(WHITE);
    for (int i = 0; i < ROWS; i++) {
        set_cursor(0, i);
        cout << "��";
        set_cursor((COLS + 1) * 2, i);
        cout << "��";
    }
    for (int i = 0; i <= COLS + 1; i++) {
        set_cursor(i * 2, ROWS);
        cout << "��";
    }
}


// ������ʾ��Ϣ



void draw_info() {
    set_cursor((COLS + 3) * 2, 6);
    cout << "��ǰ�÷֣�" << score;
    set_cursor((COLS + 3) * 2, 8);
    cout << "���ϼ���ת";
    set_cursor((COLS + 3) * 2, 9);
    cout << "�����Ҽ��ƶ�";
    set_cursor((COLS + 3) * 2, 10);
    cout << "���¼�����";
    set_cursor((COLS + 3) * 2, 11);
    cout << "���ո����ͣ";
    set_cursor((COLS + 3) * 2, 12);
    cout << "��ESC���˳�";
}



// ��������Ƿ�����ƶ�
bool check_move(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                if (x < 0 || x >= COLS || y >= ROWS || area[y][x] != 0) {
                    return false; // ��������߽������������С���飬�����ƶ�
                }
            }
        }
    }
    return true;
}

// �����̶ֹ�������
void fix_num(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                area[y][x] = num + 1; // ����ɫ��С����̶�������
            }
        }
    }
}

// ��������
void eliminate_row()
{
    int count = 0; // ����������
    for (int i = 0; i < ROWS; i++) {
        bool full = true; // �Ƿ�����
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] == 0 || area[i][j] == BLACK + 1) { // ����пո���ɫ��С����
                full = false;
                break;
            }
        }
        if (full) {
            count++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLS; j++) {
                    area[k][j] = area[k - 1][j];
                }
            }
            for (int j = 0; j < COLS; j++) {
                area[0][j] = 0;
            }
        }
    }
    if (count > 0) {
        score += SCORES[count]; // ���ӵ÷�
        delay -= SPEEDUP * (score / 15); // �����ӳ�
        if (delay < MIN_DELAY) {
            delay = MIN_DELAY; // ����ӳ�С����С�ӳ٣�������Ϊ��С�ӳ�
        }
        erase_area(); // ��������
        draw_area(); // ��������
        draw_info(); // ������ʾ��Ϣ
    }
}


// ��Ϸ��ʼ��
void game_init() {
    // ��ʽ�ؽ�time(NULL)ת��Ϊunsigned int����
    srand((unsigned int)time(NULL)); // �������������
    hide_cursor(); // ���ع��
    system("cls"); // ����
    draw_border(); // ���Ʊ߿�
    draw_info(); // ������ʾ��Ϣ
    generate_next_num(); // ������һ������
    generate_cur_num(); // ���ɵ�ǰ����
    draw_num(cur_num, cur_row, cur_col, colors[cur_num]); // ���Ƶ�ǰ����
}

// ��Ϸ����
void game_over() {
    over = true; // ���ý�����־
    set_color(WHITE);
    set_cursor(COLS, ROWS / 2);
    cout << "��Ϸ������ ";
    set_cursor(COLS, ROWS / 2 + 1);
    cout << "��������˳�";
    show_cursor(); // ��ʾ���
}

// ��Ϸ��ͣ
// ��Ϸ��ͣ
void game_pause() {
    pause = !pause; // �л���ͣ״̬
    set_color(WHITE);
    if (pause) {
        set_cursor(COLS, ROWS / 2);
        cout << "��Ϸ��ͣ�� ";
    }
    else {
        set_cursor(COLS, ROWS / 2);
        cout << "         "; // ����ո񸲸�ԭ������ʾ
    }
}



void game_loop()
{
    int num = get_next_num(true, time(0)); // ��ǰ������
    int next_num = get_next_num(); // ��һ������
    int row = 0; // ��ǰ����
    int col = COLS / 2 - 1; // ��ǰ����

    while (true) {
        draw_num(num, row, col, GREEN); // ���Ƶ�ǰ������
        draw_num(next_num, 0, COLS + 2, GREEN); // ������һ������

        int key = get_key(); // ��ȡ����
        if (key == 'q') { // �������q��
            break; // �˳���Ϸ
        }
        else if (key == 'a') { // �������a��
            erase_num(num, row, col); // ������ǰ������
            if (check_move(num, row, col - 1)) { // ������������ƶ�
                col--; // �����ƶ�
            }
        }
        else if (key == 'd') { // �������d��
            erase_num(num, row, col); // ������ǰ������
            if (check_move(num, row, col + 1)) { // ������������ƶ�
                col++; // �����ƶ�
            }
        }
        else if (key == 's') { // �������s��
            erase_num(num, row, col); // ������ǰ������
            if (check_move(num, row + 1, col)) { // ������������ƶ�
                row++; // �����ƶ�
            }
            else { // ������������ƶ�
                fix_num(num, row, col); // ����ǰ�����̶ֹ�������
                eliminate_row(); // ��������
                num = next_num; // ��һ�����ֱ�Ϊ��ǰ������
                next_num = get_next_num(); // ������һ������
                row = 0; // ��ǰ���б�Ϊ0
                col = COLS / 2 - 1; // ��ǰ���б�ΪCOLS / 2 - 1
                if (!check_move(num, row, col)) { // ������������ƶ�
                    break; // �˳���Ϸ
                }
            }
        }

        draw_num(num, row, col, GREEN); // ���Ƶ�ǰ������
        draw_num(next_num, 0, COLS + 2, GREEN); // ������һ������
        delay_ms(delay); // �ӳ�
    }
}