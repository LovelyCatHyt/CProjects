#ifndef _COLORFULCONSOLER_H_
#define _COLORFULCONSOLER_H_
#include <windows.h>

void SetPos(COORD pos);

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define PALEGREEN 10
#define PALELIGHTGREEN 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define LIGHTWHITE 15
void SetColor(unsigned short ForeColor,unsigned short BackGroundColor);
void SetAttribute(WORD attr);
void SetRectAttr(COORD beginPos,COORD endPos,WORD attr);
void SetRectChar(COORD beginPos,COORD endPos,WCHAR c);
void DefaultColor();
COORD GetCurrentCursor();
WORD ChoseColorAttr(COORD cdBeginPos);
#endif // _COLORFULCONSOLER_H_
