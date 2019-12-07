#ifndef _DATAINPUT_H_
#define _DATAINPUT_H_
#include "Payroll.h"
#include "../Toolkit/FlexibleArray.h"

void ResetInputFunction(void (*InputFunction)(FArray*));
void HardInput(FArray* payrolls);
void UserInput(FArray* payrolls);

void (*DataInput)(FArray*) = HardInput;

#endif // _DATAINPUT_H_
