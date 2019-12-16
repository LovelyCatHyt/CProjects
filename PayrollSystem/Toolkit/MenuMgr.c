#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "MenuMgr.h"
#include "ColorfulConsoler.h"
#include "KeyCtrl.h"

//Ĭ��:�ڵװ���
static WORD defaultAttr = 0x0007;
//����:Ĭ��+��ɫ+�»���
static WORD highlightAttr = 0x6007;

//�����˵���������
void SwitchMenuHighlight(COORD cdCurrent, COORD cdTarget, SHORT sWidth)
{
    //�ع�Ĭ��״̬
    SetRectAttr(cdCurrent,SHORT2COORD(cdCurrent.X + sWidth - 1,cdCurrent.Y),defaultAttr);
    SetRectAttr(cdTarget,SHORT2COORD(cdTarget.X + sWidth - 1,cdTarget.Y),highlightAttr);
}

//��ʾ�˵� ���ش����õĺ���ָ��
void (*ShowMenu(COORD cdBeginPos, MenuNode *contents, size_t arraySize))(void)
{
    size_t i;
    SHORT sSelectingMenuID = 0;
    COORD cdMenuCursor = cdBeginPos;
    //Ŀǰ����(�ݴ����)
    COORD cdCurrentPos;
    //Ŀ������
    COORD cdTargetPos;
    SHORT maxWidth = 0;
    //����ѭ��
    BOOL canLoop = TRUE;
    void (*action)(void) = NULL;
    SetPos(cdBeginPos);
    for(i = 0,cdCurrentPos = cdBeginPos;i<arraySize;i++,cdCurrentPos.Y++)
    {
        SetPos(cdCurrentPos);
        printf("%s",contents[i].lable);
        SHORT tmpLen = strlen(contents[i].lable);
        maxWidth = tmpLen>maxWidth?tmpLen:maxWidth;
    }
    //����
    cdCurrentPos = cdBeginPos;
    SetRectAttr(cdMenuCursor,SHORT2COORD(cdMenuCursor.X + maxWidth - 1,cdMenuCursor.Y),highlightAttr);
    while(canLoop)
    {
        switch(GetKeyBoardInput())
        {
        case keycode_UpArrow:
            //����
            cdTargetPos = cdCurrentPos;
            if(sSelectingMenuID == 0)
            {
                //�ڵ�һ���˵���
                sSelectingMenuID = arraySize - 1;
            }else
            {
                sSelectingMenuID--;
            }
            cdTargetPos.Y = cdBeginPos.Y + sSelectingMenuID;
            //�ƶ�����
            SwitchMenuHighlight(cdCurrentPos,cdTargetPos,maxWidth);
            cdCurrentPos = cdTargetPos;
            break;
        case keycode_DownArrow:
            //����
            cdTargetPos = cdCurrentPos;
            if(sSelectingMenuID == arraySize - 1)
            {
                //�����һ���˵���
                sSelectingMenuID = 0;
            }else
            {
                sSelectingMenuID++;
            }
            cdTargetPos.Y = cdBeginPos.Y + sSelectingMenuID;
            //�ƶ�����
            SwitchMenuHighlight(cdCurrentPos,cdTargetPos,maxWidth);
            cdCurrentPos = cdTargetPos;
            break;
        case keycode_RightArrow:
            //����
            if(contents[sSelectingMenuID].childs==NULL)
            {
                //û���Ӳ˵�
                //ɶ������
            }else
            {
                //�����Ӳ˵�
                //û��ִ�����������ѭ��
                action = ShowMenu(SHORT2COORD(cdCurrentPos.X + maxWidth + 1, cdCurrentPos.Y),
                    contents[sSelectingMenuID].childs,
                    contents[sSelectingMenuID].childNum);
                if(action != NULL)
                {
                    //���صĺ�����Ϊ��
                    //����˵�����
                    SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
                    //����˵���ɫ
                    SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
                    //������ʼ��
                    SetPos(cdBeginPos);
                    canLoop = FALSE;
                }

            }
            break;
        case keycode_Enter:
            //�س�
            if(contents[sSelectingMenuID].action == NULL)
            {
                //û�в˵�����
                //ɶ������
            }else
            {
                //����˵�����
                SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
                //����˵���ɫ
                SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
                //������ʼ��
                SetPos(cdBeginPos);
                canLoop = FALSE;
                //��ȡ�˵�����
                action = contents[sSelectingMenuID].action;
            }
            break;
        case keycode_LeftArrow:
            //����
        case keycode_Escape:
            //�˳�
            //����˵�����
            SetRectChar(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),' ');
            //����˵���ɫ
            SetRectAttr(cdBeginPos,SHORT2COORD(cdBeginPos.X + maxWidth - 1,cdBeginPos.Y + arraySize - 1),defaultAttr);
            //���ص���ʼ����
            SetPos(cdBeginPos);
            //����ѭ���Խ�����ǰ�˵�
            canLoop = FALSE;
            break;
        }
    }
    return action;
}