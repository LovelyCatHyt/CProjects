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
        /*����ÿһ��query*/
        scanf("%d",&elementNum);
        for(j = 0;j<elementNum;j++)
        {
            /*����һ������*/
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

    /*������*/
    for(i = 0;i<queryNum;i++)
    {
        printf(result[i]?"YES\n":"NO\n");
    }
    return 0;
}
