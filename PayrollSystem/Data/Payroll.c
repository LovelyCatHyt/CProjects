#ifndef _PAYROLL_C_
#define _PAYROLL_C_
#include "Payroll.h"
#include "../Toolkit/FlexibleArray.h"
#include <string.h>

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

    FArray_Initialize(&pr->ID,sizeof(char),strlen(ID));
    memcpy(pr->ID.array,ID,strlen(ID));
    FArray_Initialize(&pr->name,sizeof(char),strlen(name));
    memcpy(pr->name.array,name,strlen(name));

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
    return pr;
}

void PrintPayroll(Payroll pr,int withTag)
{
    if(withTag)
    {
        printf("职工编号  姓名   基本工资 职务工资 津贴     医疗保险 养老保险 失业保险 公积金   应发工资 个人税   实发工资\n");
    }
    printf("%-9s %-6s %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f",
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
}

void PrintPayrolls(Payroll *prs,int arraySize)
{
    int i;
    PrintPayroll(prs[0],1);
    for(i = 1;i<arraySize;i++)
    {
        PrintPayroll(prs[i],0);
    }
}

#endif // _PAYROLL_
