#ifndef _PAYROLL_H_
#define _PAYROLL_H_

#include "../Toolkit/FlexibleArray.h"

typedef struct
{
    FArray ID;
    FArray name;
    float baseWage;
    float dutyWage;
    float bonus;
    float healthInsurance;
    float endowmentInsurance;
    float unemploymentInsurance;
    float providentFund;
    float salary;
    float incomeTax;
    float takeHomePay;
}Payroll;

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
    float takeHomePay
);

void Payroll_FreeFArray(Payroll pr);

int Payroll_CmpByID(const Payroll *a, const Payroll *b);
int Payroll_CmpByName(const Payroll *a, const Payroll *b);
int Payroll_CmpByID(const Payroll *a, const Payroll *b);
int Payroll_CmpByTakeHomePay(const Payroll *a, const Payroll *b);

void Payroll_SortByID(FArray payrolls);
void Payroll_SortByName(FArray payrolls);
void Payroll_SortByBaseWage(FArray payrolls);
void Payroll_SortByTakeHomePay(FArray payrolls);

void PrintPayroll(Payroll pr,unsigned int foreColor,unsigned int backgroundColor);

void PrintPayrollTable(Payroll *prs,int arraySize);
#endif // _PAYROLL_H_
