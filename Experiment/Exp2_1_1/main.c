#include <stdio.h>
#include <stdlib.h>

int main()
{
    int year = 2019;
    int result = 0;
    printf("Please enter a year:");
    scanf("%d",&year);
    if(year%100 != 0)
    {
        //����һ�٣�ֱ����֤
        result = (year % 4 == 0);
    }else
    {
        //��һ�٣���֤���İ�
        result = (year % 400 == 0);
    }
    printf("%s����",result?"��":"����");
    return 0;
}
