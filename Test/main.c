#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    printf("Please enter two numbers,separated by \',\'.\n");
    scanf("%d,%d",&a,&b);
    printf("You enter: a = %d, b = %d.\n",a,b);
    printf("There sum is %d.\n",a+b);
    printf("Test successfully.\n");
    return 0;
}
