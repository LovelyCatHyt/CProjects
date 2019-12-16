#ifndef _DEBUGGER_C_
#define _DEBUGGER_C_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Debugger.h"
#include "ColorfulConsoler.h"
#include "MenuMgr.h"
#include "KeyCtrl.h"

void PrintSomething()
{
    printf("HaHaHa\n");
}

void Test()
{
    /*
    FArray payrolls;
    FArray_Initialize(&payrolls,sizeof(Payroll),0);
    GetPayrolls(&payrolls);
    PrintPayrollTable((Payroll *)payrolls.array,payrolls.arraySize);
    PrintWarning("Now I'm trying to sort them by basewage...\n\n\n");
    Payroll_SortByBaseWage(payrolls);
    PrintPayrollTable((Payroll *)payrolls.array,payrolls.arraySize);
    Payroll_FreePayrolls(payrolls);
    */
    MenuNode testMenu[2] = {
                        {NULL,"Root0",NULL,
                            (MenuNode []){
                                {
                                    PrintSomething,
                                    "PrintSomething",
                                    NULL,
                                    NULL,
                                    0
                                },
                                {
                                    PrintSomething,
                                    "AlsoPrintSth",
                                    NULL,
                                    NULL,
                                    0
                                }
                            }
                        ,2},
                        {NULL,"Root1",NULL,NULL,0}
    };
    void (*action)(void) = ShowMenu(SHORT2COORD(0,0),testMenu,2);
    if(action == NULL)
    {
        printf("MenuExited.");
    }else
    {
        action();
    }

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
