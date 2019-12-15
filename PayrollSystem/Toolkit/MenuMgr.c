#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "MenuMgr.h"
#include "ColorfulConsoler.h"



void ShowMenu(COORD beginPos, MenuNode *contens, size_t size)
{
    size_t i;
    COORD cdMenuCursor = beginPos;
    COORD currentPos;
    SHORT maxWidth = 0;
    SetPos(beginPos);
    for(i = 0,currentPos = beginPos;i<size;i++,currentPos.Y++)
    {
        printf("%s",contens[i].lable);
        SHORT tmpLen = strlen(contens[i].lable);
        maxWidth = tmpLen>maxWidth?tmpLen:maxWidth;
    }
    SetRectAttr(cdMenuCursor,SHORT2COORD(cdMenuCursor.X + maxWidth - 1,cdMenuCursor.Y),highlightAttr);
}
