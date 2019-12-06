#include <windows.h>
#include <time.h>

/*设置光标位置*/
void SetPos(int x,int y)
{
    COORD pos;
    HANDLE handle;
    pos.X=x;
    pos.Y=y;
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}

/*设置颜色*/
void SetColor(unsigned short ForeColor,unsigned short BackGroundColor)
{

/*
对应的颜色码表：
0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       10 = 淡绿色
3 = 浅绿色     11 = 淡浅绿色
4 = 红色       12 = 淡红色
5 = 紫色       13 = 淡紫色
6 = 黄色       14 = 淡黄色
7 = 白色       15 = 亮白色
*/
HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);/*获取当前窗口句柄*/
SetConsoleTextAttribute(handle,ForeColor+(BackGroundColor<<4));/*设置颜色*/
}
