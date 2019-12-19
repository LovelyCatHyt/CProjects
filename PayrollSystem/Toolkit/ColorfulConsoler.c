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

/*����һƬ�����Attr*/
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
//����һƬ������ַ�
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

/*���ù��λ��*/
void SetPos(COORD pos)
{
    HANDLE handle;
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}

/*������ɫ*/
void SetColor(unsigned short ForeColor,unsigned short BackGroundColor)
{

/*
��Ӧ����ɫ���
0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       10 = ����ɫ
3 = ǳ��ɫ     11 = ��ǳ��ɫ
4 = ��ɫ       12 = ����ɫ
5 = ��ɫ       13 = ����ɫ
6 = ��ɫ       14 = ����ɫ
7 = ��ɫ       15 = ����ɫ
*/
HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);/*��ȡ��ǰ���ھ��*/
SetConsoleTextAttribute(handle,ForeColor+(BackGroundColor<<4));/*������ɫ*/
}

unsigned int DefaultForeColor = 7,DefaultBackGroundColor = 0;

void DefaultColor()
{
    SetColor(DefaultForeColor,DefaultBackGroundColor);
}

#endif // _COLORFULCONSOLER_C_
