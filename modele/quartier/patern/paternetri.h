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

    Mesh paternAngleTotal(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const;
    Mesh paternAngleCarre(int i, const Vector2D& v1, const Vector2D& v2) const;
    Mesh paternAngleCarre2(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const;

    Mesh paternRebordAngle(int i, const Vector2D& v1, const Vector2D& v2, Vector2D& p2, Vector2D& p3, Vector2D& p4) const;
    Mesh paternRebord(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4, const Vector2D& v1) const;
};

#endif // PATERNETRI_H
