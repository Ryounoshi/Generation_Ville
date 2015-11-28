#include "rezdechaussehexa.h"
#include "toit.h"
#include <qdebug.h>
#include <iostream>
using namespace std;
#define scaletop 0.9
#define tailleRainure 0.01

RezdechausseHexa::RezdechausseHexa(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, const Vector3D& p4, const Vector3D& p5,float hauteur, BatParameter *par):_p0(p0),_p1(p1),_p2(p2),_p3(p3),_p4(p4),_p5(p5),_hauteur(hauteur),_par(par)
{
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);

    ourMesh = Mesh::createHexaangle3D(_p0,_p1,_p2,_p3,_p4,_p5,_hauteur*(1-tailleRainure));
    Mesh top = Mesh::createHexaangle3D(Vector3D(_p0.x,_p0.y,p0.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p1.x,_p1.y,p1.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p2.x,_p2.y,p2.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p3.x,_p3.y,p3.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p4.x,_p4.y,p4.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p5.x,_p5.y,p5.z+_hauteur*(1-tailleRainure)),
                                        _hauteur*tailleRainure);
    top.localrescaleXY(scaletop);
    ourMesh.merge(top);

}

Mesh RezdechausseHexa::generate(){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3 +_p4 + _p5)/6;
    float dist = std::sqrt((gravity.x-_par->_centreVille.x)*(gravity.x-_par->_centreVille.x)+(gravity.y-_par->_centreVille.y)*(gravity.y-_par->_centreVille.y));
    Vector3D offset(0,0,_hauteur);
    int proba = rand()%100;
    if(proba < (95) && dist < (200*_par->influenceCentreVille)){
        EtageHexa etage(_p0+offset,_p1+offset,_p2+offset,_p3+offset,_p4+offset,_p5+offset,_hauteur, _par,1,E);
        ourMesh.merge(etage.generate());
        return ourMesh;
    }else{
        Toit toit(_p0+offset,_p1+offset,_p2+offset,_p3+offset, 0,_hauteur, _par);
        ourMesh.merge(toit.generate());
        return ourMesh;
    }
}
