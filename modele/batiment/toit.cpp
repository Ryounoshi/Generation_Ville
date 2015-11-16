#include "toit.h"
#include <iostream>
using namespace std;

Toit::Toit(Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, float hauteur, BatParameter *par):_p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par)
{
    //cout << " T" << endl<< endl << endl;
    _p0.z -= _hauteur*0.08;
    _p1.z -= _hauteur*0.08;
    _p2.z -= _hauteur*0.08;
    _p3.z -= _hauteur*0.08;
    ourMesh = Mesh::createPyramidQuadrangle(_p0,_p1,_p2,_p3,_hauteur*0.7);
    Vector3D hauteurToit = (_p0 + _p1 + _p2 + _p3)/4;
    hauteurToit.z += _hauteur;
    _par->updateEtageLePlusHaut(hauteurToit);
}
Mesh Toit::generate(){
    return ourMesh;
}
