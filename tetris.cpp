// tetris.cpp
// 源文件，包含数字俄罗斯方块游戏的函数的定义

#include "tetris.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;
extern const int COLS; // 区域的列数

// 定义颜色数组
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
// 定义区域的数据
int area[ROWS][COLS] = { 0 };

// 定义当前数字的数据
int cur_num = 0; // 当前数字的种类
int cur_shape = 0; // 当前数字的形态
int cur_row = 0; // 当前数字的行坐标
int cur_col = 0; // 当前数字的列坐标

// 定义下一个数字的数据
int next_num = 0; // 下一个数字的种类
int next_shape = 0; // 下一个数字的形态

// 定义游戏的数据
int score = 0; // 当前得分
int delay = DELAY; // 当前下落延迟
bool pause = false; // 是否暂停
bool over = false; // 是否结束

// 获取用户输入
int get_key()
{
    if (_kbhit()) { // 如果有按键按下
        int key = _getch(); // 获取按键
        return key;
    }
    else {
        return -1;
    }
}

// 延迟
void delay_ms(int milliseconds)
{
    Sleep(milliseconds);
}

// 设置控制台光标的位置
void set_cursor(int x, int y) {
    // 直接使用SHORT类型的变量作为参数
    COORD pos = { (SHORT)x,(SHORT)y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

// 设置控制台文本的颜色
void set_color(Color color) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, color);
}

// 隐藏控制台光标
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hOut, &cursor_info);
}

// 显示控制台光标
void show_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hOut, &cursor_info);
}

// 获取下一个数字的种类
int get_next_num(const bool new_seed, const unsigned int seed) {
    if (new_seed)
        srand(seed);

    return rand() % 10;
}

// 生成下一个数字
void generate_next_num() {
    next_num = get_next_num(true, 12345);
    next_shape = rand() % SHAPES;
}

// 生成当前数字
void generate_cur_num() {
    cur_num = next_num;
    cur_shape = next_shape;
    cur_row = 0;
    cur_col = (COLS - MY_SIZE) / 2;
    generate_next_num();
}

// 绘制一个小方块
void draw_block(int x, int y, Color color)
{
    set_cursor(x, y);
    set_color(color);
    if (color == GREEN) {
        cout << "■"; // 输出绿色的小方块
    }
    else {
        cout << " "; // 输出黑色的小方块
    }
}


// 擦除一个小方块
void erase_block(int x, int y) {
    set_cursor(x, y);
    set_color(BLACK);
    cout << " "; // 输出空格
}

// 绘制一个数字
void draw_num(int num, int row, int col, Color color)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                draw_block(x * 2, y, color); // 绘制绿色的小方块
            }
            else {
                draw_block(x * 2, y, BLACK); // 绘制黑色的小方块
            }
        }
    }
}


// 擦除一个数字
void erase_num(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                erase_block(x * 2, y); // 擦除小方块
            }
        }
    }
}

// 绘制区域
void draw_area() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] > 0) {
                draw_block(j * 2, i, colors[area[i][j] - 1]);
            }
        }
    }
}

// 擦除区域
void erase_area() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] > 0) {
                erase_block(j * 2, i);
            }
        }
    }
}

// 绘制边框
void draw_border() {
    set_color(WHITE);
    for (int i = 0; i < ROWS; i++) {
        set_cursor(0, i);
        cout << "■";
        set_cursor((COLS + 1) * 2, i);
        cout << "■";
    }
    for (int i = 0; i <= COLS + 1; i++) {
        set_cursor(i * 2, ROWS);
        cout << "■";
    }
}


// 绘制提示信息



void draw_info() {
    set_cursor((COLS + 3) * 2, 6);
    cout << "当前得分：" << score;
    set_cursor((COLS + 3) * 2, 8);
    cout << "按上键旋转";
    set_cursor((COLS + 3) * 2, 9);
    cout << "按左右键移动";
    set_cursor((COLS + 3) * 2, 10);
    cout << "按下键加速";
    set_cursor((COLS + 3) * 2, 11);
    cout << "按空格键暂停";
    set_cursor((COLS + 3) * 2, 12);
    cout << "按ESC键退出";
}



