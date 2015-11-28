#ifndef ETAGEHEXA_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "geometrie/vector3d.h"
#include "../interface_ville.h"
#include "batparameter.h"
#include "etagetwisted.h"
#define ETAGEHEXA_H


class EtageHexa : public Interface_Ville
{
public:
    EtageHexa(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, const Vector3D &p4, const Vector3D &p5, float hauteur, BatParameter *par, int noEtage, int type);
    Mesh generate();
private:
    Mesh ourMesh;
    Vector3D _p0,_p1,_p2,_p3,_p4,_p5;
    Vector3D _p0Top,_p1Top,_p2Top,_p3Top,_p4Top,_p5Top;
    float _hauteur; //hauteur du bloque
    BatParameter *_par;
    int _noEtage=0; //numéro de l'étage qui se construit
    float longueur,largeur;
    bool _splited;
    int _twisted; //0: non twisté   1: twisté vers la droite    2: twisté vers la gauche
    int _type;

    void twister(Mesh &m);
    void twistedEtage(void);
    void toit(void);
    void splitedEtage(void);
    void smallerEtage(void);
    void sameEtage(void);
    void createMesh(int type);
};

#endif // ETAGEHEXA_H
