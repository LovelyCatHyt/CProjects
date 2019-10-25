#include <stdio.h>
#include <time.h>
void PrintResult(long,float);
int main()
{
    int big = 0,mid = 0,sml = 0;
    const int total = 729;
    long count = 0;
    clock_t start;
    start = clock();
    printf("Trying to figure out the problem.The total is \[%d\].\n",total);
    /*1.
    //printf("Available sollutions:\n   Big|Middium| Small|   Big|Middium| Small|   Big|Middium| Small|   Big|Middium| Small|\n");
    while(big < total)
    {
        big++;
        while(mid < total)
        {
            mid++;
            while(sml < total)
            {
                sml++;
                if((big*3 + mid*2 + sml*0.5 == total) && (big + mid + sml == total))
                {
                    //printf("%6d %6d %6d |",big,mid,sml);
                    count++;
                    //if(count%4==0) printf("\n");
                }
            };
            sml = 1;
        };
        mid = 1;
    };
    printf("Case 1,method 1:\n");
    PrintResult(count,(float)(clock() - start)/CLOCKS_PER_SEC);
    count = 0;
    start = clock();
    */
    /*2.
    big = mid = sml = 1;
    do
    {
        mid = 1;
        do
        {
            sml = (total - (big*3 + mid*2)) * 2;
            if(big + mid + sml == total)
            {
                //printf("%6d %6d %6d\n",big,mid,sml);
                count++;
            }
            mid++;
        }while(big + mid < total);
        big++;
    }while(big < total);
    printf("Case 1,method 2:\n");
    PrintResult(count,(float)(clock() - start)/CLOCKS_PER_SEC);
    count = 0;
    start = clock();
    */
    /*3
    for(big = 0;big <= total;big++)
    {
        for(mid = 0;mid <= total;mid++)
        {
            for(sml = 0;sml <= total;sml+=2)
            {
                if(3 * big + 2 * mid + 0.5 * sml == total && big + mid + sml ==  total)
                {
                    //printf("%6d %6d %6d|\n",big,mid,sml);
                    count++;
                }
            }
        }
    }
    printf("Case 2,method 1:\n");
    PrintResult(count,(float)(clock() - start)/CLOCKS_PER_SEC);
    count = 0;
    start = clock();
    */
    /*4:It may be the fastest method.*/
    for(big=0;big<=total;big++)
    {
        //big + mid + sml = total;mid + sml = total - big;mid = total - big - sml;
        //big*3 + mid*2 + sml*0.5 = total;sml=2total-big*6-(total - big - sml)*4;
        //6big+4total-4big-2total=4sml-sml;
        //3sml=2total+2big;sml = (total+big)*2/3;
        //mid=total - big - sml;
        sml = (total+big)*2/3;
        mid = total - big - sml;
        if((big + mid + sml ==  total) && (big*3 + mid*2 + sml*0.5 == total) && (mid>=0) && (sml>=0))
        {
            //printf("%6d %6d %6d|\n",big,mid,sml);
            count++;
        }
    }
    printf("Case 2,method 2:\n");
    PrintResult(count,(float)(clock() - start)/CLOCKS_PER_SEC);
    return 0;
}

void PrintResult(long count,float usedTime)
{
    printf("Totally \[%-5ld\] sollutions.",count);
    printf("The time used is about %1.8fs.\n",usedTime);
}
