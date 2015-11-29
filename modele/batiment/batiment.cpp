#include "batiment.h"
#include "rezdechausse.h"
#include "rezdechaussehexa.h"
#include <QDebug>

Batiment::Batiment(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hexaPourcent,BatParameter *par):
    _p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(par->hauteurEtage),_hexaPourcent(hexaPourcent),_par(par)
{
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);

    longueur *= 1;
    largeur *= 1;
}

Mesh Batiment::generate()
{
    if(orientation(Vector2D(XY(_p0)),Vector2D(XY(_p1)),Vector2D(XY(_p2))) > 0)
        return Mesh();
    //if(true){
    //if(longueur <= largeur*2 && largeur <= longueur*2 && (rand()%100 < _hexaPourcent)){
    if((rand()%100 < _hexaPourcent)){
        Vector3D dirlongueur = (_p1-_p0).normalized();
        Vector3D dirlargeur = (_p3-_p0).normalized();
        Vector3D gravity = (_p0 + _p1 + _p2 + _p3)/4;
        Vector3D hp0 = longueur*dirlongueur/2.0;
        Vector3D hp1 = longueur*dirlongueur/(5.0+(rand()%200)/100.0) - largeur*dirlargeur/2.0;
        Vector3D hp2 = -longueur*dirlongueur/(5.0+(rand()%200)/100.0) - largeur*dirlargeur/2.0;
        Vector3D hp3 = -longueur*dirlongueur/2.0;
        Vector3D hp4 = -longueur*dirlongueur/(5.0+(rand()%200)/100.0) + largeur*dirlargeur/2.0;
        Vector3D hp5 = longueur*dirlongueur/(5.0+(rand()%200)/100.0) + largeur*dirlargeur/2.0;

        hp0 += gravity;
        hp1 += gravity;
        hp2 += gravity;
        hp3 += gravity;
        hp4 += gravity;
        hp5 += gravity;

        RezdechausseHexa rdc(hp0,hp1,hp2,hp3,hp4,hp5,_hauteur,_par);
        ourMesh.merge(rdc.generate());
        return ourMesh;
    }else{
        Rezdechausse rdc(_p0,_p1,_p2,_p3,_hauteur,_par);
        ourMesh.merge(rdc.generate());
        return ourMesh;
    }
}

