#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "MsgBox.h"
#include "ColorfulConsoler.h"
#include "KeyCtrl.h"
#include "Coordinate.h"

//显示一个对话框,用方向键控制选中的按钮,按下回车则返回对应的值
int ShowMsgBox(const char *msg)
{
    int ok = 1;
    SHORT buttonWidth;
    COORD buttonLeft;
    COORD buttonRight;
    WORD defaultButtonAttr = 0x000f;
    WORD selectedButtonAttr = 0x00f0;
    int keyInput = 0;
    printf(msg);
    //如果末尾没有换行就手动加一个
    if (msg[strlen(msg) - 1] != '\n')
        putchar('\n');
    buttonRight = buttonLeft = GetCurrentCursor();
    printf("确认|取消\n");
    buttonWidth = strlen("确认");
    buttonRight.X += buttonWidth + strlen("|");
    //初始状态:左亮右暗
    SetRectAttr(buttonLeft, SHORT2COORD(buttonLeft.X + buttonWidth - 1, buttonLeft.Y), selectedButtonAttr);
    SetRectAttr(buttonRight, SHORT2COORD(buttonRight.X + buttonWidth - 1, buttonRight.Y), defaultButtonAttr);
    keyInput = GetKeyBoardInput();
    while (keyInput != keycode_Enter)
    {
        switch (keyInput)
        {
        case keycode_LeftArrow:
            ok = 1;
            SetRectAttr(buttonLeft, SHORT2COORD(buttonLeft.X + buttonWidth - 1, buttonLeft.Y), selectedButtonAttr);
            SetRectAttr(buttonRight, SHORT2COORD(buttonRight.X + buttonWidth - 1, buttonRight.Y), defaultButtonAttr);
            break;
        case keycode_RightArrow:
            ok = 0;
            SetRectAttr(buttonLeft, SHORT2COORD(buttonLeft.X + buttonWidth - 1, buttonLeft.Y), defaultButtonAttr);
            SetRectAttr(buttonRight, SHORT2COORD(buttonRight.X + buttonWidth - 1, buttonRight.Y), selectedButtonAttr);
            break;
        }
        keyInput = GetKeyBoardInput();
    }
    system("cls");
    return ok;
}
