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

static WORD defaultAttr = 0x0f;
static WORD warningAttr = 0x0e;
static WORD errorAttr = 0x0c;

//设置默认的字符属性,传入参数仅使用5~8位
void DBG_SetDefaultBg(WORD attr)
{
    //在背景色一栏置0
    defaultAttr &= 0x0f;
    //重新设置背景色
    defaultAttr |= attr & 0xf0;
    //以下同理
    warningAttr &= 0x0f;
    warningAttr |= attr & 0xf0;
    errorAttr &= 0x0f;
    errorAttr |= attr & 0xf0;
}

int CmpInt(void * a, void *b)
{
    int ia,ib;
    ia = *((int *)a);
    ib = *((int *)b);
    return ia==ib;
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
    SetAttribute(defaultAttr);
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
    SetAttribute(defaultAttr);
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
    SetAttribute(defaultAttr);
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
    SetAttribute(warningAttr);
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
    SetAttribute(defaultAttr);
}

//打印带Int的Warning
void PrintWarningWithInt(const char *formatter,int a)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetAttribute(warningAttr);
    PrintCurrentTime();
    printf("[Warning] ");
    printf(formatter,a);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetAttribute(defaultAttr);
}

//打印带String的Warning
void PrintWarningWithString(const char *formatter,char *s)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetAttribute(warningAttr);
    PrintCurrentTime();
    printf("[Warning] ");
    printf(formatter,s);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetAttribute(defaultAttr);
}

void PrintError(char *error)
{
    int addNewLine = error[strlen(error) - 1]!='\n';
    SetAttribute(errorAttr);
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
    SetAttribute(defaultAttr);
}

//打印带Int参数的Error
void PrintErrorWithInt(const char *formatter,int a)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetAttribute(errorAttr);
    PrintCurrentTime();
    printf("[Error] ");
    printf(formatter,a);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetAttribute(defaultAttr);
}

//打印带String参数的Error
void PrintErrorWithString(const char *formatter,char *s)
{
    int addNewLine = formatter[strlen(formatter) - 1]!='\n';
    SetAttribute(errorAttr);
    PrintCurrentTime();
    printf("[Error] ");
    printf(formatter,s);
    if(addNewLine)
    {
        putchar('\n');
    }
    SetAttribute(defaultAttr);
}
#endif // _DEBUGGER_
