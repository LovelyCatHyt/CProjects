#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SmartIntArray
{
    int *array;
    int len;
};

/*"SIA" is "SmartIntArray"*/
/*Initialize*/
int SIAInit(struct SmartIntArray *a,int size)
{
    if(size >= 0)
    {
        a->len = size;
        a->array = (int*)calloc(size,sizeof(int));
        return 1;
    }
    else
    {
        return 0;
    }
}

/*Free the memory used by a->array*/
int SIAFree(struct SmartIntArray *a)
{
    free(a->array);
    return 1;
}

/*Resize the array*/
int SIAResize(struct SmartIntArray *a, int newSize)
{
    if(newSize >= 0)
    {
        a->array = (int *)realloc(a->array,newSize*sizeof(int));
        a->len = newSize;
        return 1;
    }
    return 0;
}

/*Add a number at the end of the array*/
int SIAAddToEnd(struct SmartIntArray *a,int num)
{
    if(SIAResize(a,a->len+1))
    {
        a->array[a->len-1] = num;
        return 1;
    }
    return 0;
}

int main()
{
    struct SmartIntArray test;
    SIAFree(&test);
    return 0;
}
