//#define TESTING
#include <windows.h>
#include "main.h"
#include "Toolkit/Debugger.h"
#include "Toolkit/MenuMgr.h"
#include "Data/DataInput.h"
#include "Toolkit/ColorfulConsoler.h"

//全文件可见
static FArray payrollList;
//主菜单
static MenuNode mainMenu[4] =
{
    {InputData,"输入数据",TRUE,NULL,0},
    {EditData,"编辑数据",TRUE,NULL,0},
    {RemoveData,"删除数据",TRUE,NULL,0},
    {ExitSystem,"退出系统",TRUE,NULL,0}
};
//输入功能
void InputData()
{
    FArray_Initialize(&payrollList,sizeof(Payroll),0);
    GetPayrolls(&payrollList);
    PrintPayrollTable((Payroll *)payrollList.array,payrollList.arraySize);
    ShowMenu(GetCurrentCursor(),mainMenu,4);
}
//编辑功能
void EditData()
{

}
//删除数据
void RemoveData()
{

}
//退出系统
void ExitSystem()
{

}
//按ID排序
void SortByID()
{

}
//按姓名排序
void SortByName()
{

}
//按基本工资排序
void SortByBaseWage()
{

}
//按实付工资排序
void SortByTakeHomePay()
{

}

int main()
{
#ifdef TESTING
    Test();
#else // TESTING
    COORD cursor;
    void (*menuAction)(void) = NULL;
    while(!menuAction)
    {
        //获取当前光标位置
        cursor = GetCurrentCursor();
        //开新的一行
        cursor.X = 0;cursor.Y++;
        //展示菜单
        menuAction = ShowMenu(cursor,mainMenu,4);
        //执行菜单返回的函数
        if(menuAction)
        {
            menuAction();
        }else
        {
            PrintError("ExitMenu with empty funtion pointer!");
        }
    }
#endif
    return 0;
}
