#ifndef REZDECHAUSSEHEXA_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "import_export/objmanager.h"
#include "etagehexa.h"
#include "../interface_ville.h"
#include "batparameter.h"
#define REZDECHAUSSEHEXA_H


class RezdechausseHexa
{
public:
    RezdechausseHexa(const Vector3D &p0, const Vector3D &p1, const Vector3D &p2, const Vector3D &p3, const Vector3D &p4, const Vector3D &p5, float hauteur, BatParameter *par);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3,_p4,_p5;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    float longueur,largeur;

};

#endif // REZDECHAUSSEHEXA_H
