// tetris.h
// 头文件，包含常量、枚举、结构体和函数的声明


#define TETRIS_H

// 定义常量
const int ROWS = 22; // 区域的行数
const int COLS = 15; // 区域的列数
const int NUMS = 10; // 数字的种类
const int SHAPES = 4; // 每个数字的形态
const int MY_SIZE = 15; // 每个数字的方块数

const int MY_ROWS = 5; // 每个数字的行数
const int DELAY = 1000; // 初始下落延迟（毫秒）
const int SPEEDUP = 100; // 每15分加速的延迟（毫秒）
const int MIN_DELAY = 300; // 最小下落延迟（毫秒）
const int SCORES[6] = { 0, 1, 3, 6, 10, 15 }; // 消除行数对应的得分


// 定义颜色
enum Color {
    BLACK, // 黑色
    RED, // 红色
    GREEN, // 绿色
    YELLOW, // 黄色
    BLUE, // 蓝色
    PURPLE, // 紫色
    CYAN, // 青色
    WHITE // 白色
};
// 声明全局变量，使用extern关键字
extern Color colors[NUMS]; // 颜色数组
extern int area[ROWS][COLS]; // 区域数据
extern int cur_num; // 当前数字的种类
extern int cur_shape; // 当前数字的形态
extern int cur_row; // 当前数字的行坐标
extern int cur_col; // 当前数字的列坐标
extern int next_num; // 下一个数字的种类
extern int next_shape; // 下一个数字的形态
extern int score; // 当前得分
extern int delay; // 当前下落延迟
extern bool pause; // 是否暂停
extern bool over; // 是否结束



// 定义按键
enum Key {
    UP = 72, // 上
    DOWN = 80, // 下
    LEFT = 75, // 左
    RIGHT = 77, // 右
    SPACE = 32, // 空格
    ESC = 27 // 退出
};

// 定义数字的形状
// 每个数字由四个小方块组成，每个小方块用一个二维坐标表示
// 每个数字有四种形态，每种形态用一个二维数组表示
// 每个数字用一个三维数组表示
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



// 设置控制台光标的位置
void set_cursor(int x, int y);

// 设置控制台文本的颜色
void set_color(Color color);




// 隐藏控制台光标
void hide_cursor();

// 显示控制台光标
void show_cursor();

// 获取下一个数字的种类
int get_next_num(const bool new_seed = false, const unsigned int seed = 0);

// 生成下一个数字
void generate_next_num();

// 生成当前数字
void generate_cur_num();

// 绘制一个小方块
void draw_block(int x, int y, Color color);

// 擦除一个小方块
void erase_block(int x, int y);

// 绘制一个数字
void draw_num(int num, int row, int col, Color color);

// 擦除一个数字
// // 擦除一个数字
void erase_num(int num, int shape, int row, int col);
// 擦除一个数字
// 游戏初始化
void game_init();

// 游戏主循环
void game_loop();
