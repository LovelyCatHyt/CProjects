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

void ShowMenu(COORD beginPos, MenuNode *contens, size_t arraySize);

#endif // _MENUMGR_H
