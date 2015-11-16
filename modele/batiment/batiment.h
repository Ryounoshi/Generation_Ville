#ifndef BATIMENT_H
#define BATIMENT_H

#include "../interface_ville.h"
#include "batparameter.h"

class Batiment : public Interface_Ville
{
public:
    Batiment(Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, float hauteur, BatParameter *par);
    Mesh generate();
private:
    Vector3D _p0,_p1,_p2,_p3;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
};

#endif // BATIMENT_H