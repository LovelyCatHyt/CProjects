#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "MenuMgr.h"
#include "ColorfulConsoler.h"

//默认:黑底白字
static WORD defaultAttr = 0x0007;
//高亮:默认+反色+下划线
static WORD highlightAttr = 0x6007;

void ShowMenu(COORD beginPos, MenuNode *contens, size_t arraySize)
{
    size_t i;
    COORD cdMenuCursor = beginPos;
    COORD currentPos;
    SHORT maxWidth = 0;
    SetPos(beginPos);
    for(i = 0,currentPos = beginPos;i<arraySize;i++,currentPos.Y++)
    {
        SetPos(currentPos);
        printf("%s",contens[i].lable);
        SHORT tmpLen = strlen(contens[i].lable);
        maxWidth = tmpLen>maxWidth?tmpLen:maxWidth;
    }
    SetRectAttr(cdMenuCursor,SHORT2COORD(cdMenuCursor.X + maxWidth - 1,cdMenuCursor.Y),highlightAttr);
}
