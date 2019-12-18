#ifndef _DATAINPUT_H_
#define _DATAINPUT_H_
#include "Payroll.h"
#include "../Toolkit/FlexibleArray.h"

int GetPayrolls(FArray* payrolls);
void ResetInputFunction(void (*InputFunction)(FArray*));
void HardInput(FArray* payrolls);
void UserInput(FArray* payrolls);
void InputFloat(const char *inputTip, float *target,const char *afterTipFormatter);
#endif // _DATAINPUT_H_
