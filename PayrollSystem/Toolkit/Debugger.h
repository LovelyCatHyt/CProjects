#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <windows.h>

/*Debugger*/
void DBG_SetDefaultBg(WORD attr);
void PrintCurrentTime();
void PrintLog(const char *log);
void PrintLogWithInt(const char *formatter,int a);
void PrintLogWithString(const char *formatter,char *s);
void PrintWarning(char *warning);
void PrintWarningWithInt(const char *formatter,int a);
void PrintWarningWithString(const char *formatter,char *s);
void PrintError(char *error);
void PrintErrorWithInt(const char *formatter,int a);
void PrintErrorWithString(const char *formatter,char *s);

#endif // _DEBUGGER_H_
