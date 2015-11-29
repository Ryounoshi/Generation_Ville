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

    float _profondeurBatiment;

    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);

    /*
    Mesh paternQuatreBatiment();
    Mesh paternTroisBatiment();
    Mesh paternDeuxBatimentDiagonale();
    Mesh paternDeuxBatimentDiametre();
    */

    void determinationBatimentCoin(const int &indicePointCoin, Vector2D &point1Batiment, Vector2D &pointCentre, Vector2D &point3Batiment);
    Mesh remplissageCoin(const int &indicePointCoin, Vector2D &point1Batiment, Vector2D &pointCentre, Vector2D &point3Batiment);
    Mesh remplissageBord(Vector2D &point1Batiment0, Vector2D &point2Batiment0,
                         Vector2D &point2Batiment1, Vector2D &point3Batiment1);

    float coeffShrinkMax() const;
    float ratioDiametre() const;

    float angleEntreVecteur(const Vector2D& v1, const Vector2D& v2) const;
};

#endif // PATERNEQUADRESIDENCE_H
