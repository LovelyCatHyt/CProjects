#ifndef _FLEXIBLEARRAY_C_
#define _FLEXIBLEARRAY_C_
#include "FlexibleArray.h"
#include <string.h>
#include <stdlib.h>
#include "Debugger.h"

int FArray_Initialize(FArray *a , int unitSize, int arraySize)
{
    a->arraySize = 0;
    a->array = calloc(unitSize, arraySize);
    a->unitSize = unitSize;
    a->arraySize = arraySize;
    return a!=NULL?1:0;
}

void FArray_Free(FArray *a)
{
    free(a->array);
    a->arraySize = 0;
}

void FArray_Add(FArray *a, void *element)
{
    a->array = realloc(a->array,(a->arraySize+1)*a->unitSize);
    a->arraySize++;
    memcpy(a->array+(a->arraySize-1)*a->unitSize,element,a->unitSize);
}

#endif // FLEXIBLEARRAY

