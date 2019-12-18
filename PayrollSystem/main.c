//#define TESTING
#include <windows.h>
#include "Toolkit/Debugger.h"
#include "Toolkit/MenuMgr.h"
#include "Data/DataInput.h"
#include "Toolkit/ColorfulConsoler.h"

//全文件可见
static FArray payrollList;

//输入功能
void InputData()
{
    FArray_Initialize(&payrollList,sizeof(Payroll),0);
    GetPayrolls(&payrollList);
    PrintPayrollTable((Payroll *)payrollList.array,payrollList.arraySize);
    
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

//主菜单
MenuNode mainMenu[4] =
{
    {InputData,"输入数据",TRUE,NULL,0},
    {EditData,"编辑数据",TRUE,NULL,0},
    {RemoveData,"删除数据",TRUE,NULL,0},
    {ExitSystem,"退出系统",TRUE,NULL,0}
};

int main()
{
#ifdef TESTING
    Test();
#endif // TESTING
    //获取句柄
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //控制台缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    COORD cursor = {0,0};
    void (*menuAction)(void) = NULL;
    FArray_Initialize(&payrollList,sizeof(Payroll),0);
    GetPayrolls(&payrollList);
    PrintPayrollTable((Payroll *)payrollList.array,payrollList.arraySize);
    //获取当前光标位置
    GetConsoleScreenBufferInfo(hStdOut,&csbiInfo);
    cursor = csbiInfo.dwCursorPosition;
    cursor.X = 0;
    while(!menuAction)
    {
        //只要menuAction为NULL就保持菜单显示
        menuAction = ShowMenu(cursor,mainMenu,4);
    }
    //执行菜单返回的函数
    menuAction();
    
    return 0;
}
