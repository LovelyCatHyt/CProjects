#include <stdio.h>
#include <stdlib.h>

int main()
{
    int result[100];
    int queryNum;
    int elementNum;
    int flag;
    int temp;
    int sum=0;
    int i,j;
    scanf("%d",&queryNum);
    for(i = 0;i<queryNum;i++)
    {
        /*遍历每一个query*/
        scanf("%d",&elementNum);
        for(j = 0;j<elementNum;j++)
        {
            /*存入一个数字*/
            scanf("%d",&temp);
            sum +=temp;
            if(sum & (1<<11))
            {
                flag = 1;
            }
        }
        result[i] = flag;
        sum = 0;
        flag = 0;
    }

    /*输出结果*/
    for(i = 0;i<queryNum;i++)
    {
        printf(result[i]?"YES\n":"NO\n");
    }
    return 0;
}
