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
    /*��ȡʮ�������*/
    srand((unsigned)time(NULL));
    for(i = 0;i<10;i++)
        a[i]=rand();
    /*���ԭ����*/
    printf("The array is :");
    PrintArray(a,length);
    putchar('\n');
    /*����*/
    Sort(a,length);
    /*������������*/
    printf("The sorted array is :");
    PrintArray(a,length);
    putchar('\n');
    return 0;
}

/*ð������*/
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

/*��ӡ��������Ԫ��*/
void PrintArray(int a[],int len)
{
    int i;
    for(i = 0;i<len;i++)
        printf("%6d",a[i]);
}
