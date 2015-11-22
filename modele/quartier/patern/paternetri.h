#ifndef PATERNETRI_H
#define PATERNETRI_H

#include "modele/batiment/batiment.h"
#include "geometrie/Triangle.h"

class PaterneTri: public Interface_Ville, public Triangle
{
public:
    PaterneTri(){}
    PaterneTri(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, BatParameter *par) :
            Triangle(p0,p1,p2), _par(par){}

    BatParameter *_par;
    Mesh generate();

private:
    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);
    Mesh paternConstruction() const;
    Mesh paternAngle(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2, float tv1, float tv2) const;
};

#endif // PATERNETRI_H
