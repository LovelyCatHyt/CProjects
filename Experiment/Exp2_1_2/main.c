#include <stdio.h>
#include <math.h>

int main()
{
    double a,b,c;
    double delta,sqrDelta;
    double x1,x2;
    int valid = 1;
    int isClpx = 0;
    printf("������a,b,c����ϵ�����ÿո���з��ָ���");
    do
    {
        scanf("%lf%lf%lf",&a,&b,&c);
        if(a == 0)
        {
            valid = 0;
            printf("\na����Ϊ0�����������룡");
        }
    }while(!valid);
    delta = b * b - 4 * a * c;
    isClpx = delta < 0;
    sqrDelta = isClpx?sqrt(-delta):sqrt(delta);
    if(isClpx)
    {
        //���������
        /*DEBUG*/
        printf("sqrDelta = %lf",sqrDelta);
        printf("���Ϊ������\nx1 = %lf + %lfi\nx2 = %lf - %lfi\n",-b/(2*a),sqrDelta/(2*a),-b/(2*a),sqrDelta/(2*a));
    }else
    {
        printf("���Ϊʵ����");
        if(delta == 0) printf("����ͬʵ����x = %lf\n",-b/(2*a));
        else    printf("x1 = %lf,x2 = %lf",(-b + sqrDelta)/(2*a),(-b- sqrDelta)/(2*a));
    }

    return 0;
}
