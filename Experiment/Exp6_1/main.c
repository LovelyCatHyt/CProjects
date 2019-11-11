#include <stdio.h>
#include <stdlib.h>

/*��������int(finished)*/
void Swap(int *a,int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

/*���Լ��*/
int f(int a,int b)
{
    int num;
    /*�ȴ������,ʹa>b*/
    if(a<b) Swap(&a,&b);
    for(num = b;num>=1;num--)
    {
        if(!(a%num) && !(b%num)) break;
    }
    return num;
}

/*��С������*/
int g(int a, int b)
{
    return a/f(a,b)*b;
}

/*ѭ����������,ֱ���������������*/
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
