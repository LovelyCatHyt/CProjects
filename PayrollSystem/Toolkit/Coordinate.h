#ifndef _COORDINATE_H
#include <windows.h>

COORD cdZero = {0,0};
COORD cdOne = {1,1};

COORD SHORT2COORD(SHORT x,SHORT y);
COORD Int2COORD(int x, int y);
COORD COORD_Add(COORD a, COORD b);
COORD COORD_Sub(COORD a, COORD b);
COORD COORD_Scale(COORD a, COORD b);

#define _COORDINATE_H
#endif // _COORDINATE_H
