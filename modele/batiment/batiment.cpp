#include "batiment.h"
#include "rezdechausse.h"

Batiment::Batiment(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par):_p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par)
{

}

Mesh Batiment::generate()
{
    Rezdechausse rdc(_p0,_p1,_p2,_p3,_hauteur,_par);
    return rdc.generate();
}

