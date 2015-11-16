#ifndef POLYGONE_H
#define POLYGONE_H

#include "vector2d.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <cstdlib>      //RAND_MAX

class Polygone
{
public:
    Polygone();


    virtual Vector2D& operator[] (int i) = 0;
    virtual Vector2D operator[] (int i) const = 0;

    Vector2D& get(int i);
    Vector2D get(int i) const;
    void set(int i, const Vector2D& p);

    virtual void shrink(float l) = 0;
    virtual float area() const = 0;
    virtual float perimetre() const = 0;

    virtual int nbPoints() const = 0;



protected:
    void shrinkPoly(int nb, float l);
};

float areaTriangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2);
float areaQuad(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3);


#endif // POLYGONE_H
