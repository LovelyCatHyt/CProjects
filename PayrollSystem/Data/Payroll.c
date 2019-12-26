#ifndef _PAYROLL_C_
#define _PAYROLL_C_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Payroll.h"
#include "../Toolkit/FlexibleArray.h"
#include "../Toolkit/ColorfulConsoler.h"
#include "../Settings/Settings.h"
#include "../main.h"

extern Settings settings;

void Payroll_Initialize(
    Payroll *pr,
    char *ID,
    char *name,
    float baseWage,
    float dutyWage,
    float bonus,
    float healthInsurance,
    float endowmentInsurance,
    float unemploymentInsurance,
    float providentFund,
    float salary,
    float incomeTax,
    float takeHomePay)
{

    FArray_Initialize(&pr->ID,sizeof(char),strlen(ID)+1);
    memcpy(pr->ID.array,ID,strlen(ID)+1);
    FArray_Initialize(&pr->name,sizeof(char),strlen(name)+1);
    memcpy(pr->name.array,name,strlen(name)+1);

    pr->baseWage = baseWage;
    pr->dutyWage = dutyWage;
    pr->bonus = bonus;
    pr->healthInsurance = healthInsurance;
    pr->endowmentInsurance = endowmentInsurance;
    pr->unemploymentInsurance = unemploymentInsurance;
    pr->providentFund = providentFund;
    pr->salary = salary;
    pr->incomeTax = incomeTax;
    pr->takeHomePay = takeHomePay;
}

void Payroll_FreeFArray(Payroll pr)
{
    FArray_Free(&(pr.ID));
    FArray_Free(&(pr.name));
}

void Payroll_FreePayrolls(FArray payrolls)
{
    int i;
    for(i = 0;i<payrolls.arraySize;i++)
    {
        Payroll_FreeFArray(((Payroll *)payrolls.array)[i]);
    }
}

//检查是否几倍相同ID
//专为SearchByCondition函数设计的函数,所以参数是void *
int Payroll_HasSameID(void * a, void * b)
{
    Payroll prA = *((Payroll *)a);
    Payroll prB = *((Payroll *)b);
    //ID用strcmp返回0说明相同
    return strcmp((char *)prA.ID.array,(char *)prB.ID.array) == 0;
}

//在数组中有重复ID的Payroll
int Payroll_IDExistInFArray(FArray prArray, Payroll toSeach)
{
    return FArray_SearchByCondition(prArray,(void *)&toSeach,Payroll_HasSameID) != -1;
}

//填充Payroll中需要计算的内容(这个操作描述太长 不知道怎么翻译)
void Payroll_FillContent(Payroll *toFill)
{
    //应发工资
    toFill->salary = toFill->baseWage + toFill->dutyWage + toFill->bonus;
    //应纳税所得额 = 应发工资 - 医疗保险 - 养老保险 - 失业保险 - 公积金
    float taxToCount = toFill->salary -
        toFill->healthInsurance -
        toFill->endowmentInsurance -
        toFill->unemploymentInsurance -
        toFill->providentFund;
    float totalTax = 0;
    //税收阶梯数组
    float taxPeakList[8] = {0,3500,5000,8000,12500,38500,58500,83500};
    float taxRateList[8] = {0,0.03,0.1,0.2,0.25,0.3,0.35,0.45};
    int i;
    if(taxToCount > taxPeakList[7])
    {
        totalTax += (taxToCount - taxPeakList[7]) * taxRateList[7];
        taxToCount = taxPeakList[7];
    }
    for(i = 6;i>=0;i--)
    {
        //从后往前遍历
        if(taxToCount>taxPeakList[i] && taxToCount <= taxPeakList[i+1])
        {
            totalTax += (taxToCount - taxPeakList[i]) * taxRateList[i];
            taxToCount = taxPeakList[i];
        }
    }
    //个税额
    toFill->incomeTax = totalTax;
    //实发工资 = 应发工资 - 医疗保险 - 养老保险 - 失业保险 - 公积金 - 个人所得税
    toFill->takeHomePay = toFill->salary -
        toFill->healthInsurance -
        toFill->endowmentInsurance -
        toFill->unemploymentInsurance -
        toFill->providentFund -
        toFill->incomeTax;
}

