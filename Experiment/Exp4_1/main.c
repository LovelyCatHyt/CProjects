#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 5
#define COLUMN 5
#define MAX 100

/*打印数组所有元素*/
void PrintArray(int a[],int len)
{
    int i;
    for(i = 0;i<len;i++)
        printf("%5d",a[i]);
}

int main()
{
    int a[ROW][COLUMN];
    int i,j;
    int temp;
    int maxr,maxc;

    /*随机生成一个数组*/
    srand((unsigned)time(NULL));
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COLUMN;j++)
        {
            a[i][j] = ((float)rand()/RAND_MAX)*100;
        }
    }

    /*打印数组*/
    printf("The array is:\n");
    for(i=0;i<ROW;i++)
    {
        PrintArray(a[i],COLUMN);
        putchar('\n');
    }

    printf("Now exchange the numbers in row 1 and row 5.\n");
    /*1行5行对调*/
    for(i=0;i<COLUMN;i++)
    {
        temp = a[0][i];
        a[0][i] = a[4][i];
        a[4][i] = temp;
    }

    /*打印数组*/
    printf("New array is:\n");
    for(i=0;i<ROW;i++)
    {
        PrintArray(a[i],COLUMN);
        putchar('\n');
    }

    /*找最大*/
    temp=a[0][0];
    maxr = maxc = 0;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COLUMN;j++)
        {
            if(temp<a[i][j])
            {
                temp = a[i][j];
                maxr = i;
                maxc = j;
            }
        }
        printf("In row %d,the largest number is %d on %d.\n",maxr,temp,maxc);
        if(i<ROW-1)
        {
            /*还不到最后一行,重置temp*/
            temp = a[i+1][0];
        }
    }
    return 0;
}
