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
    int length;
    length = strlen(ID);
    pr->ID = FArray_Initialize(sizeof(char),length);
    memcpy(pr->ID->array,ID,length);
    length = strlen(name);
    pr->name = FArray_Initialize(sizeof(char),length);
    memcpy(pr->name->array,name,length);
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

#endif // _PAYROLL_