/*一系列必要的比较函数*/
/*因为一共有十二项数据,编写和除错工作量巨大,所以仅对四项数据处理*/
int floatCmp(float a, float b)
{
    float tmp = a-b;
    if(tmp>0) return 1;
    else if(tmp==0) return 0;
    else return -1;
}
int Payroll_CmpByID(const void *a, const void *b)
{
    return strcmp(((Payroll *)a)->ID.array,((Payroll *)b)->ID.array);
}
int Payroll_CmpByName(const void *a, const void *b)
{
    return strcmp(((Payroll *)a)->name.array,((Payroll *)b)->name.array);
}
int Payroll_CmpByBaseWage(const void *a, const void *b)
{
    return floatCmp(((Payroll *)a)->baseWage,((Payroll *)b)->baseWage);
}
int Payroll_CmpByTakeHomePay(const void *a, const void *b)
{
    return floatCmp(((Payroll *)a)->takeHomePay,((Payroll *)b)->takeHomePay);
}

/*一系列排序函数*/
void Payroll_SortByID(FArray payrolls)
{
    qsort((Payroll *)payrolls.array,payrolls.arraySize,payrolls.unitSize,Payroll_CmpByID);
}
void Payroll_SortByName(FArray payrolls)
{
    qsort((Payroll *)payrolls.array,payrolls.arraySize,payrolls.unitSize,Payroll_CmpByName);
}
void Payroll_SortByBaseWage(FArray payrolls)
{
    qsort((Payroll *)payrolls.array,payrolls.arraySize,payrolls.unitSize,Payroll_CmpByBaseWage);
}
void Payroll_SortByTakeHomePay(FArray payrolls)
{
    qsort((Payroll *)payrolls.array,payrolls.arraySize,payrolls.unitSize,Payroll_CmpByTakeHomePay);
}

void PrintTableTop(WORD attr)
{
    SetAttribute(attr);
    printf("   职工编号  姓名     基本工资 职务工资 津贴     医疗保险 养老保险 失业保险 公积金   应发工资 个人税   实发工资\n");
    SetAttribute(settings.consoleDefaultAttr);
}

void PrintPayroll(Payroll pr,WORD attr)
{
    SetAttribute(attr);
    printf("   %-9s %-8s %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
           (char *)pr.ID.array,
           (char *)pr.name.array,
           pr.baseWage,
           pr.dutyWage,
           pr.bonus,
           pr.healthInsurance,
           pr.endowmentInsurance,
           pr.unemploymentInsurance,
           pr.providentFund,
           pr.salary,
           pr.incomeTax,
           pr.takeHomePay);
    SetAttribute(settings.consoleDefaultAttr);
}

void PrintPayrollTable(Payroll *prs,int arraySize)
{
    int i;
    PrintTableTop(settings.tagAttr);
    for(i = 0;i<arraySize;i++)
    {
        WORD attr;
        if(i%2==0)
        {
            attr = settings.contentAttrA;
        }else
        {
            attr = settings.contentAttrB;
        }
        SetAttribute(attr);
        printf("[%d]%-9s %-8s %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
           i,
           (char *)prs[i].ID.array,
           (char *)prs[i].name.array,
           prs[i].baseWage,
           prs[i].dutyWage,
           prs[i].bonus,
           prs[i].healthInsurance,
           prs[i].endowmentInsurance,
           prs[i].unemploymentInsurance,
           prs[i].providentFund,
           prs[i].salary,
           prs[i].incomeTax,
           prs[i].takeHomePay);
        SetAttribute(settings.consoleDefaultAttr);
    }
    SetAttribute(settings.consoleDefaultAttr);
}

#endif // _PAYROLL_
