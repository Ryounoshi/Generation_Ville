#include "rezdechausse.h"
#include "toit.h"
#include <qdebug.h>
#include <iostream>
using namespace std;
#define scaletop 0.9
#define tailleRainure 0.01

Rezdechausse::Rezdechausse(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par):_p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par)
{
    longueur = distance(p0, p1);
    largeur = distance(p0, p3);
    //cout << " R" << endl;
    ourMesh = Mesh::createQuadrangle3D(_p0,_p1,_p2,_p3,_hauteur*(1-tailleRainure));
    Mesh top = Mesh::createQuadrangle3D(Vector3D(_p0.x,_p0.y,p0.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p1.x,_p1.y,p1.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p2.x,_p2.y,p2.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p3.x,_p3.y,p3.z+_hauteur*(1-tailleRainure)),
                                        _hauteur*tailleRainure);
    top.localrescaleXY(scaletop);
    ourMesh.merge(top);
}

Mesh Rezdechausse::generate(){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3)/4;
    float dist = std::sqrt((gravity.x-_par->_centreVille.x)*(gravity.x-_par->_centreVille.x)+(gravity.y-_par->_centreVille.y)*(gravity.y-_par->_centreVille.y));
    Vector3D newp0(_p0.x,_p0.y,_p0.z+_hauteur);
    Vector3D newp1(_p1.x,_p1.y,_p1.z+_hauteur);
    Vector3D newp2(_p2.x,_p2.y,_p2.z+_hauteur);
    Vector3D newp3(_p3.x,_p3.y,_p3.z+_hauteur);
    int proba = rand()%100;
    if(proba < (95) && dist < (20*_par->influenceCentreVille)){
        if(rand()%100 < 20 && _par->splitPourcent)
        {
            qDebug()<<_par->splitPourcent;
            if(longueur>largeur*1.8)
            {
                Vector3D mid1;
                mid1.x = (_p0.x+_p1.x)/2;
                mid1.y = (_p0.y+_p1.y)/2;
                Vector3D mid2;
                mid2.x = (_p2.x+_p3.x)/2;
                mid2.y = (_p2.y+_p3.y)/2;
                int randtmp = rand()%100;
                if(randtmp<50 && _par->splitPourcent){
                    int twist = rand()%3;
                    int twist2 = rand()%3;
                    Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                                Vector3D(mid1.x,mid1.y,_p1.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                                Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                                Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                                Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist2);
                    Mesh m1 = etage1.generate();
                    Mesh m2 = etage2.generate();
                    m1.localrescaleXY(0.9);
                    m2.localrescaleXY(0.9);
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }else if(randtmp >= 50 && randtmp <75){
                    qDebug()<<"tutu";
                    int twist = rand()%3;
                    Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                                Vector3D(mid1.x,mid1.y,_p1.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                                Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Toit toit1(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                               Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                               Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                               Vector3D(mid2.x,mid2.y,_p3.z+_hauteur),
                               _hauteur,_par);
                    Mesh m1 = etage1.generate();
                    Mesh m2 = toit1.generate();
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }else{
                    qDebug()<<"tutu";
                    int twist = rand()%3;
                    Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                                Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                                Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Toit toit2(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                               Vector3D(mid1.x,mid1.y,_p1.z+_hauteur),
                               Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                               Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                               _hauteur,_par);
                    Mesh m2 = etage2.generate();
                    Mesh m1 = toit2.generate();
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }
                return ourMesh;

            }else if(largeur>longueur*1.8){
                Vector3D mid1;
                mid1.x = (_p0.x+_p3.x)/2;
                mid1.y = (_p0.y+_p3.y)/2;
                Vector3D mid2;
                mid2.x = (_p1.x+_p2.x)/2;
                mid2.y = (_p1.y+_p2.y)/2;
                int randtmp = rand()%100;
                if(randtmp<50 && _par->splitPourcent){
                    int twist = rand()%3;
                    int twist2 = rand()%3;
                    Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                                Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                                Vector3D(mid1.x,mid1.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p1.z+_hauteur),
                                Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                                Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist2);
                    Mesh m1 = etage1.generate();
                    Mesh m2 = etage2.generate();
                    m1.localrescaleXY(0.9);
                    m2.localrescaleXY(0.9);
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }else if(randtmp >=50 && randtmp <75){
                    qDebug()<<"tutu";
                    int twist = rand()%3;
                    Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                                Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                                Vector3D(mid1.x,mid1.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Toit toit1(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                               Vector3D(mid2.x,mid2.y,_p1.z+_hauteur),
                               Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                               Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                               _hauteur,_par);
                    Mesh m1 = etage1.generate();
                    Mesh m2 = toit1.generate();
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }else{
                    qDebug()<<"tutu";
                    int twist = rand()%3;
                    Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                                Vector3D(mid2.x,mid2.y,_p1.z+_hauteur),
                                Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                                Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                                _hauteur,_par,1,true,twist);
                    Toit toit2(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                               Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                               Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                               Vector3D(mid1.x,mid1.y,_p3.z+_hauteur),
                               _hauteur,_par);
                    Mesh m2 = etage2.generate();
                    Mesh m1 = toit2.generate();
                    ourMesh.merge(m1);
                    ourMesh.merge(m2);
                }

                return ourMesh;
            }else
            {
                Etage etage(newp0,newp1,newp2,newp3,_hauteur, _par,1,false,0);
                ourMesh.merge(etage.generate());
                return ourMesh;
            }
        }else
        {
            Etage etage(newp0,newp1,newp2,newp3,_hauteur, _par,1,false,0);
            ourMesh.merge(etage.generate());
            return ourMesh;
        }
    }else{
        Toit toit(newp0,newp1,newp2,newp3, _hauteur, _par);
        ourMesh.merge(toit.generate());
        return ourMesh;
    }

}

