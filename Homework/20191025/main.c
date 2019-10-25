#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <dos.h>

/*打印数组所有元素*/
void PrintArray(int a[],int len)
{
    int i;
    for(i = 0;i<len;i++)
        printf("%6d",a[i]);
}
/*冒泡排序*/
void Sort(int a[],int len)
{
    int i,j,temp;
    system("cls");
    printf("The program is sorting the array …");
    for(j=1;j<len;j++)
    {
        for(i=0;i<len-j;i++)
        {
            if(a[i]>a[i+1])
            {
                /*刷新输出界面*/
                PrtSortingTip(a,len,i,i+1,j);
                Delay(250);
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                /*刷新输出界面*/
                PrtSortingTip(a,len,i+1,i,j);
                Delay(250);
            }
        }
    }
    printf("Sorting finished!");
    PrintArray(a,len);
}

/*打印出sorting的提示*/
void PrtSortingTip(int a[],int len,int hiLi1,int hiLi2,int round)
{
    SetPos(0,1);
    printf("Round ");
    SetColor(6,0);
    printf("%d:\n",round);
    SetColor(7,0);
    PrtAryHiLi(a,len,hiLi1,hiLi2);
}

/*打印数组,高亮显示指定元素*/
void PrtAryHiLi(int a[],int len,int hiLi1,int hiLi2)
{
    int i;
    for(i=0;i<len;i++)
    {
        if(i == hiLi1)
        {
            /*浅蓝色*/
            SetColor(9,0);
        }
        if(i == hiLi2)
        {
            /*浅绿色*/
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
    /*获取十个随机数*/
    srand((unsigned)time(NULL));
    for(i = 0;i<10;i++)
        a[i]=rand();
    /*输出原数组*/
    printf("The array is :");
    PrintArray(a,length);
    printf("\nPress any key to continue.");
    getch();
    Delay(2000);
    /*排序*/
    Sort(a,length);
    /*输出排序后数组*/
    system("cls");
    printf("The sorted array is :");
    PrintArray(a,length);
    putchar('\n');
    getch();
    return 0;
}
