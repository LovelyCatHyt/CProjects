#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/*��ӡ��������Ԫ��*/
void PrintArray(int a[],int len)
{
    int i;
    for(i = 0;i<len;i++)
        printf("%6d",a[i]);
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

/*��ӡ����,������ʾָ��Ԫ��*/
void PrtAryHiLi(int a[],int len,int hiLi1,int hiLi2)
{
    int i;
    for(i=0;i<len;i++)
    {
        if(i == hiLi1 || i == hiLi2)
        {
            //textbackground();
        }
    }
}

void setColor(unsigned short ForeColor,unsigned short BackGroundColor)
{
/*
��Ӧ����ɫ���
0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       10 = ����ɫ
3 = ǳ��ɫ     11 = ��ǳ��ɫ
4 = ��ɫ       12 = ����ɫ
5 = ��ɫ       13 = ����ɫ
6 = ��ɫ       14 = ����ɫ
7 = ��ɫ       15 = ����ɫ
*/
HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);/*��ȡ��ǰ���ھ��*/
SetConsoleTextAttribute(handle,ForeColor+BackGroundColor<<4);/*������ɫ*/
}

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
