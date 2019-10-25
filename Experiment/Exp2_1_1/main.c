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
        //非整一百，直接验证
        result = (year % 4 == 0);
    }else
    {
        //整一百，验证整四百
        result = (year % 400 == 0);
    }
    printf("%s闰年",result?"是":"不是");
    return 0;
}
