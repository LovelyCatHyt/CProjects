#ifndef _KEYCTRL_H
#define _KEYCTRL_H
//键码
enum KeyCode
{
    keycode_UpArrow = 0x0148,
    keycode_LeftArrow = 0x14b,
    keycode_RightArrow = 0x14d,
    keycode_DownArrow = 0x0150,
    keycode_Enter = 0x000d,
    keycode_Escape = 0x001b,
};
int GetKeyBoardInput();

#endif
