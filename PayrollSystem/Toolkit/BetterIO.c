#include <time.h>
#include "BetterIO.h"

void Delay(float delay)
{
    clock_t start = clock();
    while((float)(clock() - start) / CLK_TCK<delay);
}

