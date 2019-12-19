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

void PrintLog(const char *log)
{
    int addNewLine = log[strlen(log) - 1]!='\n';
    SetColor(WHITE,BLACK);
    PrintCurrentTime();
    printf("[Log] ");
    while(*log)
    {
        putchar(*log);
        log++;
    }
    if(addNewLine)
    {
        putchar('\n');
    }
}

//打印带int参数的Log
void PrintLogWithInt(const char *formatter,const int a)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(WHITE,BLACK);
    PrintCurrentTime();
    printf("[Log] ");
    printf(formatter,a);
    if(addNewLine)
    {
        putchar('\n');
    }
}

void PrintLogWithString(const char *formatter,char *s)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(WHITE,BLACK);
    PrintCurrentTime();
    printf("[Log] ");
    printf(formatter,s);
    if(addNewLine)
    {
        putchar('\n');
    }
}

void PrintWarning(char *warning)
{
    int addNewLine = warning[strlen(warning) - 1]!='\n';
    SetColor(LIGHTYELLOW,BLACK);
    PrintCurrentTime();
    printf("[Warning] ");
    while(*warning)
    {
        putchar(*warning);
        warning++;
    }
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

//打印带Int的Warning
void PrintWarningWithInt(const char *formatter,int a)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(LIGHTYELLOW,BLACK);
    PrintCurrentTime();
    printf("[Warning] ");
    printf(formatter,a);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

//打印带String的Warning
void PrintWarningWithString(const char *formatter,char *s)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(LIGHTYELLOW,BLACK);
    PrintCurrentTime();
    printf("[Warning] ");
    printf(formatter,s);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

void PrintError(char *error)
{
    int addNewLine = error[strlen(error) - 1]!='\n';
    SetColor(LIGHTRED,BLACK);
    PrintCurrentTime();
    printf("[Error] ");
    while(*error)
    {
        putchar(*error);
        error++;
    }
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

//打印带Int参数的Error
void PrintErrorWithInt(const char *formatter,int a)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(LIGHTRED,BLACK);
    PrintCurrentTime();
    printf("[Error] ");
    printf(formatter,a);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}

//打印带String参数的Error
void PrintErrorWithString(const char *formatter,char *s)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetColor(LIGHTRED,BLACK);
    PrintCurrentTime();
    printf("[Error] ");
    printf(formatter,s);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetColor(WHITE,BLACK);
}
#endif // _DEBUGGER_