// 检查数字是否可以移动
bool check_move(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                if (x < 0 || x >= COLS || y >= ROWS || area[y][x] != 0) {
                    return false; // 如果超出边界或者碰到其他小方块，则不能移动
                }
            }
        }
    }
    return true;
}

// 将数字固定到区域
void fix_num(int num, int row, int col)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            int x = col + j;
            int y = row + i;
            if (shapes[num][i][j] == 1) {
                area[y][x] = num + 1; // 将绿色的小方块固定到区域
            }
        }
    }
}

// 消除满行
void eliminate_row()
{
    int count = 0; // 消除的行数
    for (int i = 0; i < ROWS; i++) {
        bool full = true; // 是否满行
        for (int j = 0; j < COLS; j++) {
            if (area[i][j] == 0 || area[i][j] == BLACK + 1) { // 如果有空格或黑色的小方块
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
        score += SCORES[count]; // 增加得分
        delay -= SPEEDUP * (score / 15); // 调整延迟
        if (delay < MIN_DELAY) {
            delay = MIN_DELAY; // 如果延迟小于最小延迟，则设置为最小延迟
        }
        erase_area(); // 擦除区域
        draw_area(); // 绘制区域
        draw_info(); // 绘制提示信息
    }
}


// 游戏初始化
void game_init() {
    // 显式地将time(NULL)转换为unsigned int类型
    srand((unsigned int)time(NULL)); // 设置随机数种子
    hide_cursor(); // 隐藏光标
    system("cls"); // 清屏
    draw_border(); // 绘制边框
    draw_info(); // 绘制提示信息
    generate_next_num(); // 生成下一个数字
    generate_cur_num(); // 生成当前数字
    draw_num(cur_num, cur_row, cur_col, colors[cur_num]); // 绘制当前数字
}

// 游戏结束
void game_over() {
    over = true; // 设置结束标志
    set_color(WHITE);
    set_cursor(COLS, ROWS / 2);
    cout << "游戏结束！ ";
    set_cursor(COLS, ROWS / 2 + 1);
    cout << "按任意键退出";
    show_cursor(); // 显示光标
}

// 游戏暂停
// 游戏暂停
void game_pause() {
    pause = !pause; // 切换暂停状态
    set_color(WHITE);
    if (pause) {
        set_cursor(COLS, ROWS / 2);
        cout << "游戏暂停！ ";
    }
    else {
        set_cursor(COLS, ROWS / 2);
        cout << "         "; // 输出空格覆盖原来的提示
    }
}



void game_loop()
{
    int num = get_next_num(true, time(0)); // 当前的数字
    int next_num = get_next_num(); // 下一个数字
    int row = 0; // 当前的行
    int col = COLS / 2 - 1; // 当前的列

    while (true) {
        draw_num(num, row, col, GREEN); // 绘制当前的数字
        draw_num(next_num, 0, COLS + 2, GREEN); // 绘制下一个数字

        int key = get_key(); // 获取按键
        if (key == 'q') { // 如果按下q键
            break; // 退出游戏
        }
        else if (key == 'a') { // 如果按下a键
            erase_num(num, row, col); // 擦除当前的数字
            if (check_move(num, row, col - 1)) { // 如果可以向左移动
                col--; // 向左移动
            }
        }
        else if (key == 'd') { // 如果按下d键
            erase_num(num, row, col); // 擦除当前的数字
            if (check_move(num, row, col + 1)) { // 如果可以向右移动
                col++; // 向右移动
            }
        }
        else if (key == 's') { // 如果按下s键
            erase_num(num, row, col); // 擦除当前的数字
            if (check_move(num, row + 1, col)) { // 如果可以向下移动
                row++; // 向下移动
            }
            else { // 如果不能向下移动
                fix_num(num, row, col); // 将当前的数字固定到区域
                eliminate_row(); // 消除满行
                num = next_num; // 下一个数字变为当前的数字
                next_num = get_next_num(); // 生成下一个数字
                row = 0; // 当前的行变为0
                col = COLS / 2 - 1; // 当前的列变为COLS / 2 - 1
                if (!check_move(num, row, col)) { // 如果不能向下移动
                    break; // 退出游戏
                }
            }
        }

        draw_num(num, row, col, GREEN); // 绘制当前的数字
        draw_num(next_num, 0, COLS + 2, GREEN); // 绘制下一个数字
        delay_ms(delay); // 延迟
    }
}