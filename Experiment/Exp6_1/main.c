#include <stdio.h>
#include <stdlib.h>

/*交换两个int(finished)*/
void Swap(int *a,int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

/*最大公约数*/
int f(int a,int b)
{
    int num;
    /*先处理参数,使a>b*/
    if(a<b) Swap(&a,&b);
    for(num = b;num>=1;num--)
    {
        if(!(a%num) && !(b%num)) break;
    }
    return num;
}

/*最小公倍数*/
int g(int a, int b)
{
    return a/f(a,b)*b;
}

/*循环输入整数,直到输入的是正整数*/
int InNumber()
{
    int a;
    do
    {
        printf("Please input a positive integer:");
        scanf("%d",&a);
    }while(a<=0);
    return a;
}

int main()
{
    int a,b;
    int c,d;
    a = InNumber();
    printf("a = %d\n",a);
    b = InNumber();
    printf("b = %d\n",b);
    c = f(a,b);
    d = g(a,b);
    printf("c = %d, d = %d.\n",c,d);
    return 0;
}
