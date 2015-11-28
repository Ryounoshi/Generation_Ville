#ifndef TOITHEXA_H
#define TOITHEXA_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "../interface_ville.h"
#include "batparameter.h"

class ToitHexa
{
public:
    ToitHexa(const Vector3D &p0, const Vector3D &p1, const Vector3D &p2, const Vector3D &p3, const Vector3D &p4, const Vector3D &p5, int noEtage, float hauteur, BatParameter *par);
    Mesh generate();
private:
    Mesh ourMesh;
    float longueur,largeur;
    Vector3D _p0,_p1,_p2,_p3,_p4,_p5;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    int _noEtage=0; //numéro de l'étage qui se construit
    void createMesh(int type);
};

#endif // TOITHEXA_H
