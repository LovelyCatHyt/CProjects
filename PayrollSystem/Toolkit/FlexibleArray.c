#ifndef _FLEXIBLEARRAY_C_
#define _FLEXIBLEARRAY_C_
#include "FlexibleArray.h"
#include <string.h>
#include <stdlib.h>

FArray* FArray_Initialize(int unitSize, int arraySize)
{
    FArray* a = calloc(1,sizeof(FArray));
    a->array = calloc(unitSize, arraySize);
    a->unitSize = unitSize;
    a->arraySize = arraySize;
}

void FArray_Clear(FArray *a)
{
    free(a->array);
    a->arraySize = 0;
}

void FArray_Free(FArray *a)
{
    FArray_Clear(a);
    free(a);
}

void FArray_Add(FArray *a, void *element)
{
    a->array = realloc(a->array,(a->arraySize+1)*a->unitSize);
    a->arraySize++;
    memcpy(a->array+(a->arraySize-1)*a->unitSize,element,a->unitSize);
}

#endif // FLEXIBLEARRAY

