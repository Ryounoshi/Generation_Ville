#ifndef REZDECHAUSSE_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "import_export/objmanager.h"
#include "etage.h"
#include "../interface_ville.h"
#include "batparameter.h"
#define REZDECHAUSSE_H


class Rezdechausse : public Interface_Ville
{
public:
    Rezdechausse(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    float longueur,largeur;
};

#endif // REZDECHAUSSE_H
