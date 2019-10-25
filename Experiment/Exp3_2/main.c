#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void DrawLine(char *c,int num,char endc,int hasN)
{
    int i;
    for(i = 0;i<num;i++)
        printf(c);
    putchar(endc);
    if(hasN) putchar('\n');
    return 0;
}

int main()
{
    int i;
    time_t t;
    int password;
    int input;
    srand(time(&t));
    //TOFINISH
    //Get a password randomly
    password = (int)(((float)rand())*10/RAND_MAX) + 10;
    for(i=0;i<5;i++)
    {
        printf("Enter your password\(%d/5\):",i+1);
        scanf("%d",&input);
        if(input==password)
        {
            printf("Now you can enter the system.\n");
            break;
        }else
        {
            if(i<4)
            {
                system("cls");
                printf("Wrong password.Try again.\n");
            }
            else
            {
                system("cls");
                printf("Wrong password.You have lost your last chance.The password is %d.\n",password);
            }
        }
    }
    return 0;
}
