#ifndef ETAGETWISTED_H
#define ETAGETWISTED_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "geometrie/vector3d.h"
#include "../interface_ville.h"
#include "batparameter.h"
#include "toit.h"

class EtageTwisted : public Interface_Ville
{
public:
    EtageTwisted(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par, int noEtage, int type);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3;
    Vector3D _p0Top,_p1Top,_p2Top,_p3Top;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    int _noEtage=0; //numéro de l'étage qui se construit
    float longueur,largeur;
    bool _splited;
    int _twisted; //0: non twisté   1: twisté vers la droite    2: twisté vers la gauche
    int _type;

    void twister(Mesh &m);
    void toit(void);
    void splitedEtage(void);
    void smallerEtage(void);
    void sameEtage(void);
    void createMesh(int type);
};

#endif // ETAGETWISTED_H
