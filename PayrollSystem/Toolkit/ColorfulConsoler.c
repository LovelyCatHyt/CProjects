#ifndef _COLORFULCONSOLER_C_
#define _COLORFULCONSOLER_C_

#include <time.h>
#include "ColorfulConsoler.h"


COORD SHORT2COORD(SHORT x,SHORT y)
{
    COORD result = {x,y};
    return result;
}

COORD GetCurrentCursor()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdOut,&csbiInfo);
    return csbiInfo.dwCursorPosition;
}

/*设置一片区域的Attr*/
void SetRectAttr(COORD beginPos,COORD endPos,WORD attr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cdCurrent;
    DWORD width = endPos.X - beginPos.X + 1;
    DWORD dwTemp;
    for(cdCurrent = beginPos;cdCurrent.Y<=endPos.Y;cdCurrent.Y++)
    {
        FillConsoleOutputAttribute(hStdout,attr,width,cdCurrent,&dwTemp);
    }

}
//设置一片区域的字符
void SetRectChar(COORD beginPos,COORD endPos,WCHAR c)
{
    
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cdCurrent;
    DWORD width = endPos.X - beginPos.X + 1;
    DWORD dwTemp;
    for(cdCurrent = beginPos;cdCurrent.Y<=endPos.Y;cdCurrent.Y++)
    {
        FillConsoleOutputCharacter(hStdout,c,width,cdCurrent,&dwTemp);
    }
}

/*设置光标位置*/
void SetPos(COORD pos)
{
    HANDLE handle;
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

unsigned int DefaultForeColor = 7,DefaultBackGroundColor = 0;

void DefaultColor()
{
    SetColor(DefaultForeColor,DefaultBackGroundColor);
}

#endif // _COLORFULCONSOLER_C_
