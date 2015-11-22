#ifndef PATERNEQUADRESIDENCE_H
#define PATERNEQUADRESIDENCE_H

#include "modele/batiment/batiment.h"

class PaterneQuad : public Interface_Ville, public Quadrangle
{
public:

    PaterneQuad(){}
    PaterneQuad(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, BatParameter *par) :
            Quadrangle(p0,p1,p2,p3), _par(par){}

    BatParameter *_par;
    Mesh generate();

private:
    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);

    Mesh paternQuatreBatiment();
    Mesh paternTroisBatiment();
    Mesh paternDeuxBatimentDiagonale();
    Mesh paternDeuxBatimentDiametre();
    Mesh paternQuartierPlein();

    float coeffShrinkMax() const;
    float ratioDiametre() const;
};

#endif // PATERNEQUADRESIDENCE_H
