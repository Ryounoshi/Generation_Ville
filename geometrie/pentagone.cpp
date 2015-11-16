#include "pentagone.h"

// Functions to access Vector2D class components
Vector2D& Pentagone::operator[] (int i) {
    if (i == 0)		return p0;
    else if(i == 1)	return p1;
    else if(i == 2) return p2;
    else if(i == 3) return p3;
    else if(i == 4) return p4;
    else    {
        i %=5;
        if(i < 0)   i+=5;
        return (*this)[i];
    }
}

Vector2D Pentagone::operator[] (int i) const {
    if (i == 0)		return p0;
    else if(i == 1)	return p1;
    else if(i == 2) return p2;
    else if(i == 3)	return p3;
    else if(i == 4) return p4;
    else    {
        i %=5;
        if(i < 0)   i+=5;
        return (*this)[i];
    }
}

void Pentagone::shrink(float l)
{
    shrinkPoly(5, l);
}


float Pentagone::area() const
{
    return areaQuad(p0,p1,p2,p3) + areaTriangle(p3,p4,p0);
}

float Pentagone::perimetre() const
{
    return distance(p0,p1)+distance(p1,p2)+distance(p2,p3)+distance(p3,p4)+distance(p4,p0);
}

int Pentagone::nbPoints() const
{
    return 5;
}
