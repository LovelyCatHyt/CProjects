#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "MenuMgr.h"
#include "ColorfulConsoler.h"
#include "KeyCtrl.h"

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
