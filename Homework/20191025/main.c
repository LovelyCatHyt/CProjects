#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Sort(int[],int);
void PrintArray(int[],int);
int main()
{
    int a[10];
    int i=0;
    int length = sizeof(a)/sizeof(int);
    /*获取十个随机数*/
    srand((unsigned)time(NULL));
    for(i = 0;i<10;i++)
        a[i]=rand();
    /*输出原数组*/
    printf("The array is :");
    PrintArray(a,length);
    putchar('\n');
    /*排序*/
    Sort(a,length);
    /*输出排序后数组*/
    printf("The sorted array is :");
    PrintArray(a,length);
    putchar('\n');
    return 0;
}

/*冒泡排序*/
void Sort(int a[],int len)
{
    int i,j,temp;
    for(j=1;j<len;j++)
    {
        for(i=0;i<len-j;i++)
        {
            if(a[i]>a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
        }
    }
}

/*打印数组所有元素*/
void PrintArray(int a[],int len)
{
    int i;
    for(i = 0;i<len;i++)
        printf("%6d",a[i]);
}
