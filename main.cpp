// main.cpp
// �������ļ��������˵�����Ϸ�߼�

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "tetris.h"
using namespace std;
extern Color colors[NUMS]; // ��ɫ����

// ����˵�ѡ��
enum Menu {
    START = 1, // ��ʼ��Ϸ
    HELP = 2, // ������Ϣ
    ABOUT = 3, // ��������
    EXIT = 4 // �˳���Ϸ
};

// ��ʾ�˵�
void show_menu() {
    system("cls"); // ����
    set_color(WHITE); // ������ɫΪ��ɫ
    set_cursor(0, 0); // ���ù��λ��Ϊ���Ͻ�
    cout << "��ӭ�������ֶ���˹������Ϸ��\n";
    cout << "��ѡ������ѡ�\n";
    cout << "1. ��ʼ��Ϸ\n";
    cout << "2. ������Ϣ\n";
    cout << "3. ��������\n";
    cout << "4. �˳���Ϸ\n";
}

// ��ȡ�û�����Ĳ˵�ѡ��
Menu get_choice() {
    char ch;
    do {
        ch = _getch(); // ��ȡ�û�������ַ�
    } while (ch < '1' || ch > '4'); // ѭ��ֱ������Ϸ���ѡ��
    return (Menu)(ch - '0'); // ���ַ�ת��Ϊö������
}

// ��ʾ������Ϣ
void show_help() {
    system("cls"); // ����
    set_color(WHITE); // ������ɫΪ��ɫ
    set_cursor(0, 0); // ���ù��λ��Ϊ���Ͻ�
    cout << "���ֶ���˹������Ϸ���淨���£�\n";
    cout << "�����СΪ22*15��ÿ�����ֵ�����Ϊ3*5�����������Ϊ0-9��ÿ��������������̬��������ת��\n";
    cout << "��һ�б�����ʱ�������������÷����ӣ������ٶȼӿ졣\n";
    cout << "�����򶥲���ռ��ʱ����Ϸ������\n";
    cout << "����˵����\n";
    cout << "�ϼ�ͷ������ת����\n";
    cout << "���ͷ��������ƽ��\n";
    cout << "�Ҽ�ͷ��������ƽ��\n";
    cout << "�¼�ͷ������������\n";
    cout << "�ո������ͣ��Ϸ\n";
    cout << "ESC�����˳���Ϸ\n";
    cout << "--�밴���ⰴ���������˵�--\n";
    _getch(); // �ȴ��û����������
}

// ��ʾ�������ߵ���Ϣ
void show_about() {
    system("cls"); // ����
    set_color(WHITE); // ������ɫΪ��ɫ
    set_cursor(0, 0); // ���ù��λ��Ϊ���Ͻ�
    cout << "��������궨��\n";
    cout << "--�밴���ⰴ���������˵�--\n";
    _getch(); // �ȴ��û����������
}

// ������
int main() {
    hide_cursor(); // ���ع��
    while (true) {
        show_menu(); // ��ʾ�˵�
        Menu choice = get_choice(); // ��ȡ�û�ѡ��Ĳ˵�ѡ��
        switch (choice) {
        case START: // ��ʼ��Ϸ
            game_init(); // ��Ϸ��ʼ��
            game_loop(); // ��Ϸ��ѭ��
            break;
        case HELP: // ������Ϣ
            show_help(); // ��ʾ������Ϣ
            break;
        case ABOUT: // ��������
            show_about(); // ��ʾ�������ߵ���Ϣ
            break;
        case EXIT: // �˳���Ϸ
            return 0; // �˳�����
        }
    }
    return 0;
}
