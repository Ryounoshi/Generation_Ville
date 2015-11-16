#ifndef ETAGE_H
#define ETAGE_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "geometrie/vector3d.h"
#include "../interface_ville.h"
#include "batparameter.h"

class Etage : public Interface_Ville
{
public:
    Etage(Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, float hauteur, BatParameter *par, int noEtage, bool splited);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3;
    float _hauteur; //hauteur du bloque
    int _noEtage=0; //numéro de l'étage qui se construit
    BatParameter *_par;
    float longueur,largeur;
    bool _splited;
};

#endif // ETAGE_H
