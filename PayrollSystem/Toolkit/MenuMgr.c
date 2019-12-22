#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "MenuMgr.h"
#include "ColorfulConsoler.h"
#include "KeyCtrl.h"
#include "Coordinate.h"

//默认:黑底白字
static WORD defaultAttr = 0x0007;
//高亮:默认+反色+下划线
static WORD highlightAttr = 0x6007;

//调整菜单高亮区域
void SwitchMenuHighlight(COORD cdCurrent, COORD cdTarget, SHORT sWidth)
{
    //回归默认状态
    SetRectAttr(cdCurrent,SHORT2COORD(cdCurrent.X + sWidth - 1,cdCurrent.Y),defaultAttr);
    SetRectAttr(cdTarget,SHORT2COORD(cdTarget.X + sWidth - 1,cdTarget.Y),highlightAttr);
}

//展示一个线性的菜单,仅返回一个菜单项对应的数字,但是选择/高亮功能与菜单相同
int ShowSimpleMenu(char *contents[], int size, COORD cdBeginPos)
{
    //枚举变量
    int i;
    COORD cdCursor = cdBeginPos;
    COORD cdTargetCursor;
    int iMenuWidth = 0;
    int iIndex = 0;
    BOOL bLoop = TRUE;
    int iKeyInput;
    //输出菜单内容
    for (i = 0; i < size; i++)
    {
        //打印
        printf("[%d]%s", i, contents[i]);
        //获取最大值
        int length = strlen(contents[i]) + 3;
        iMenuWidth = length > iMenuWidth ? length : iMenuWidth;
        //往下移一行
        cdCursor.Y++;
        cdCursor.X = cdBeginPos.X;
        SetPos(cdCursor);
    }
    //设置第一条高光
    cdCursor = cdBeginPos;
    SwitchMenuHighlight(cdCursor,cdCursor,iMenuWidth);
    //键盘操作循环
    while(bLoop)
    {
        iKeyInput = GetKeyBoardInput();
        //根据输入修改iIndex的值
        switch (iKeyInput)
        {
        case keycode_UpArrow:
            if (iIndex <= 0)
            {
                iIndex = size - 1;
            }
            else
            {
                iIndex--;
            }
            break;
        case keycode_DownArrow:
            if (iIndex >= size - 1)
            {
                iIndex = 0;
            }else
            {
                iIndex++;
            }
            break;
        case keycode_Enter:
            bLoop = FALSE;
            break;
        default:
            if (iKeyInput >= '0' && iKeyInput <= size -1 + '0')
            {
                iIndex = iKeyInput - '0';
            }
                break;
        }
        //根据iIndex转换高亮位置
        cdTargetCursor = SHORT2COORD(cdBeginPos.X,cdBeginPos.Y + iIndex);
        SwitchMenuHighlight(cdCursor,cdTargetCursor,iMenuWidth);
        //重置光标位置
        cdCursor = cdTargetCursor;
    }
    //清除菜单
    SetRectChar(cdBeginPos, COORD_Add(cdBeginPos, SHORT2COORD(iMenuWidth - 1, size - 1)), ' ');
    SetRectAttr(cdBeginPos, COORD_Add(cdBeginPos, SHORT2COORD(iMenuWidth - 1, size - 1)), 0x0007);
    SetPos(cdBeginPos);
    return iIndex;
}

