#include "quadrangle.h"


Vector2D& Quadrangle::operator[] (int i) {
    if (i == 0)     return p0;
    else if(i == 1) return p1;
    else if(i == 2) return p2;
    else if(i == 3) return p3;
    else    {
        i %=4;
        if(i < 0)   i+=4;
        return (*this)[i];
    }
}

Vector2D Quadrangle::operator[] (int i) const {
    if (i == 0)     return p0;
    else if(i == 1) return p1;
    else if(i == 2) return p2;
    else if(i == 3) return p3;
    else    {
        i %=4;
        if(i < 0)   i+=4;
        return (*this)[i];
    }
}

/**
 * A=1/2*d1*d2*sin(alpha)
 *
 * http://onlinemschool.com/math/formula/area/#h5
 *
 */
float Quadrangle::area() const
{
    return areaQuad(p0,p1,p2,p3);
}

float Quadrangle::perimetre() const
{
    return distance(p0,p1)+distance(p1,p2)+distance(p2,p3)+distance(p3,p0);
}

void Quadrangle::shrink(float l)
{
    shrinkPoly(4, l);   
}

int Quadrangle::nbPoints() const
{
    return 4;
}
