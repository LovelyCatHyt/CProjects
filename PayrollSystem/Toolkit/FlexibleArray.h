#ifndef _FLEXIBLEARRAY_H_
#define _FLEXIBLEARRAY_H_

typedef struct
{
    void *array;
    int unitSize;
    int arraySize;
}FArray;

void FArray_Free(FArray *a);

void FArray_Add(FArray *a, void *element);

#endif // _FLEXIBLEARRAY_H
