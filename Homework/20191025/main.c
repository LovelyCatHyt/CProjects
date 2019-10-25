#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <dos.h>

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
    system("cls");
    printf("The program is sorting the array ��");
    for(j=1;j<len;j++)
    {
        for(i=0;i<len-j;i++)
        {
            if(a[i]>a[i+1])
            {
                /*ˢ���������*/
                PrtSortingTip(a,len,i,i+1,j);
                Delay(250);
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                /*ˢ���������*/
                PrtSortingTip(a,len,i+1,i,j);
                Delay(250);
            }
        }
    }
    printf("Sorting finished!");
    PrintArray(a,len);
}

/*��ӡ��sorting����ʾ*/
void PrtSortingTip(int a[],int len,int hiLi1,int hiLi2,int round)
{
    SetPos(0,1);
    printf("Round ");
    SetColor(6,0);
    printf("%d:\n",round);
    SetColor(7,0);
    PrtAryHiLi(a,len,hiLi1,hiLi2);
}

/*��ӡ����,������ʾָ��Ԫ��*/
void PrtAryHiLi(int a[],int len,int hiLi1,int hiLi2)
{
    int i;
    for(i=0;i<len;i++)
    {
        if(i == hiLi1)
        {
            /*ǳ��ɫ*/
            SetColor(9,0);
        }
        if(i == hiLi2)
        {
            /*ǳ��ɫ*/
            SetColor(10,0);
        }
        printf("%-6d",a[i]);
        SetColor(7,0);
    }
    putchar('\n');
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
    printf("\nPress any key to continue.");
    getch();
    Delay(2000);
    /*����*/
    Sort(a,length);
    /*������������*/
    system("cls");
    printf("The sorted array is :");
    PrintArray(a,length);
    putchar('\n');
    getch();
    return 0;
}
