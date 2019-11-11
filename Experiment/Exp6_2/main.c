#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char HexLookUpTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*Dec->Hex*/
void trans10to16(int bit,int num,char *current)
{
    *(current + bit - 1) = HexLookUpTable[num%16];
    if(bit>1)
    {
        trans10to16(bit-1,num>>4,current);
    }
}

void SetRandomArray(int *a,int len)
{
    int i;
    srand((unsigned)time(NULL));
    for(i=0;i<len;i++)
    {
        a[i]=rand()%65535;
    }
}

int main()
{
    int num[5];
    int i;
    char hexResult[5] = {0,0,0,0,0};
    SetRandomArray(num,5);
    for(i=0;i<5;i++)
    {
        trans10to16(4,num[i],hexResult);
        printf("Random number\[%d\] = %d, Result = %s\n",i,num[i],hexResult);
    }
    return 0;
}
