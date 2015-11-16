#ifndef PATERNEQUADRESIDENCE_H
#define PATERNEQUADRESIDENCE_H

#include "../quarquad.h"
#include "modele/batiment/batiment.h"
#include "modele/batiment/bat_parameter.h"

class PaterneQuadResidence : public QuarQuad
{
public:
    float largeurBatiment;
    float largeurRoute;
    PaterneQuadResidence(){}
    PaterneQuadResidence(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const float& _largeurBatiment, BatParameter *par) :
            QuarQuad(p0,p1,p2,p3), largeurBatiment(_largeurBatiment), largeurRoute(0), _par(par){}
    BatParameter *_par;
    Mesh generate();
};

#endif // PATERNEQUADRESIDENCE_H
