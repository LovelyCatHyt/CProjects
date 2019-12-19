#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "DataInput.h"
#include "Payroll.h"
#include "../Toolkit/BetterIO.h"
#include "../Toolkit/Debugger.h"
#include "../Toolkit/FlexibleArray.h"

void (*DataInput)(FArray*) = UserInput;

/*获取工资数据表*/
int GetPayrolls(FArray* payrolls)
{
    DataInput(payrolls);
    return 1;
}

/*重置数据输入函数*/
void ResetInputFunction(void (*InputFunction)(FArray*))
{
    DataInput = InputFunction;
}

/*所有输入方法都需要先处理payrolls,因此独立出一个函数*/
int PreProcessPayrolls(FArray *payrolls)
{
    if(payrolls == NULL)
    {
        PrintError("Payrolls = NULL!");
        return 0;
    }
    return 1;
}

void InputFloat(const char *inputTip, float *target,const char *afterTipFormatter)
{
    PrintLog(inputTip);
    scanf("%f",target);
    printf(afterTipFormatter,*target);
}

/*直接生成数据*/
void HardInput(FArray* payrolls)
{
    if(!PreProcessPayrolls(payrolls))
    {
        return;
    }
    Payroll *newPayroll;
    newPayroll = (Payroll *)malloc(sizeof(Payroll));
    Payroll_Initialize(newPayroll,"CSU200501","张三",3000,900,5000,50,100,20,560,8900,525,8375);
    FArray_Add(payrolls,newPayroll);
    newPayroll = (Payroll *)malloc(sizeof(Payroll));
    Payroll_Initialize(newPayroll,"CSU200612","李四",2800,600,4000,45,80,19,550,7400,285,7115);
    FArray_Add(payrolls,newPayroll);
    newPayroll = (Payroll *)malloc(sizeof(Payroll));
    Payroll_Initialize(newPayroll,"CSU201208","王五",3200,1000,5600,55,110,22,580,9800,705,9095);
    FArray_Add(payrolls,newPayroll);
    newPayroll = (Payroll *)malloc(sizeof(Payroll));
    Payroll_Initialize(newPayroll,"CSU201608","赵六",2900,800,4800,48,100,21,560,8500,445,8055);
    FArray_Add(payrolls,newPayroll);
    newPayroll = (Payroll *)malloc(sizeof(Payroll));
    Payroll_Initialize(newPayroll,"CSU201698","陈七",3100,900,5200,52,110,22,570,9200,585,8615);
    FArray_Add(payrolls,newPayroll);

    //TODO
}
/*由用户输入数据*/
void UserInput(FArray* payrolls)
{
    if(!PreProcessPayrolls(payrolls))
    {
        return;
    }
    char tempID[32];
    char tempName[10];
    int loopInput = 0;
    char controlInput = 0;
    Payroll tempPayroll;
    int dataAvailable = 0;
    do
    {
        do
        {
            dataAvailable = 1;
            PrintLog("请输入ID,输入完毕后按下回车:");
            scanf("%s",tempID);
            PrintLogWithString("你输入的ID是\"%s\"\n",tempID);
            Payroll_Initialize(&tempPayroll,tempID,"",0,0,0,0,0,0,0,0,0,0);
            if(Payroll_IDExistInFArray(*payrolls,tempPayroll))
            {
                PrintError("该编号已存在!");
                dataAvailable = 0;
            }
        }while(!dataAvailable);
        PrintLog("请输入姓名:");
        scanf("%s",tempName);
        Payroll_Initialize(&tempPayroll,tempID,tempName,0,0,0,0,0,0,0,0,0,0);
        PrintLogWithString("你输入的姓名是\"%s\"\n",tempName);

        InputFloat("请输入基本工资:",&tempPayroll.baseWage,"基本工资:%.2f\n");
        InputFloat("请输入职务工资:",&tempPayroll.dutyWage,"职务工资:%.2f\n");
        InputFloat("请输入津贴:",&tempPayroll.bonus,"津贴:%.2f\n");
        InputFloat("请输入医疗保险:",&tempPayroll.healthInsurance,"医疗保险:%.2f\n");
        InputFloat("请输入养老保险:",&tempPayroll.endowmentInsurance,"养老保险:%.2f\n");
        InputFloat("请输入失业保险:",&tempPayroll.unemploymentInsurance,"失业保险:%.2f\n");
        InputFloat("请输入公积金:",&tempPayroll.providentFund,"公积金:%.2f\n");
        //计算公积金
        Payroll_FillContent(&tempPayroll);
        PrintLog("您输入的工资信息如下:");
        PrintPayrollTable(&tempPayroll,1);
        PrintLog("是否确认保存?按Esc取消,按回车键确定.");
        do
        {
            controlInput = getch();
        } while (controlInput  != 27 && controlInput != 13);
        switch (controlInput)
        {
        case 27:
            //Esc
            PrintLog("本次输入的数据已取消录入.");
            break;
        case 13:
            //Enter
            FArray_Add(payrolls,&tempPayroll);
            PrintLog("本次输入的数据已录入");
        default:
            //???
            break;
        }
        PrintLog("是否继续输入数据?按Esc取消,按回车键确定.");
        do
        {
            controlInput = getch();
        } while (controlInput  != 27 && controlInput != 13);
        switch (controlInput)
        {
        case 27:
            //Esc
            loopInput = 0;
            break;
        case 13:
            loopInput = 1;
        default:
            break;
        }
    }while(loopInput);
}
