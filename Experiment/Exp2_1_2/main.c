#include <stdio.h>
#include <math.h>

int main()
{
    double a,b,c;
    double delta,sqrDelta;
    double x1,x2;
    int valid = 1;
    int isClpx = 0;
    printf("请输入a,b,c三个系数，用空格或换行符分隔：");
    do
    {
        scanf("%lf%lf%lf",&a,&b,&c);
        if(a == 0)
        {
            valid = 0;
            printf("\na不能为0！请重新输入！");
        }
    }while(!valid);
    delta = b * b - 4 * a * c;
    isClpx = delta < 0;
    sqrDelta = isClpx?sqrt(-delta):sqrt(delta);
    if(isClpx)
    {
        //是虚数结果
        /*DEBUG*/
        printf("sqrDelta = %lf",sqrDelta);
        printf("结果为虚数！\nx1 = %lf + %lfi\nx2 = %lf - %lfi\n",-b/(2*a),sqrDelta/(2*a),-b/(2*a),sqrDelta/(2*a));
    }else
    {
        printf("结果为实数！");
        if(delta == 0) printf("有相同实根：x = %lf\n",-b/(2*a));
        else    printf("x1 = %lf,x2 = %lf",(-b + sqrDelta)/(2*a),(-b- sqrDelta)/(2*a));
    }

    return 0;
}
