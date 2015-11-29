#include "etagehexa.h"
#include "toithexa.h"
#include "etagehexatwisted.h"
#include <iostream>
#include <QDebug>
using namespace std;
#include "toit.h"
#define scaletop 0.9
#define pToit 90
#define pReduction 60
#define tailleRainure 0.05
#define rotation 0.05

EtageHexa::EtageHexa(const Vector3D &p0, const Vector3D &p1, const Vector3D &p2, const Vector3D &p3, const Vector3D &p4, const Vector3D &p5,float hauteur, BatParameter *par, int noEtage, int type):
    _p0(p0),_p1(p1),_p2(p2),_p3(p3),_p4(p4),_p5(p5),_hauteur(hauteur),_par(par),_noEtage(noEtage),_type(type)
{
    //cout << " E" << endl;
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);

    _p0Top = _p0;
    _p1Top = _p1;
    _p2Top = _p2;
    _p3Top = _p3;
    _p4Top = _p4;
    _p5Top = _p5;

    //E
    createMesh(_type);
}

Mesh EtageHexa::generate(){
    Vector3D gravity = (_p0 + _p1 + _p2 + _p3 + _p4 +_p5)/6;
    float dist = std::sqrt((gravity.x-_par->_centreVille.x)*(gravity.x-_par->_centreVille.x)+(gravity.y-_par->_centreVille.y)*(gravity.y-_par->_centreVille.y));
    int proba = rand()%100;
    float bornemax = _par->maxEtage;
    float tmp = dist / ((_par->influenceCentreVille*200)/_par->maxEtage);
    bornemax -= tmp;
    if(_noEtage > bornemax){
        toit();
        return ourMesh;
    }else if(proba<=pReduction){
        if((longueur>largeur*1.6 || largeur>longueur*1.6)){ //si le batiment n'est pas carré on fait un etage identique
            //twistedEtage();
            sameEtage();
        }else{  //sinon 50% de chance de faire un etage twisté
            if(rand()%100<50){
                twistedEtage();
            }else{
                //twistedEtage();
                sameEtage();
            }
        }
        return ourMesh;
    }else if(proba>pReduction && proba<=pToit){ //on fait un etage plus petit
        smallerEtage();
        return ourMesh;
    }else{
        toit();
        return ourMesh;
    }
}

void EtageHexa::toit(void){
    Vector3D offset(0,0,_hauteur);
    ToitHexa toit(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_noEtage ,_hauteur, _par);
    _par->updateEtageLePlusHaut(Vector3D(),_noEtage);
    Mesh m = toit.generate();
    ourMesh.merge(m);
}

void EtageHexa::twistedEtage(void){
    Vector3D offset(0,0,_hauteur);
    EtageHexaTwisted etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_hauteur, _par,_noEtage+1,E);
    ourMesh.merge(etage.generate());
}

void EtageHexa::smallerEtage(void){
    Vector3D offset(0,0,_hauteur);
    if(rand()%10 < 6 && _type != ERS){
        if(rand()%2){
            EtageHexa etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_hauteur, _par,_noEtage+1,ER2);
            ourMesh.merge(etage.generate());
        }else{
            EtageHexa etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_hauteur, _par,_noEtage+1,ER);
            ourMesh.merge(etage.generate());
        }
    }else{
        EtageHexa etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_hauteur, _par,_noEtage+1,ERS);
        ourMesh.merge(etage.generate());
    }
}

void EtageHexa::sameEtage(void){
    Vector3D offset(0,0,_hauteur);
    EtageHexa etage(_p0Top+offset,_p1Top+offset,_p2Top+offset,_p3Top+offset,_p4Top+offset,_p5Top+offset,_hauteur, _par,_noEtage+1,E);
    ourMesh.merge(etage.generate());
}

void EtageHexa::createMesh(int type){

    if(type == ER){
        float scale = 0.9;
        Vector3D gravite = (_p0 + _p1 + _p2 + _p3+ _p4 +_p5)/6;

        _p0 -= gravite;
        _p1 -= gravite;
        _p2 -= gravite;
        _p3 -= gravite;
        _p4 -= gravite;
        _p5 -= gravite;

        _p0.x *= scale;
        _p1.x *= scale;
        _p2.x *= scale;
        _p3.x *= scale;
        _p4.x *= scale;
        _p5.x *= scale;
        _p0.y *= scale;
        _p1.y *= scale;
        _p2.y *= scale;
        _p3.y *= scale;
        _p4.y *= scale;
        _p5.y *= scale;

        _p0 += gravite;
        _p1 += gravite;
        _p2 += gravite;
        _p3 += gravite;
        _p4 += gravite;
        _p5 += gravite;

        _p0Top = _p0;
        _p1Top = _p1;
        _p2Top = _p2;
        _p3Top = _p3;
        _p4Top = _p4;
        _p5Top = _p5;
    }else if(type == ER2){
        float scale = 0.8;
        Vector3D lon = (_p5 - _p0);
        Vector3D lon2 = (_p4 - _p0);
        Vector3D lon3 = (_p3 - _p1);
        Vector3D lon4 = (_p2 - _p1);
        _p2 = _p1 + lon4*scale;
        _p3 = _p1 + lon3*scale;
        _p4 = _p0 + lon2*scale;
        _p5 = _p0 + lon*scale;

        _p0Top = _p0;
        _p1Top = _p1;
        _p2Top = _p2;
        _p3Top = _p3;
        _p4Top = _p4;
        _p5Top = _p5;

    }
    if(type == ERS){
        float scale = 0.9;
        Vector3D gravite = (_p0Top + _p1Top + _p2Top + _p3Top +_p4 +_p5)/6;
        _p0Top -= gravite;
        _p1Top -= gravite;
        _p2Top -= gravite;
        _p3Top -= gravite;
        _p4Top -= gravite;
        _p5Top -= gravite;

        _p0Top.x *= scale;
        _p1Top.x *= scale;
        _p2Top.x *= scale;
        _p3Top.x *= scale;
        _p4Top.x *= scale;
        _p5Top.x *= scale;
        _p0Top.y *= scale;
        _p1Top.y *= scale;
        _p2Top.y *= scale;
        _p3Top.y *= scale;
        _p4Top.y *= scale;
        _p5Top.y *= scale;

        _p0Top += gravite;
        _p1Top += gravite;
        _p2Top += gravite;
        _p3Top += gravite;
        _p4Top += gravite;
        _p5Top += gravite;
    }
    ourMesh = Mesh::createHexaangleTwisted(_p0,_p1,_p2,_p3,_p4,_p5,_p0Top,_p1Top,_p2Top,_p3Top,_p4Top,_p5Top,_hauteur*(1-tailleRainure));
    Mesh top = Mesh::createHexaangle3D(Vector3D(_p0Top.x,_p0Top.y,_p0Top.z+_hauteur*(1-tailleRainure)),
                                       Vector3D(_p1Top.x,_p1Top.y,_p1Top.z+_hauteur*(1-tailleRainure)),
                                       Vector3D(_p2Top.x,_p2Top.y,_p2Top.z+_hauteur*(1-tailleRainure)),
                                       Vector3D(_p3Top.x,_p3Top.y,_p3Top.z+_hauteur*(1-tailleRainure)),
                                       Vector3D(_p4Top.x,_p4Top.y,_p4Top.z+_hauteur*(1-tailleRainure)),
                                       Vector3D(_p5Top.x,_p5Top.y,_p5Top.z+_hauteur*(1-tailleRainure)),
                                        _hauteur*tailleRainure);
    top.localrescaleXY(scaletop);
    ourMesh.merge(top);
}
