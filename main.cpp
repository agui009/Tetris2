// main.cpp
// 主程序文件，包含菜单和游戏逻辑

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "tetris.h"
using namespace std;
extern Color colors[NUMS]; // 颜色数组

// 定义菜单选项
enum Menu {
    START = 1, // 开始游戏
    HELP = 2, // 帮助信息
    ABOUT = 3, // 关于作者
    EXIT = 4 // 退出游戏
};

// 显示菜单
void show_menu() {
    system("cls"); // 清屏
    set_color(WHITE); // 设置颜色为白色
    set_cursor(0, 0); // 设置光标位置为左上角
    cout << "欢迎来到数字俄罗斯方块游戏！\n";
    cout << "请选择以下选项：\n";
    cout << "1. 开始游戏\n";
    cout << "2. 帮助信息\n";
    cout << "3. 关于作者\n";
    cout << "4. 退出游戏\n";
}

// 获取用户输入的菜单选项
Menu get_choice() {
    char ch;
    do {
        ch = _getch(); // 获取用户输入的字符
    } while (ch < '1' || ch > '4'); // 循环直到输入合法的选项
    return (Menu)(ch - '0'); // 将字符转换为枚举类型
}

// 显示帮助信息
void show_help() {
    system("cls"); // 清屏
    set_color(WHITE); // 设置颜色为白色
    set_cursor(0, 0); // 设置光标位置为左上角
    cout << "数字俄罗斯方块游戏的玩法如下：\n";
    cout << "区域大小为22*15，每个数字的区域为3*5，下落的数字为0-9，每个数字有四种形态，可以旋转。\n";
    cout << "当一行被填满时，该行消除，得分增加，下落速度加快。\n";
    cout << "当区域顶部被占满时，游戏结束。\n";
    cout << "按键说明：\n";
    cout << "上箭头键：旋转数字\n";
    cout << "左箭头键：向左平移\n";
    cout << "右箭头键：向右平移\n";
    cout << "下箭头键：快速下落\n";
    cout << "空格键：暂停游戏\n";
    cout << "ESC键：退出游戏\n";
    cout << "--请按任意按键返回主菜单--\n";
    _getch(); // 等待用户输入任意键
}

// 显示关于作者的信息
void show_about() {
    system("cls"); // 清屏
    set_color(WHITE); // 设置颜色为白色
    set_cursor(0, 0); // 设置光标位置为左上角
    cout << "你好我是岁定云\n";
    cout << "--请按任意按键返回主菜单--\n";
    _getch(); // 等待用户输入任意键
}

// 主函数
int main() {
    hide_cursor(); // 隐藏光标
    while (true) {
        show_menu(); // 显示菜单
        Menu choice = get_choice(); // 获取用户选择的菜单选项
        switch (choice) {
        case START: // 开始游戏
            game_init(); // 游戏初始化
            game_loop(); // 游戏主循环
            break;
        case HELP: // 帮助信息
            show_help(); // 显示帮助信息
            break;
        case ABOUT: // 关于作者
            show_about(); // 显示关于作者的信息
            break;
        case EXIT: // 退出游戏
            return 0; // 退出程序
        }
    }
    return 0;
}
