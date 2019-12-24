#ifndef _PAYROLL_JSON_H
#define _PAYROLL_JSON_H
#include "../Toolkit/FlexibleArray.h"
#include "Payroll.h"

int GetWholeFile(FArray *buffer,const char *fileName);
int SaveData(FArray payrollData);
int LoadData(FArray *out);
int FileEmpty(const char *fileName);

#endif //_PAYROLL_JSON_H
