#ifndef _MENUMGR_H
#define _MENUMGR_H
#define MAX_MENU_LABLE 32
#include <windows.h>

typedef struct _MenuNode
{
    void (*action)(void);
    char lable[MAX_MENU_LABLE];
    struct _MenuNode *parent;
    struct _MenuNode *childs;

}MenuNode;

void ShowMenu(COORD beginPos, MenuNode *contens, size_t size);
//默认:黑底白字
WORD defaultAttr = 0x0007;
//高亮:默认+反色+下划线
WORD highlightAttr = 0x6007;

#endif // _MENUMGR_H
