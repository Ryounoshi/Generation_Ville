#include "toit.h"
#include <iostream>
using namespace std;

Toit::Toit(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, int noEtage, float hauteur, BatParameter *par):
        _p0(p0),_p1(p1),_p2(p2),_p3(p3),_noEtage(noEtage),_hauteur(hauteur),_par(par)
{
    //cout << " T" << endl<< endl << endl;
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);
    createMesh(0);

}
Mesh Toit::generate(){
    return ourMesh;
}

void Toit::createMesh(int type){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3)/4;
    if(_noEtage>=6){
        float largeurBordure = 0.1;

        Vector3D p0bis = _p0 + (_p2-_p0)*largeurBordure;
        Vector3D p1bis = _p1 + (_p3-_p1)*largeurBordure;
        Vector3D p2bis = _p2 + (_p0-_p2)*largeurBordure;
        Vector3D p3bis = _p3 + (_p1-_p3)*largeurBordure;

        ourMesh = Mesh::createQuadrangle3D(_p0,_p1,p1bis,p0bis,_hauteur/3);
        ourMesh.merge(Mesh::createQuadrangle3D(_p1,_p2,p2bis,p1bis,_hauteur/3));
        ourMesh.merge(Mesh::createQuadrangle3D(_p2,_p3,p3bis,p2bis,_hauteur/3));
        ourMesh.merge(Mesh::createQuadrangle3D(_p3,_p0,p0bis,p3bis,_hauteur/3));

        Vector3D hauteurToit = (_p0 + _p1 + _p2 + _p3)/4;
        hauteurToit.z += _hauteur*6;
        _par->updateEtageLePlusHaut(hauteurToit);
        if(rand()%100 <10){
            Mesh antenne = Mesh::createPyramidQuadrangle(Vector3D(-0.3,-0.3,0),Vector3D(-0.3,0.3,0),Vector3D(0.3,0.3,0),Vector3D(0.3,-0.3,0),_hauteur*5);
            antenne.translation(gravity.x,gravity.y,_p0.z);
            ourMesh.merge(antenne);
        }
    }else{
        _p0.z -= _hauteur*0.08;
        _p1.z -= _hauteur*0.08;
        _p2.z -= _hauteur*0.08;
        _p3.z -= _hauteur*0.08;
        ourMesh = Mesh::createPyramidQuadrangle(_p0,_p1,_p2,_p3,_hauteur*0.7);
        Vector3D hauteurToit = (_p0 + _p1 + _p2 + _p3)/4;
        hauteurToit.z += _hauteur;
        _par->updateEtageLePlusHaut(hauteurToit);
    }
}
