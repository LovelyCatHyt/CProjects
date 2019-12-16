#include "KeyCtrl.h"
#include <conio.h>
#include <stdio.h>

int GetKeyBoardInput()
{
    char temp = getch();
    //如果是字母以外的按键
    if(temp==0xffffffe0)
    {
        //在第9位 置1
        return getch()|0x0100;
    }else
    {
        return temp;
    }


}
