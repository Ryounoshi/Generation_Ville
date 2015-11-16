#ifndef PATERNEQUADRESIDENCE_H
#define PATERNEQUADRESIDENCE_H

#include "../quarquad.h"
#include "modele/batiment/batiment.h"

class PaterneQuadResidence : public QuarQuad
{
public:
    float largeurBatiment;
    float largeurRoute;
    float largeurTrotoir;

    PaterneQuadResidence(){}
    PaterneQuadResidence(const QuarQuad& parent, const float& _largeurBatiment, BatParameter *par) :
            QuarQuad(parent), largeurBatiment(_largeurBatiment), largeurRoute(0), _par(par){}
    PaterneQuadResidence(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const float& _largeurBatiment, BatParameter *par) :
            QuarQuad(p0,p1,p2,p3), largeurBatiment(_largeurBatiment), largeurRoute(0), _par(par){}

    BatParameter *_par;
    Mesh generate();

private:
    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);
};

#endif // PATERNEQUADRESIDENCE_H
