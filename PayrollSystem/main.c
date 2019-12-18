//#define TESTING
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Toolkit/Debugger.h"
#include "Toolkit/MenuMgr.h"
#include "Data/DataInput.h"
#include "Toolkit/ColorfulConsoler.h"

//全文件可见的工资表
static FArray payrollList={NULL,0,0};
//主菜单
static MenuNode mainMenu[] =
{
    {InputData,"输入数据",TRUE,NULL,0},
    {EditData,"编辑数据",TRUE,NULL,0},
    {NULL,"数据排序>",TRUE,(MenuNode [])
    {
        {SortByID,"ID排序",FALSE,NULL,0},
        {SortByName,"姓名排序",FALSE,NULL,0},
        {SortByBaseWage,"基本工资排序",FALSE,NULL,0},
        {SortByTakeHomePay,"实发工资排序",FALSE,NULL,0}
    },4},
    {RemoveData,"删除数据",TRUE,NULL,0},
    {ExitSystem,"退出系统",TRUE,NULL,0}
};

//一个模块的结束,包括打印最新工资表和显示主菜单
void EndOfModule()
{
    void (*action)(void) = NULL;
    PrintLog("当前工资表数据如下:");
    PrintPayrollTable((Payroll *)payrollList.array,payrollList.arraySize);
    action = ShowMenu(GetCurrentCursor(),mainMenu,sizeof(mainMenu)/sizeof(MenuNode));
    if(!action)
    {
        PrintError("Menu return a Null function pointer!");
    }else
    {
        action();
    }
}

//输入功能
void InputData()
{
    if(payrollList.array==NULL)
    {
        //如果为空则初始化
        FArray_Initialize(&payrollList,sizeof(Payroll),0);
    }
    GetPayrolls(&payrollList);
    //清屏
    system("cls");
   EndOfModule();
}
//编辑功能
void EditData()
{
    int index = 0;
    int column = 0;
    int inputAvailable = 1;
    char tempID[32];
    char tempName[10];
    Payroll tempPayroll;
    Payroll *toEdit;
    PrintLog("【编辑功能】");
    PrintPayrollTable((Payroll *)(payrollList.array),payrollList.arraySize);
    printf("请选择要编辑的信息的编号(从0开始),目前共 %d 条.输入负数则退出编辑系统",payrollList.arraySize);
    do
    {
        inputAvailable = 1;
        scanf("%d",&index);
        if(index<payrollList.arraySize)
        {
            if(index>=0)
            {
                //打印当前信息
                printf("您选择了第%d条信息:",index);
                PrintPayrollTable(((Payroll *)(payrollList.array)) + index,1);
            }else
            {
                //退出编辑功能
                PrintLog("已退出编辑.");
                ShowMenu(GetCurrentCursor(),mainMenu,4)();
                return;
            }
        }else
        {
            PrintError("不存在第%d条信息!");
            inputAvailable = 0;
        }
    }while(!inputAvailable);
    //设置当前编辑对象
    toEdit = (Payroll *)payrollList.array + index;
    PrintLog("请输入需要修改的项目编号:");
    printf("[0]编号\n"
        "[1]姓名\n"
        "[2]基本工资\n"
        "[3]职务工资\n"
        "[4]津贴\n"
        "[5]养老保险\n"
        "[6]失业保险\n"
        "[7]公积金\n");
    do
    {
        inputAvailable = 1;
        scanf("%d",&column);
        if(column < 0 || column > 7)
        {
            PrintError("编号错误!请重新输入.");
            inputAvailable = 0;
        }
    } while(!inputAvailable);
    switch(column)
    {
    case 0:

        do
        {
            inputAvailable = 1;
            PrintLog("请输入ID,输入完毕后按下回车:");
            scanf("%s",tempID);
            printf("你输入的ID是\"%s\"\n",tempID);
            Payroll_Initialize(&tempPayroll,tempID,"",0,0,0,0,0,0,0,0,0,0);
            if(Payroll_IDExistInFArray(payrollList,tempPayroll))
            {
                PrintError("该编号已存在!");
                inputAvailable = 0;
            }
        }while(!inputAvailable);
        //录入ID
        FArray_Free(&toEdit->ID);
        FArray_Initialize(&toEdit->ID,sizeof(char),strlen(tempID)+1);
        memcpy(toEdit->ID.array,tempID,strlen(tempID)+1);
        break;
    case 1:
        PrintLog("请输入姓名:");
        scanf("%s",tempName);
        printf("你输入的姓名是:%s",tempName);
        //录入姓名
        FArray_Free(&toEdit->name);
        FArray_Initialize(&toEdit->name,sizeof(char),strlen(tempName)+1);
        memcpy(toEdit->name.array,tempName,strlen(tempName)+1);
        break;
    case 2:
        InputFloat("请输入基本工资:",&toEdit->baseWage,"基本工资:%f\n");
        break;
    case 3:
        InputFloat("请输入职务工资:",&toEdit->dutyWage,"职务工资:%f\n");
        break;
    case 4:
        InputFloat("请输入津贴:",&toEdit->bonus,"津贴:%f\n");
        break;
    case 5:
        InputFloat("请输入养老保险:",&toEdit->endowmentInsurance,"养老保险:%f\n");
        break;
    case 6:
        InputFloat("请输入失业保险:",&toEdit->unemploymentInsurance,"失业保险:%f\n");
        break;
    case 7:
        InputFloat("请输入公积金:",&toEdit->providentFund,"公积金:%f\n");
        break;
    }
    PrintLog("修改后信息如下:");
    PrintPayrollTable(toEdit,1);
    EndOfModule();
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
    PrintLog("【排序功能】- 按ID排序");
    //排序
    Payroll_SortByID(payrollList);
    EndOfModule();
}
//按姓名排序
void SortByName()
{
    PrintLog("【排序功能】- 按姓名排序");
    //排序
    Payroll_SortByName(payrollList);
    EndOfModule();
}
//按基本工资排序
void SortByBaseWage()
{
    PrintLog("【排序功能】- 按基本工资排序");
    //排序
    Payroll_SortByBaseWage(payrollList);
    EndOfModule();
}
//按实发工资排序
void SortByTakeHomePay()
{
    PrintLog("【排序功能】- 按实发工资排序");
    //排序
    Payroll_SortByTakeHomePay(payrollList);
    EndOfModule();
}

int main()
{
#ifdef TESTING
    int a[] = {0,0,0,0,0};
    printf("sizeof(a) = %d",sizeof(a));
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
        menuAction = ShowMenu(cursor,mainMenu,sizeof(mainMenu)/sizeof(MenuNode));
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
