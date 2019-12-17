#ifndef _PAYROLL_C_
#define _PAYROLL_C_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Payroll.h"
#include "../Toolkit/FlexibleArray.h"
#include "../Toolkit/ColorfulConsoler.h"

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

//���Payroll����Ҫ���������(�����������̫�� ��֪����ô����)
void Payroll_FillContent(Payroll *toFill)
{
    //Ӧ������
    toFill->salary = toFill->baseWage + toFill->dutyWage + toFill->bonus;
    //Ӧ��˰���ö� = Ӧ������ - ҽ�Ʊ��� - ���ϱ��� - ʧҵ���� - ������
    float taxToCount = toFill->salary -
        toFill->healthInsurance -
        toFill->endowmentInsurance -
        toFill->unemploymentInsurance -
        toFill->providentFund;
    float totalTax = 0;
    //˰�ս�������
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
        //�Ӻ���ǰ����
        if(taxToCount>taxPeakList[i] && taxToCount <= taxPeakList[i+1])
        {
            totalTax += (taxToCount - taxPeakList[i]) * taxRateList[i];
            taxToCount = taxPeakList[i];
        }
    }
    //��˰��
    toFill->incomeTax = totalTax;
    //ʵ������ = Ӧ������ - ҽ�Ʊ��� - ���ϱ��� - ʧҵ���� - ������ - ��������˰
    toFill->takeHomePay = toFill->salary -
        toFill->healthInsurance -
        toFill->endowmentInsurance -
        toFill->unemploymentInsurance -
        toFill->providentFund -
        toFill->incomeTax;
}

/*һϵ�б�Ҫ�ıȽϺ���*/
/*��Ϊһ����ʮ��������,��д�ͳ��������޴�,���Խ����������ݴ���*/
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

/*һϵ��������*/
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

void PrintTableTop(unsigned int foreColor,unsigned int backgroundColor)
{
    SetColor(foreColor,backgroundColor);
    printf("ְ�����  ����   �������� ְ���� ����     ҽ�Ʊ��� ���ϱ��� ʧҵ���� ������   Ӧ������ ����˰   ʵ������\n");
    SetColor(WHITE,BLACK);
}

void PrintPayroll(Payroll pr,unsigned int foreColor,unsigned int backgroundColor)
{
    SetColor(foreColor,backgroundColor);
    printf("%-9s %-6s %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f\n",
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
    SetColor(WHITE,BLACK);
}

void PrintPayrollTable(Payroll *prs,int arraySize)
{
    int i;
    PrintTableTop(LIGHTBLUE,BLACK);
    for(i = 0;i<arraySize;i++)
    {
        unsigned int color;
        color = i%2?BLACK:GRAY;
        PrintPayroll(prs[i],WHITE,color);
    }
    SetColor(WHITE,BLACK);
}

#endif // _PAYROLL_
