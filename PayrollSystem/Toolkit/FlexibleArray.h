#ifndef _FLEXIBLEARRAY_H_
#define _FLEXIBLEARRAY_H_

typedef struct
{
    void *array;
    int unitSize;
    int arraySize;
}FArray;

int FArray_Initialize(FArray *a , int unitSize, int arraySize);

void FArray_Free(FArray *a);

void FArray_Add(FArray *a, void *element);
void FArray_RemoveAt(FArray *a, int index);
int FArray_SearchByCondition(FArray a, void *toSearch, int (*condition)(void * a, void * b));
int FArray_Search(FArray a, void *toSearch);

#endif // _FLEXIBLEARRAY_H
