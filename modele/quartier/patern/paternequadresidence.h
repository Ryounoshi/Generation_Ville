#ifndef PATERNEQUADRESIDENCE_H
#define PATERNEQUADRESIDENCE_H

#include "../quarquad.h"
#include "modele/batiment/batiment.h"

class PaterneQuadResidence : public QuarQuad
{
public:

    PaterneQuadResidence(){}
    PaterneQuadResidence(const QuarQuad& parent, BatParameter *par) :
            QuarQuad(parent), _par(par){}
    PaterneQuadResidence(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, BatParameter *par) :
            QuarQuad(p0,p1,p2,p3, par), _par(par){}

    BatParameter *_par;
    Mesh generate();

private:
    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);

    Mesh paternQuatreBatiment();
    Mesh paternTroisBatiment();
    Mesh paternDeuxBatimentDiagonale();
    Mesh paternDeuxBatimentDiametre();
};

#endif // PATERNEQUADRESIDENCE_H
