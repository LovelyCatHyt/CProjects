//#define TESTING
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"
#include "Toolkit/Debugger.h"
#include "Toolkit/MenuMgr.h"
#include "Data/DataInput.h"
#include "Toolkit/ColorfulConsoler.h"

//全文件可见的工资表
static FArray payrollList = {NULL, 0, 0};
//主菜单
static MenuNode mainMenu[] =
    {
        {InputData, "输入数据", TRUE, NULL, 0},
        {EditData, "编辑数据", TRUE, NULL, 0},
        {NULL, "数据排序>", TRUE, (MenuNode[]){{SortByID, "ID排序", FALSE, NULL, 0}, {SortByName, "姓名排序", FALSE, NULL, 0}, {SortByBaseWage, "基本工资排序", FALSE, NULL, 0}, {SortByTakeHomePay, "实发工资排序", FALSE, NULL, 0}}, 4},
        {RemoveData, "删除数据", TRUE, NULL, 0},
        {DoStatistic, "统计数据", TRUE, 0},
        {SearchData, "查询数据", TRUE, 0},
        {ExitSystem, "退出系统", TRUE, NULL, 0}};

//一个模块的结束,包括打印最新工资表和显示主菜单
void EndOfModule()
{
    void (*action)(void) = NULL;
    PrintLog("当前工资表数据如下:");
    PrintPayrollTable((Payroll *)payrollList.array, payrollList.arraySize);
    action = ShowMenu(GetCurrentCursor(), mainMenu, sizeof(mainMenu) / sizeof(MenuNode));
    if (!action)
    {
        PrintError("Menu return a Null function pointer!");
    }
    else
    {
        action();
    }
}

