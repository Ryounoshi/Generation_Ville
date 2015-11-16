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
    Etage(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par, int noEtage, bool splited, int twisted);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    int _noEtage=0; //numéro de l'étage qui se construit
    float longueur,largeur;
    bool _splited;
    int _twisted; //0: non twisté   1: twisté vers la droite    2: twisté vers la gauche

    void twister(Mesh &m);
};

#endif // ETAGE_H
