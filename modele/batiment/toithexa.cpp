#include "toithexa.h"
#include <iostream>
#include <QDebug>
using namespace std;

ToitHexa::ToitHexa(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, const Vector3D &p4, const Vector3D &p5, int noEtage, float hauteur, BatParameter *par):
    _p0(p0),_p1(p1),_p2(p2),_p3(p3),_p4(p4),_p5(p5),_noEtage(noEtage),_hauteur(hauteur),_par(par)
{
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);
    createMesh(0);
}

Mesh ToitHexa::generate(){
    return ourMesh;
}


void ToitHexa::createMesh(int type){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3 +_p4 + _p5)/6;
    if(_noEtage>=6){
        //qDebug()<<"toto";
        float largeurBordure = 0.1;
        Vector3D p0bis = _p0 + (_p3-_p0)*largeurBordure;
        Vector3D p1bis = _p1 + (_p4-_p1)*largeurBordure;
        Vector3D p2bis = _p2 + (_p5-_p2)*largeurBordure;
        Vector3D p3bis = _p3 + (_p0-_p3)*largeurBordure;
        Vector3D p4bis = _p4 + (_p1-_p4)*largeurBordure;
        Vector3D p5bis = _p5 + (_p2-_p5)*largeurBordure;

        ourMesh = Mesh::createQuadrangle3D(_p0,_p1,p1bis,p0bis,_hauteur/3);
        ourMesh.merge(Mesh::createQuadrangle3D(_p5,_p0,p0bis,p5bis,_hauteur/3));
        if(!rand()%2){
            ourMesh.merge(Mesh::createQuadrangle3D(_p1,_p2,p2bis,p1bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3D(_p4,_p5,p5bis,p4bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3D(_p2,_p3,p3bis,p2bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3D(_p3,_p4,p4bis,p3bis,_hauteur/3));
        }else{
            Vector3D offset(0,0,_hauteur/1.0);
            Vector3D p32 = _p3;
            Vector3D p32bis = p3bis;
            p32 += offset;
            p32bis += offset;

            Vector3D p42 = _p4;
            Vector3D p42bis = p4bis;
            p42 += offset/2.0;
            p42bis += offset/2.0;

            Vector3D p22 = _p2;
            Vector3D p22bis = p2bis;
            p22 += offset/2.0;
            p22bis += offset/2.0;
            ourMesh.merge(Mesh::createQuadrangle3DTwisted(_p2,_p3,p3bis,p2bis,p22,p32,p32bis,p22bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3DTwisted(_p3,_p4,p4bis,p3bis,p32,p42,p42bis,p32bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3DTwisted(_p1,_p2,p2bis,p1bis,_p1,p22,p22bis,p1bis,_hauteur/3));
            ourMesh.merge(Mesh::createQuadrangle3DTwisted(_p4,_p5,p5bis,p4bis,p42,_p5,p5bis,p42bis,_hauteur/3));

            ourMesh.merge(Mesh::createHexaangleTwisted(p0bis,p1bis,p2bis,p3bis,p4bis,p5bis,
                                                       p0bis,p1bis,p22bis,p32bis,p42bis,p5bis,_hauteur/100.0));
        }


        Vector3D hauteurToit = (_p0 + _p1 + _p2 + _p3 +_p4 +_p5)/6;
        hauteurToit.z += _hauteur*6;
        _par->updateEtageLePlusHaut(hauteurToit);
        if(rand()%100 <10){
            float largeurantenne = 0.3;
            if(largeurantenne > longueur/3.0)largeurantenne=longueur/3.0;
            Mesh antenne = Mesh::createPyramidQuadrangle(Vector3D(-largeurantenne,-largeurantenne,0),Vector3D(-largeurantenne,largeurantenne,0),Vector3D(largeurantenne,largeurantenne,0),Vector3D(largeurantenne,-largeurantenne,0),_hauteur*5);
            antenne.translation(gravity.x,gravity.y,_p0.z);
            ourMesh.merge(antenne);
        }
    }else{
        _p0.z -= _hauteur*0.08;
        _p1.z -= _hauteur*0.08;
        _p2.z -= _hauteur*0.08;
        _p3.z -= _hauteur*0.08;
        ourMesh = Mesh::createHexaangle3D(_p0,_p1,_p2,_p3,_p4,_p5,_hauteur*0.7);
        Vector3D hauteurToit = (_p0 + _p1 + _p2 + _p3 + _p4 +_p5)/6;
        hauteurToit.z += _hauteur;
        _par->updateEtageLePlusHaut(hauteurToit);
    }
}
