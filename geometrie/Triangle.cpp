#include "Triangle.h"


// Functions to access Vector2D class components
Vector2D& Triangle::operator[] (int i) {
	if (i == 0)		return p0;
	else if(i == 1)	return p1;
    else if(i == 2) return p2;
    else    {
        i %=3;
        if(i < 0)   i+=3;
        return (*this)[i];
    }
}

Vector2D Triangle::operator[] (int i) const {
	if (i == 0)		return p0;
    else if(i == 1)	return p1;
    else if(i == 2) return p2;
    else    {
        i %=3;
        if(i < 0)   i+=3;
        return (*this)[i];
    }
}

void Triangle::shrink(float l)
{
    shrinkPoly(3, l);
}

float Triangle::area() const
{
    return areaTriangle(p0,p1,p2);
}

float Triangle::perimetre() const
{
	return (distance(p0,p1) + distance(p1,p2) + distance(p2,p0));
}

int Triangle::nbPoints() const
{
    return 3;
}
