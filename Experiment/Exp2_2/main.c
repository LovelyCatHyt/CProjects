#include <stdio.h>
#include <stdlib.h>

int main()
{
    int score;
    int level;
    int valid = 1;
    printf("Enter your score£º");
    do
    {
        valid = 1;
        scanf("%d",&score);
        level = score/10;
        switch(level)
        {
        case 0:
            if(score<0)
            {
                printf("Wrong Score!Enter again!\n");
                valid = 0;
            break;
            }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Bad!\n");
            break;
        case 6:
            printf("Not bad!\n");
            break;
        case 7:
            printf("Good !\n");
            break;
        case 8:
            printf("Very good!\n");
            break;
        case 9:
            printf("Excellent!\n");
            break;
        default:
            if(score == 100) printf("Excellent!\n");
            else
            {
                printf("Wrong Score!Enter again!\n");
                valid = 0;
            }
        break;
        }
    }while(!valid);

}
