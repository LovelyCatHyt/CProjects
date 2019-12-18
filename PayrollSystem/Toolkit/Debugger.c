#ifndef _DEBUGGER_C_
#define _DEBUGGER_C_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Debugger.h"
#include "ColorfulConsoler.h"
#include "MenuMgr.h"
#include "KeyCtrl.h"
#include "FlexibleArray.h"
#include "../Data/Payroll.h"
#include "../Data/DataInput.h"

int CmpInt(void * a, void *b)
{
    int ia,ib;
    ia = *((int *)a);
    ib = *((int *)b);
    return ia==ib;
}

void Test()
{
    FArray payrolls;
    FArray_Initialize(&payrolls,sizeof(Payroll),0);
    GetPayrolls(&payrolls);
    Payroll newpr;
    Payroll_Initialize(&newpr,"CSU200508","问题在这儿",3000,900,5000,50,100,20,560,0,0,0);
    Payroll_FillContent(&newpr);
    if(Payroll_IDExistInFArray(payrolls,newpr))
    {
        PrintError("This ID already exist!");
    }else
    {
        FArray_Add(&payrolls,(void *)&newpr);
    }
    PrintPayrollTable((Payroll*)payrolls.array,payrolls.arraySize);
    system("Pause");
}

void PrintCurrentTime()
{
    struct tm *t;
    time_t lct = time(NULL);
    t = localtime(&lct);
    printf("%02d:%02d:%02d",t->tm_hour,t->tm_min,t->tm_sec);
}

void PrintLog(char *log)
{
    SetColor(WHITE,BLACK);
    PrintCurrentTime();
    printf("[Log] ");
    while(*log)
    {
        putchar(*log);
        log++;
    }
    if(*(log-1)!='\n')
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

void PrintWarning(char *warning)
{
    SetColor(LIGHTYELLOW,BLACK);
    PrintCurrentTime();
    printf("[Warning] ");
    while(*warning)
    {
        putchar(*warning);
        warning++;
    }
    if(*(warning-1)!='\n')
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

void PrintError(char *error)
{
    SetColor(LIGHTRED,BLACK);
    PrintCurrentTime();
    printf("[Error] ");
    while(*error)
    {
        putchar(*error);
        error++;
    }
    if(*(error-1)!='\n')
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

#endif // _DEBUGGER_
