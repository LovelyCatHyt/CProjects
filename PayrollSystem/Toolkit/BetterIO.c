#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "BetterIO.h"


void Delay(float delay)
{
    clock_t start = clock();
    while((float)(clock() - start) / CLK_TCK<delay);
}

//清除无用输入,通常用于清除scanf后的回车
void ClearUselessInput()
{
    char c = 0;
    do
    {
        c = getch();
    }while(c != 13);
}
