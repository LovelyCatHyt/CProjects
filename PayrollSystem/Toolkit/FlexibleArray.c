#ifndef _FLEXIBLEARRAY_C_
#define _FLEXIBLEARRAY_C_
#include "FlexibleArray.h"
#include <string.h>
#include <stdlib.h>
#include "Debugger.h"

int FArray_Initialize(FArray *a , int unitSize, int arraySize)
{
    a->arraySize = arraySize;
    a->unitSize = unitSize;
    a->array = calloc(unitSize, arraySize);
    return (a->array!=NULL)? 1 : 0;
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

void FArray_RemoveAt(FArray *a, int index)
{
    int i;
    if(index <= a->arraySize)
    {
        for(i = index;i<a->arraySize;i++)
        {
            memcpy(a->array + (i*a->unitSize),a->array + ((i+1)*a->unitSize),a->unitSize);
        }
        a->arraySize--;
        a->array = realloc(a->array,(a->arraySize)*a->unitSize);
    }else
    {
        PrintError("执行Remove操作时 index 下标越界!");
    }

}

int FArray_CopyMemory(FArray *a, void *src, int byte)
{
    if(byte % a->unitSize!=0)
    {
        //如果byte不是unitSize的整倍数
        return 0;
    }
    //先清除数据
    FArray_Free(a);
    //再重置之
    if(FArray_Initialize(a,a->unitSize, byte / a->unitSize))
    {
        memcpy(a->array,src,byte);

    }else
    {
        PrintError("Can't copy memory!");
    }

    return 1;
}

int CmpMemory(void *a, void *b,size_t memorySize)
{
    char *ca,*cb;
    int i;
    char same = 1;
    ca = (char *)a;
    cb = (char *)b;
    for(i = 0;i<memorySize;i++)
    {
        if(*(ca+i) != *(cb+i))
        {
            //不一样
            same = 0;
            break;
        }
    }
    return same;
}

//按照给出的相等条件搜索是否存在某个元素匹配条件,存在则返回第一个匹配的元素索引,不存在则返回-1
int FArray_SearchByCondition(FArray a, void *toSearch, int (*condition)(void * a, void * b))
{
    int i;
    int result = -1;
    for(i = 0;i<a.arraySize;i++)
    {
        if(condition(a.array + i*a.unitSize, toSearch))
        {
            result = i;
            break;
        }
    }
    return result;
}

//搜索是否存在某个元素,存在则返回第一个匹配的元素索引,不存在则返回-1
int FArray_Search(FArray a, void * toSearch)
{
    int i,j;
    int result = -1;
    for(i = 0;i<a.arraySize;i++)
    {
        if(CmpMemory(a.array+i*a.unitSize,toSearch,a.unitSize))
        {
            //相同数据段
            result = i;
            break;
        }

    }
    return result;
}

#endif // FLEXIBLEARRAY

