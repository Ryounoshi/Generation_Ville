#include "etage.h"
#include <iostream>
#include <QDebug>
using namespace std;
#include "toit.h"
#define scaletop 0.9
#define pToit 90
#define pReduction 60
#define tailleRainure 0.05
#define rotation 0.05

Etage::Etage(const Vector3D& p0, const Vector3D& p1, const Vector3D& p2, const Vector3D& p3, float hauteur, BatParameter *par, int noEtage, int type):
    _p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par),_noEtage(noEtage),_type(type)
{
    //cout << " E" << endl;
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);

    _p0Top = _p0;
    _p1Top = _p1;
    _p2Top = _p2;
    _p3Top = _p3;

    //E
    createMesh(_type);
}
Mesh Etage::generate(){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3)/4;
    float dist = std::sqrt((gravity.x-_par->_centreVille.x)*(gravity.x-_par->_centreVille.x)+(gravity.y-_par->_centreVille.y)*(gravity.y-_par->_centreVille.y));
    int proba = rand()%100;
    float bornemax = _par->maxEtage;
    float tmp = dist / ((_par->influenceCentreVille*200)/_par->maxEtage);
    bornemax -= tmp;
    if(_noEtage > bornemax){
        toit();
        return ourMesh;
    }else if(proba<=pReduction){
        if((longueur>largeur*1.2 || largeur>longueur*1.2)){ //si le batiment n'est pas carré on fait un etage identique
            sameEtage();
        }else{  //sinon 20% de chance de faire un etage twisté
            if(rand()%100<20){
                twistedEtage();
            }else{
                sameEtage();
            }
        }
        return ourMesh;
        /*
        if((longueur>largeur*1.5 || largeur>longueur*1.5) && ((rand()%100 < _par->splitPourcent) && !_splited)){
            splitedEtage();
            return ourMesh;
        }else{
            sameEtage();
            return ourMesh;
        }*/
    }else if(proba>pReduction && proba<=pToit){ //on fait un etage plus petit
        smallerEtage();
        return ourMesh;
    }else{
        toit();
        return ourMesh;
    }
}

void Etage::toit(void){
    Vector3D offset(0,0,_hauteur);
    Toit toit(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_noEtage ,_hauteur, _par);
    _par->updateEtageLePlusHaut(Vector3D(),_noEtage);
    Mesh m = toit.generate();
    ourMesh.merge(m);
}

void Etage::twistedEtage(void){
    Vector3D offset(0,0,_hauteur);
    EtageTwisted etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_hauteur, _par,_noEtage+1,E);
    ourMesh.merge(etage.generate());
}

void Etage::smallerEtage(void){
    Vector3D offset(0,0,_hauteur);
    if(rand()%10 < 11 && _type != ERS){
        Etage etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_hauteur, _par,_noEtage+1,ER);
        ourMesh.merge(etage.generate());
    }else{
        Etage etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_hauteur, _par,_noEtage+1,ERS);
        ourMesh.merge(etage.generate());
    }
}

void Etage::sameEtage(void){
    Vector3D offset(0,0,_hauteur);
    Etage etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_hauteur, _par,_noEtage+1,E);
    ourMesh.merge(etage.generate());
}

void Etage::createMesh(int type){

    if(type == ER){
        float scale = 0.9;
        Vector3D gravite = (_p0 + _p1 + _p2 + _p3)/4;

        _p0 -= gravite;
        _p1 -= gravite;
        _p2 -= gravite;
        _p3 -= gravite;

        _p0.x *= scale;
        _p1.x *= scale;
        _p2.x *= scale;
        _p3.x *= scale;
        _p0.y *= scale;
        _p1.y *= scale;
        _p2.y *= scale;
        _p3.y *= scale;

        _p0 += gravite;
        _p1 += gravite;
        _p2 += gravite;
        _p3 += gravite;

        _p0Top = _p0;
        _p1Top = _p1;
        _p2Top = _p2;
        _p3Top = _p3;
    }
    if(type == ERS){
        float scale = 0.9;
        Vector3D gravite = (_p0Top + _p1Top + _p2Top + _p3Top)/4;
        _p0Top -= gravite;
        _p1Top -= gravite;
        _p2Top -= gravite;
        _p3Top -= gravite;

        _p0Top.x *= scale;
        _p1Top.x *= scale;
        _p2Top.x *= scale;
        _p3Top.x *= scale;
        _p0Top.y *= scale;
        _p1Top.y *= scale;
        _p2Top.y *= scale;
        _p3Top.y *= scale;

        _p0Top += gravite;
        _p1Top += gravite;
        _p2Top += gravite;
        _p3Top += gravite;
    }
    ourMesh = Mesh::createQuadrangle3DTwisted(_p0,_p1,_p2,_p3,_p0Top,_p1Top,_p2Top,_p3Top,_hauteur*(1-tailleRainure));
    Mesh top = Mesh::createQuadrangle3D(Vector3D(_p0Top.x,_p0Top.y,_p0Top.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p1Top.x,_p1Top.y,_p1Top.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p2Top.x,_p2Top.y,_p2Top.z+_hauteur*(1-tailleRainure)),
                                        Vector3D(_p3Top.x,_p3Top.y,_p3Top.z+_hauteur*(1-tailleRainure)),
                                        _hauteur*tailleRainure);
    top.localrescaleXY(scaletop);
    ourMesh.merge(top);
}

void Etage::splitedEtage(void){
    /*
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

    }*/
}
