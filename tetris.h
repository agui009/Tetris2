// tetris.h
// ͷ�ļ�������������ö�١��ṹ��ͺ���������


#define TETRIS_H

// ���峣��
const int ROWS = 22; // ���������
const int COLS = 15; // ���������
const int NUMS = 10; // ���ֵ�����
const int SHAPES = 4; // ÿ�����ֵ���̬
const int MY_SIZE = 15; // ÿ�����ֵķ�����

const int MY_ROWS = 5; // ÿ�����ֵ�����
const int DELAY = 1000; // ��ʼ�����ӳ٣����룩
const int SPEEDUP = 100; // ÿ15�ּ��ٵ��ӳ٣����룩
const int MIN_DELAY = 300; // ��С�����ӳ٣����룩
const int SCORES[6] = { 0, 1, 3, 6, 10, 15 }; // ����������Ӧ�ĵ÷�


// ������ɫ
enum Color {
    BLACK, // ��ɫ
    RED, // ��ɫ
    GREEN, // ��ɫ
    YELLOW, // ��ɫ
    BLUE, // ��ɫ
    PURPLE, // ��ɫ
    CYAN, // ��ɫ
    WHITE // ��ɫ
};
// ����ȫ�ֱ�����ʹ��extern�ؼ���
extern Color colors[NUMS]; // ��ɫ����
extern int area[ROWS][COLS]; // ��������
extern int cur_num; // ��ǰ���ֵ�����
extern int cur_shape; // ��ǰ���ֵ���̬
extern int cur_row; // ��ǰ���ֵ�������
extern int cur_col; // ��ǰ���ֵ�������
extern int next_num; // ��һ�����ֵ�����
extern int next_shape; // ��һ�����ֵ���̬
extern int score; // ��ǰ�÷�
extern int delay; // ��ǰ�����ӳ�
extern bool pause; // �Ƿ���ͣ
extern bool over; // �Ƿ����



// ���尴��
enum Key {
    UP = 72, // ��
    DOWN = 80, // ��
    LEFT = 75, // ��
    RIGHT = 77, // ��
    SPACE = 32, // �ո�
    ESC = 27 // �˳�
};

// �������ֵ���״
// ÿ���������ĸ�С������ɣ�ÿ��С������һ����ά�����ʾ
// ÿ��������������̬��ÿ����̬��һ����ά�����ʾ
// ÿ��������һ����ά�����ʾ
const int shapes[NUMS][5][3] = {
    // 0
    {
        {0, 1, 0},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0}
    },
    // 1
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    },
    // 2
    {
        {0, 1, 0},
        {1, 0, 1},
        {0, 0, 1},
        {0, 1, 0},
        {1, 1, 1}
    },
    // 3
    {
        {1, 1, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0}
    },
    // 4
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    },
    // 5
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 0},
        {0, 0, 1},
        {1, 1, 0}
    },
    // 6
    {
        {0, 1, 1},
        {1, 0, 0},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    },
    // 7
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // 8
    {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    },
    // 9
    {
        {0, 1, 1},
        {1, 0, 1},
        {0, 1, 1},
        {0, 0, 1},
        {1, 1, 0}
    }
};



// ���ÿ���̨����λ��
void set_cursor(int x, int y);

// ���ÿ���̨�ı�����ɫ
void set_color(Color color);




// ���ؿ���̨���
void hide_cursor();

// ��ʾ����̨���
void show_cursor();

// ��ȡ��һ�����ֵ�����
int get_next_num(const bool new_seed = false, const unsigned int seed = 0);

// ������һ������
void generate_next_num();

// ���ɵ�ǰ����
void generate_cur_num();

// ����һ��С����
void draw_block(int x, int y, Color color);

// ����һ��С����
void erase_block(int x, int y);

// ����һ������
void draw_num(int num, int row, int col, Color color);

// ����һ������
// // ����һ������
void erase_num(int num, int shape, int row, int col);
// ����һ������
// ��Ϸ��ʼ��
void game_init();

// ��Ϸ��ѭ��
void game_loop();