//输入功能
void InputData()
{
    system("cls");
    PrintLog("【输入功能】");
    if (payrollList.array == NULL)
    {
        //如果为空则初始化
        FArray_Initialize(&payrollList, sizeof(Payroll), 0);
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
    system("cls");
    PrintLog("【编辑功能】");
    PrintPayrollTable((Payroll *)(payrollList.array), payrollList.arraySize);
    PrintLogWithInt("请选择要编辑的信息的索引(从0开始),目前共 %d 条.输入负数则退出编辑系统", payrollList.arraySize);
    do
    {
        inputAvailable = 1;
        scanf("%d", &index);
        if (index < payrollList.arraySize)
        {
            if (index >= 0)
            {
                //打印当前信息
                PrintLogWithInt("您选择了索引为%d的信息:", index);
                PrintPayrollTable(((Payroll *)(payrollList.array)) + index, 1);
            }
            else
            {
                //退出编辑功能
                PrintLog("已退出编辑.");
                EndOfModule();
                return;
            }
        }
        else
        {
            PrintErrorWithInt("不存在编号为%d的信息!", index);
            inputAvailable = 0;
        }
    } while (!inputAvailable);
    //复制当前编辑缓冲对象
    toEdit = (Payroll *)payrollList.array + index;
    Payroll_Initialize(&tempPayroll, (char *)toEdit->ID.array, (char *)toEdit->name.array, toEdit->baseWage, toEdit->dutyWage, toEdit->bonus, toEdit->healthInsurance, toEdit->endowmentInsurance, toEdit->unemploymentInsurance, toEdit->providentFund, toEdit->salary, toEdit->incomeTax, toEdit->takeHomePay);
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
        scanf("%d", &column);
        if (column < 0 || column > 7)
        {
            PrintError("编号错误!请重新输入.");
            inputAvailable = 0;
        }
    } while (!inputAvailable);
    switch (column)
    {
    case 0:

        do
        {
            inputAvailable = 1;
            PrintLog("请输入ID,输入完毕后按下回车:");
            scanf("%s", tempID); //TOFIX
            FArray_CopyMemory(&tempPayroll.ID, tempID, strlen(tempID) + 1);
            PrintLogWithString("你输入的ID是\"%s\"", (char *)tempPayroll.ID.array);
            if (Payroll_IDExistInFArray(payrollList, tempPayroll))
            {
                PrintError("该编号已存在!");
                inputAvailable = 0;
            }
        } while (!inputAvailable);
        break;
    case 1:
        PrintLog("请输入姓名:");
        scanf("%s", tempName);
        PrintLogWithString("你输入的姓名是:%s", tempName);
        //录入姓名
        FArray_CopyMemory(&tempPayroll.name, tempName, strlen(tempName) + 1);
        break;
    case 2:
        InputFloat("请输入基本工资:", &tempPayroll.baseWage, "基本工资:%f\n");
        break;
    case 3:
        InputFloat("请输入职务工资:", &tempPayroll.dutyWage, "职务工资:%f\n");
        break;
    case 4:
        InputFloat("请输入津贴:", &tempPayroll.bonus, "津贴:%f\n");
        break;
    case 5:
        InputFloat("请输入养老保险:", &tempPayroll.endowmentInsurance, "养老保险:%f\n");
        break;
    case 6:
        InputFloat("请输入失业保险:", &tempPayroll.unemploymentInsurance, "失业保险:%f\n");
        break;
    case 7:
        InputFloat("请输入公积金:", &tempPayroll.providentFund, "公积金:%f\n");
        break;
    }
    //更新应发工资 个税 实付工资
    Payroll_FillContent(&tempPayroll);
    PrintLog("原信息:");
    PrintPayrollTable((Payroll *)payrollList.array + index, 1);
    PrintLog("修改后信息如下:");
    PrintPayrollTable(&tempPayroll, 1);
    PrintWarning("是否保存编辑的信息?按回车键确认,按Esc取消.");
    do
    {
        inputAvailable = 1;
        switch (getch())
        {
        case 13:
            //保存数据
            *((Payroll *)payrollList.array + index) = tempPayroll;
            break;
        case 27:
            //退出
            inputAvailable = 1;
            break;
        default:
            inputAvailable = 0;
            break;
        }
    } while (!inputAvailable);
    EndOfModule();
}
//删除数据
void RemoveData()
{
    int inputAvailable;
    int index = -1;
    system("cls");
    PrintLog("【删除功能】\n");
    PrintLog("当前工资表:");
    PrintPayrollTable((Payroll *)payrollList.array, payrollList.arraySize);
    PrintLogWithInt("请选择要删除的项的编号(从0开始),目前共%d项.输入负数则退出删除功能", payrollList.arraySize);
    do
    {
        inputAvailable = 1;
        scanf("%d", &index);
        if (index >= payrollList.arraySize)
        {
            PrintErrorWithInt("错误编号!不存在编号为%d的项", index);
            inputAvailable = 0;
        }
        else if (index < 0)
        {
            PrintLog("删除功能退出.");
            EndOfModule();
            return;
        }
    } while (!inputAvailable);
    //删除这一项数据
    int sureToRemove = 0;
    PrintWarning("警告:此操作不可撤销!是否继续?若继续请按回车.");
    if (getch() == 13)
    {
        FArray_RemoveAt(&payrollList, index);
        PrintLogWithInt("编号为%d的项已删除.", index);
    }
    PrintLog("删除功能退出.");
    EndOfModule();
}
//统计数据
void DoStatistic()
{
    system("cls");
    PrintLog("【统计功能】");
    int lowIncome = 0, middleIncome = 0, highIncome = 0;
    Payroll maximums, minimums, averages;
    Payroll *list = (Payroll *)payrollList.array;
    int arraySize = payrollList.arraySize;
    int i;
    if (arraySize <= 0)
    {
        PrintError("无可用数据!无法进行统计.");
        EndOfModule();
        return;
    }
    minimums = maximums = list[0];
    Payroll_Initialize(&averages, " - ", "平均值", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    for (i = 0; i < arraySize; i++)
    {
        //求最大值
        maximums.baseWage = list[i].baseWage > maximums.baseWage ? list[i].baseWage : maximums.baseWage;
        maximums.bonus = list[i].bonus > maximums.bonus ? list[i].bonus : maximums.bonus;
        maximums.dutyWage = list[i].dutyWage > maximums.dutyWage ? list[i].dutyWage : maximums.dutyWage;
        maximums.healthInsurance = list[i].healthInsurance > maximums.healthInsurance ? list[i].healthInsurance : maximums.healthInsurance;
        maximums.endowmentInsurance = list[i].endowmentInsurance > maximums.endowmentInsurance ? list[i].endowmentInsurance : maximums.endowmentInsurance;
        maximums.unemploymentInsurance = list[i].unemploymentInsurance > maximums.unemploymentInsurance ? list[i].unemploymentInsurance : maximums.unemploymentInsurance;
        maximums.providentFund = list[i].providentFund > maximums.providentFund ? list[i].providentFund : maximums.providentFund;
        maximums.salary = list[i].salary > maximums.salary ? list[i].salary : maximums.salary;
        maximums.incomeTax = list[i].incomeTax > maximums.incomeTax ? list[i].incomeTax : maximums.incomeTax;
        maximums.takeHomePay = list[i].takeHomePay > maximums.takeHomePay ? list[i].takeHomePay : maximums.takeHomePay;
        //求最小值
        minimums.baseWage = list[i].baseWage < minimums.baseWage ? list[i].baseWage : minimums.baseWage;
        minimums.bonus = list[i].bonus < minimums.bonus ? list[i].bonus : minimums.bonus;
        minimums.dutyWage = list[i].dutyWage < minimums.dutyWage ? list[i].dutyWage : minimums.dutyWage;
        minimums.healthInsurance = list[i].healthInsurance < minimums.healthInsurance ? list[i].healthInsurance : minimums.healthInsurance;
        minimums.endowmentInsurance = list[i].endowmentInsurance < minimums.endowmentInsurance ? list[i].endowmentInsurance : minimums.endowmentInsurance;
        minimums.unemploymentInsurance = list[i].unemploymentInsurance < minimums.unemploymentInsurance ? list[i].unemploymentInsurance : minimums.unemploymentInsurance;
        minimums.providentFund = list[i].providentFund < minimums.providentFund ? list[i].providentFund : minimums.providentFund;
        minimums.salary = list[i].salary < minimums.salary ? list[i].salary : minimums.salary;
        minimums.incomeTax = list[i].incomeTax < minimums.incomeTax ? list[i].incomeTax : minimums.incomeTax;
        minimums.takeHomePay = list[i].takeHomePay < minimums.takeHomePay ? list[i].takeHomePay : minimums.takeHomePay;
        //求和
        averages.baseWage += list[i].baseWage;
        averages.dutyWage += list[i].dutyWage;
        averages.bonus += list[i].bonus;
        averages.endowmentInsurance += list[i].endowmentInsurance;
        averages.healthInsurance += list[i].healthInsurance;
        averages.providentFund += list[i].providentFund;
        averages.unemploymentInsurance += list[i].unemploymentInsurance;
        averages.salary += list[i].salary;
        averages.incomeTax += list[i].incomeTax;
        averages.takeHomePay += list[i].takeHomePay;
        //统计不同工资层次的数量
        if (list[i].takeHomePay < 5000)
            lowIncome++;
        if (list[i].takeHomePay >= 5000 && list[i].takeHomePay < 10000)
            middleIncome++;
        if(list[i].takeHomePay > 10000)
            highIncome++;
    }
    //求平均(大括号是为了方便在编辑视图中收起来)
    {
        averages.baseWage /= arraySize;
        averages.dutyWage /= arraySize;
        averages.bonus /= arraySize;
        averages.endowmentInsurance /= arraySize;
        averages.healthInsurance /= arraySize;
        averages.providentFund /= arraySize;
        averages.unemploymentInsurance /= arraySize;
        averages.salary /= arraySize;
        averages.incomeTax /= arraySize;
        averages.takeHomePay /= arraySize;
    }
    SetColor(WHITE, BLACK);
    printf("低收入(少于5000):");
    SetColor(LIGHTWHITE, BLACK);
    printf("%d\n",lowIncome);
    SetColor(WHITE, BLACK);
    printf("中等收入(5000~10000):",middleIncome);
    SetColor(LIGHTWHITE, BLACK);
    printf("%d\n", middleIncome);
    SetColor(WHITE, BLACK);
    printf("高收入(10000以上):");
    SetColor(LIGHTWHITE, BLACK);
    printf("%d\n", highIncome);
    SetColor(AQUA, BLACK);
    printf("统计项目 基本工资 职务工资 津贴     医疗保险 养老保险 失业保险 公积金   应发工资 个人税   实发工资\n");
    SetColor(LIGHTRED, BLACK);
    printf("最大值   %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
           maximums.baseWage,
           maximums.dutyWage,
           maximums.bonus,
           maximums.healthInsurance,
           maximums.endowmentInsurance,
           maximums.unemploymentInsurance,
           maximums.providentFund,
           maximums.salary,
           maximums.incomeTax,
           maximums.takeHomePay);
    SetColor(PALEGREEN, BLACK);
    printf("最小值   %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
           minimums.baseWage,
           minimums.dutyWage,
           minimums.bonus,
           minimums.healthInsurance,
           minimums.endowmentInsurance,
           minimums.unemploymentInsurance,
           minimums.providentFund,
           minimums.salary,
           minimums.incomeTax,
           minimums.takeHomePay);
    SetColor(LIGHTWHITE, BLACK);
    printf("平均值   %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
           averages.baseWage,
           averages.dutyWage,
           averages.bonus,
           averages.healthInsurance,
           averages.endowmentInsurance,
           averages.unemploymentInsurance,
           averages.providentFund,
           averages.salary,
           averages.incomeTax,
           averages.takeHomePay);
    SetColor(WHITE, BLACK);
    EndOfModule();
}
//查询数据
void SearchData()
{
    int inputAvailable;
    int itemIndex;
    char toSearchString[32];
    float min, max;
    Payroll *list = (Payroll *)payrollList.array;
    int arraySize = payrollList.arraySize;
    int i;
    FArray foundList;
    //TODO
    system("cls");
    PrintLog("【查询功能】(未完成)");
    PrintLog("请选择要查询的项目:");
    printf("[0]编号(ID)查询\n[1]姓名查询\n[2]实发工资区间查询\n");
    do
    {
        inputAvailable = 1;
        scanf("%d", &itemIndex);
        if (itemIndex > 2 || itemIndex < 0)
        {
            PrintError("错误输入!请重新选择要查询的项目:");
            inputAvailable = 0;
        }
    } while (!inputAvailable);
    FArray_Initialize(&foundList, sizeof(Payroll), 0);
    switch (itemIndex)
    {
    case 0:
        PrintLog("请输入要查询的编号:");
        scanf("%s", toSearchString);
        for (i = 0; i < arraySize; i++)
        {
            if (strcmp((char *)list[i].ID.array, toSearchString) == 0)
            {
                //找到就在列表中添加上去
                FArray_Add(&foundList, &list[i]);
            }
        }
        break;
    case 1:
        PrintLog("请输入要查询的姓名:");
        scanf("%s", toSearchString);
        for (i = 0; i < arraySize; i++)
        {
            if (strcmp((char *)list[i].name.array, toSearchString) == 0)
            {
                //找到就在列表中添加上去
                FArray_Add(&foundList, &list[i]);
            }
        }
        break;
    case 2:
        PrintLog("请输入要查询的实发工资下限:");
        scanf("%f", &min);
        PrintLog("请输入上限:");
        scanf("%f", &max);
        for (i = 0; i < arraySize; i++)
        {
            if (list[i].takeHomePay >= min && list[i].takeHomePay <= max)
            {
                //在列表中添加
                FArray_Add(&foundList, &list[i]);
            }
        }
        break;
    }
    if (foundList.arraySize == 0)
    {
        PrintLog("无查询结果!");
    }
    else
    {
        PrintLog("查询结果如下:");
        PrintPayrollTable((Payroll *)foundList.array, foundList.arraySize);
    }
    //释放内存
    FArray_Free(&foundList);
    EndOfModule();
}
//退出系统
void ExitSystem()
{
    system("cls");
    PrintWarning("确定要退出吗? 按回车确定,否则继续.");
    if (getch() == 13)
    {
        PrintLog("感谢您的使用,期待下次再见!");
        return;
    }
    EndOfModule();
}
//按ID排序
void SortByID()
{
    PrintLog("【排序功能】- 按ID排序\n");
    //排序
    Payroll_SortByID(payrollList);
    EndOfModule();
}
//按姓名排序
void SortByName()
{
    PrintLog("【排序功能】- 按姓名排序\n");
    //排序
    Payroll_SortByName(payrollList);
    EndOfModule();
}
//按基本工资排序
void SortByBaseWage()
{
    PrintLog("【排序功能】- 按基本工资排序\n");
    //排序
    Payroll_SortByBaseWage(payrollList);
    EndOfModule();
}
//按实发工资排序
void SortByTakeHomePay()
{
    PrintLog("【排序功能】- 按实发工资排序\n");
    //排序
    Payroll_SortByTakeHomePay(payrollList);
    EndOfModule();
}

int main()
{
#ifdef TESTING
    int a[] = {0, 0, 0, 0, 0};
    printf("sizeof(a) = %d", sizeof(a));
#else // TESTING
    COORD cursor;
    void (*menuAction)(void) = NULL;
    while (!menuAction)
    {
        //获取当前光标位置
        cursor = GetCurrentCursor();
        //开新的一行
        cursor.X = 0;
        cursor.Y++;
        //展示菜单
        menuAction = ShowMenu(cursor, mainMenu, sizeof(mainMenu) / sizeof(MenuNode));
        //执行菜单返回的函数
        if (menuAction)
        {
            menuAction();
        }
        else
        {
            PrintError("ExitMenu with empty funtion pointer!\n");
        }
    }
#endif
    return 0;
}