//显示菜单 返回待调用的函数指针
void (*ShowMenu(COORD cdBeginPos, MenuNode *contents, size_t arraySize))(void)
{
    size_t i;
    SHORT sSelectingMenuID = 0;
    COORD cdMenuCursor = cdBeginPos;
    //目前坐标(暂存变量)
    COORD cdCurrentPos;
    //目标坐标
    COORD cdTargetPos;
    SHORT menuWidth = 0;
    //启用循环
    BOOL canLoop = TRUE;
    void (*action)(void) = NULL;
    SetPos(cdBeginPos);
    for(i = 0,cdCurrentPos = cdBeginPos;i<arraySize;i++,cdCurrentPos.Y++)
    {
        //遍历输出每个菜单项
        SetPos(cdCurrentPos);
        //用字母编号 暂时不管菜单数量大于26的情况
        printf("[%c]%s",i+'a',contents[i].lable);
        SHORT tmpLen = strlen(contents[i].lable) + 3;
        menuWidth = tmpLen>menuWidth ? tmpLen : menuWidth;
    }
    //高亮
    cdCurrentPos = cdBeginPos;
    SetRectAttr(cdMenuCursor,SHORT2COORD(cdMenuCursor.X + menuWidth - 1,cdMenuCursor.Y),highlightAttr);
    while(canLoop)
    {
        int input = GetKeyBoardInput();
        switch(input)
        {
        case keycode_UpArrow:
            //向上
            cdTargetPos = cdCurrentPos;
            if(sSelectingMenuID == 0)
            {
                //在第一个菜单项
                sSelectingMenuID = arraySize - 1;
            }else
            {
                sSelectingMenuID--;
            }
            cdTargetPos.Y = cdBeginPos.Y + sSelectingMenuID;
            //移动高亮
            SwitchMenuHighlight(cdCurrentPos,cdTargetPos,menuWidth);
            cdCurrentPos = cdTargetPos;
            break;
        case keycode_DownArrow:
            //向下
            cdTargetPos = cdCurrentPos;
            if(sSelectingMenuID == arraySize - 1)
            {
                //在最后一个菜单项
                sSelectingMenuID = 0;
            }else
            {
                sSelectingMenuID++;
            }
            cdTargetPos.Y = cdBeginPos.Y + sSelectingMenuID;
            //移动高亮
            SwitchMenuHighlight(cdCurrentPos,cdTargetPos,menuWidth);
            cdCurrentPos = cdTargetPos;
            break;
        case keycode_RightArrow:
            //向右
            if(contents[sSelectingMenuID].childs==NULL)
            {
                //没有子菜单
                //啥都不干
            }else
            {
                //进入子菜单
                //没有执行任务则继续循环
                action = ShowMenu(SHORT2COORD(cdCurrentPos.X + menuWidth + 1, cdCurrentPos.Y),
                    contents[sSelectingMenuID].childs,
                    contents[sSelectingMenuID].childNum);
                if(action != NULL)
                {
                    //返回的函数不为空
                    //清除菜单内容
                    SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
                    //清除菜单颜色
                    SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
                    //返回起始点
                    SetPos(cdBeginPos);
                    canLoop = FALSE;
                }

            }
            break;
        case keycode_Enter:
            //回车
            if(contents[sSelectingMenuID].action == NULL)
            {
                //没有菜单函数
                //啥都不干
            }else
            {
                //清除菜单内容
                SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
                //清除菜单颜色
                SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
                //返回起始点
                SetPos(cdBeginPos);
                canLoop = FALSE;
                //获取菜单内容
                action = contents[sSelectingMenuID].action;
            }
            break;
        case keycode_LeftArrow:
            //向左
        case keycode_Escape:
            //退出
            if(!contents[sSelectingMenuID].isRoot)
            {
                //不是根菜单
                //清除菜单内容
                SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
                //清除菜单颜色
                SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + menuWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
                //返回到初始坐标
                SetPos(cdBeginPos);
                //禁用循环以结束当前菜单
                canLoop = FALSE;
            }
            break;
        default:
            //其他情况,支持用字母定位菜单
            if(input>='A' && input <='Z')
            {
                //转换成小写
                input+='a'-'A';
            }
            if(input>='a' && input<='z' && (input - 'a')<arraySize)
            {
                //跳转到对应菜单并更新相关参数
                cdTargetPos = cdBeginPos;
                sSelectingMenuID = input - 'a';
                cdTargetPos.Y += sSelectingMenuID;
                SwitchMenuHighlight(cdCurrentPos,cdTargetPos,menuWidth);
                cdCurrentPos = cdTargetPos;
            }
            break;
        }
    }
    return action;
}
