#ifndef _DATAINPUT_C_
#define _DATAINPUT_C_
#include <stdio.h>
#include <stdlib.h>
#include "DataInput.h"
#include "Payroll.h"
#include "../Toolkit/Debugger.h"
#include "../Toolkit/FlexibleArray.h"

extern void (*DataInput)(FArray*);

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
    if(payrolls->arraySize>0)
    {
        /*释放FArray中的内容*/
        FArray_Free(payrolls);
    }
    //初始化
    FArray_Initialize(payrolls,sizeof(Payroll),0);
    return 1;
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
    //TODO
}
#endif //_DATAINPUT_C_
