#ifndef _MENUMGR_H
#define _MENUMGR_H
#define MAX_MENU_LABLE 32
#include <windows.h>

typedef struct _MenuNode
{
    void (*action)(void);
    char lable[MAX_MENU_LABLE];
    //struct _MenuNode *parent;
    int isRoot;
    struct _MenuNode *childs;
    size_t childNum;

}MenuNode;

void (*ShowMenu(COORD cdBeginPos, MenuNode *contents, size_t arraySize))(void);

#endif // _MENUMGR_H
