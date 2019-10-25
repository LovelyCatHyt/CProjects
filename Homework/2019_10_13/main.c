#include <stdio.h>

int main()
{
	int num,a,b,c,temp,count = 0;
	float min = 100,max = 300;
	int i_min,i_max;
	printf("Please enter two number to set searching range.\n");
	scanf("%f %f",&min,&max);
	while(min<100 || min>999 || max<100 || max>999)
    {
        printf("Data invalid.Try again:");
        scanf("%f %f",&min,&max);
    }
    //直接赋值
    i_min = min;i_max = max;
    //提示可能会有类型转换
    printf("Mind that if you enter a float number, the program will transfer it into integer.\n");
    if(i_min>i_max)
    {
        //用位异或操作排个序
        i_min = i_min ^ i_max;
        i_max = i_min ^ i_max;
        i_min = i_min ^ i_max;
    }
	for (num = i_min;num < i_max; num++)
	{
		temp = num;
		//一边求最低位，一边右移一位。
		temp = (temp - (a = num % 10))/10;
		temp = (temp - (b = temp % 10))/10;
		c = temp % 10;
		//Debug
		//printf("a = %d;b = %d;c= %d.\n",a,b,c);
		//回来求个位数与百位数对调的数
		temp = a * 100 + b * 10 + c;
		if (temp > 2 * num && temp < 3 * num)
        {
            printf("%4d", num);
            count++;
            if(count%10 == 0) printf("\n");
        }
	}
	printf("\nThere are %d numbers found.\n",count);
	system("Pause");
	return 0;
}
