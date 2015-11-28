#ifndef ETAGESPLITED_H
#define ETAGESPLITED_H
#include "modele/mesh.h"
#include "geometrie/vector2d.h"
#include "geometrie/vector3d.h"
#include "../interface_ville.h"
#include "batparameter.h"

class EtageSplited : public Interface_Ville
{
public:
    EtageSplited(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par, int noEtage, int type);
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
    int _type;

    void twister(Mesh &m);
    void toit(void);
    void splitedEtage(void);
    void smallerEtage(void);
    void sameEtage(void);
    void createMesh(Vector3D p0,Vector3D p1,Vector3D p2,Vector3D p3,float hauteur);
};

#endif // ETAGESPLITED_H
