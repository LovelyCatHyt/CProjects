#include "Coordinate.h"

//从两个SHORT类型获取COORD
COORD SHORT2COORD(SHORT x,SHORT y)
{
    COORD result = {x,y};
    return result;
}

//从两个Int类型获取COORD
COORD Int2COORD(int x, int y)
{
    COORD result = {(SHORT)x, (SHORT)y};
    return result;
}

//把COORD看做向量的加法
COORD COORD_Add(COORD a, COORD b)
{
    return SHORT2COORD(a.X + b.X, a.Y + b.Y);
}

//把COORD看做向量的减法
COORD COORD_Sub(COORD a, COORD b)
{
    return SHORT2COORD(a.X - b.X, a.Y - b.Y);
}

//返回值两个分量分别是两个参数分量的代数积
COORD COORD_Scale(COORD a, COORD b)
{
    return SHORT2COORD(a.X * b.X, a.Y * b.Y);
}

//返回a和num的乘积,结果是COORD
COORD COORD_MultBySHORT(COORD a, SHORT num)
{
    return SHORT2COORD(a.X * num, a.Y * num);
}