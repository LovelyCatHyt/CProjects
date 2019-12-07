#ifndef _PAYROLL_H_
#define _PAYROLL_H_

#include "../Toolkit/FlexibleArray.h"

typedef struct
{
    FArray *ID;
    FArray *name;
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

#endif // _PAYROLL_H_
