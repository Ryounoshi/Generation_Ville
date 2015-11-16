#ifndef TOIT_H
#define TOIT_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "../interface_ville.h"
#include "batparameter.h"

class Toit : public Interface_Ville
{
public:
    Toit(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
};

#endif // TOIT_H
