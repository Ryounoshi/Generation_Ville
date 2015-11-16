#include "etage.h"
#include <iostream>
#include <QDebug>
using namespace std;
#include "toit.h"
#define scaletop 0.9
#define pToit 90
#define pReduction 40
#define tailleRainure 0.01
#define rotation 0.05

Etage::Etage(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par, int noEtage, bool splited, int twisted):_p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par),_noEtage(noEtage),_splited(splited),_twisted(twisted)
{
    //cout << " E" << endl;
    longueur = distance(p0, p1);
    largeur = distance(p0, p3);
    ourMesh = Mesh::createQuadrangle3D(_p0,_p1,_p2,_p3,_hauteur*(1-tailleRainure));
    Mesh top = Mesh::createQuadrangle3D(Vector3D(_p0.x,_p0.y,p0.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p1.x,_p1.y,p1.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p2.x,_p2.y,p2.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p3.x,_p3.y,p3.z+_hauteur*(1-tailleRainure)),
                                        _hauteur*tailleRainure);
    top.localrescaleXY(scaletop);
    ourMesh.merge(top);
}
Mesh Etage::generate(){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3)/4;
    float dist = std::sqrt((gravity.x-_par->_centreVille.x)*(gravity.x-_par->_centreVille.x)+(gravity.y-_par->_centreVille.y)*(gravity.y-_par->_centreVille.y));

    //_hauteur *= 0.9;
    Vector3D newp0(_p0.x,_p0.y,_p0.z+_hauteur);
    Vector3D newp1(_p1.x,_p1.y,_p1.z+_hauteur);
    Vector3D newp2(_p2.x,_p2.y,_p2.z+_hauteur);
    Vector3D newp3(_p3.x,_p3.y,_p3.z+_hauteur);
    int proba = rand()%100;
    //if(_noEtage > (_par->maxEtage - (dist*_par->influenceCentreVille)/(_par->influenceCentreVille*_par->influenceCentreVille))){
    float bornemax = _par->maxEtage;
    float tmp = dist / ((_par->influenceCentreVille*20)/_par->maxEtage);
    bornemax -= tmp;
    if(_noEtage > bornemax){
        Toit toit(newp0,newp1,newp2,newp3, _hauteur, _par);
        _par->updateEtageLePlusHaut(Vector3D(),_noEtage);
        Mesh m = toit.generate();
        ourMesh.merge(m);
        return ourMesh;
    }else if(proba<=pReduction){
        if((rand()%100 < _par->splitPourcent) && !_splited){
            if(longueur>largeur*1.5){
                int twist = rand()%3;
                Vector3D mid1;
                mid1.x = (_p0.x+_p1.x)/2;
                mid1.y = (_p0.y+_p1.y)/2;
                Vector3D mid2;
                mid2.x = (_p2.x+_p3.x)/2;
                mid2.y = (_p2.y+_p3.y)/2;

                Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                            Vector3D(mid1.x,mid1.y,_p1.z+_hauteur),
                            Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                            Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                            _hauteur,_par,_noEtage+1,true,twist);
                Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                            Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                            Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                            Vector3D(mid2.x,mid2.y,_p3.z+_hauteur),
                            _hauteur,_par,_noEtage+1,true,twist);
                Mesh m1 = etage1.generate();
                Mesh m2 = etage2.generate();
                m1.localrescaleXY(0.9);
                m2.localrescaleXY(0.9);
                twister(m1);
                twister(m2);
                ourMesh.merge(m1);
                ourMesh.merge(m2);
                return ourMesh;

            }else if(largeur>longueur*1.5){
                int twist = rand()%3;
                Vector3D mid1;
                mid1.x = (_p0.x+_p3.x)/2;
                mid1.y = (_p0.y+_p3.y)/2;
                Vector3D mid2;
                mid2.x = (_p1.x+_p2.x)/2;
                mid2.y = (_p1.y+_p2.y)/2;

                Etage etage1(Vector3D(_p0.x,_p0.y,_p0.z+_hauteur),
                            Vector3D(_p1.x,_p1.y,_p1.z+_hauteur),
                            Vector3D(mid2.x,mid2.y,_p2.z+_hauteur),
                            Vector3D(mid1.x,mid1.y,_p3.z+_hauteur),
                            _hauteur,_par,_noEtage+1,true,twist);
                Etage etage2(Vector3D(mid1.x,mid1.y,_p0.z+_hauteur),
                            Vector3D(mid2.x,mid2.y,_p1.z+_hauteur),
                            Vector3D(_p2.x,_p2.y,_p2.z+_hauteur),
                            Vector3D(_p3.x,_p3.y,_p3.z+_hauteur),
                            _hauteur,_par,_noEtage+1,true,twist);
                Mesh m1 = etage1.generate();
                Mesh m2 = etage2.generate();
                m1.localrescaleXY(0.9);
                m2.localrescaleXY(0.9);
                twister(m1);
                twister(m2);
                ourMesh.merge(m1);
                ourMesh.merge(m2);
                return ourMesh;

            }else{
                Etage etage(newp0,newp1,newp2,newp3,_hauteur, _par,_noEtage+1,_splited,_twisted);
                Mesh m = etage.generate();
                twister(m);
                ourMesh.merge(m);
                return ourMesh;
            }
        }else{
            Etage etage(newp0,newp1,newp2,newp3,_hauteur, _par,_noEtage+1,_splited,_twisted);
            Mesh m = etage.generate();
            twister(m);
            ourMesh.merge(m);

            return ourMesh;
        }
    }else if(proba>pReduction && proba<=pToit){ //on fait un etage plus petit
        Etage etage(newp0,newp1,newp2,newp3,_hauteur, _par,_noEtage+1,_splited,_twisted);
        Mesh m = etage.generate();
        m.localrescaleXY(0.9);
        twister(m);
        ourMesh.merge(m);
        return ourMesh;
    }else{
        _par->updateEtageLePlusHaut(Vector3D(),_noEtage);
        Toit toit(newp0,newp1,newp2,newp3, _hauteur, _par);
        Mesh m = toit.generate();
        ourMesh.merge(m);
        return ourMesh;
    }
}

void Etage::twister(Mesh &m){
    if(_twisted == 1){
        m.localRotation(0,0,rotation);
    }else if(_twisted == 2){
        m.localRotation(0,0,-rotation);
    }
}
