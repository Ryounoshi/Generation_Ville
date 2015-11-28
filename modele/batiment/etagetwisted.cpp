#include "etagetwisted.h"
#define scaletop 0.9
#define pToit 90
#define pReduction 60
#define tailleRainure 0.05
#define rotation 0.05

EtageTwisted::EtageTwisted(const Vector3D &p0, const Vector3D &p1, const Vector3D &p2, const Vector3D &p3, float hauteur, BatParameter *par, int noEtage, int type):
    _p0(p0),_p1(p1),_p2(p2),_p3(p3),_hauteur(hauteur),_par(par),_noEtage(noEtage),_type(type)
{
    longueur = distance(p0,p1);
    largeur = distance(p0,p3);

    _p0Top = _p0;
    _p1Top = _p1;
    _p2Top = _p2;
    _p3Top = _p3;

    Vector3D gravite = (_p0 + _p1 + _p2 + _p3)/4;

    _p0Top -= gravite;
    _p1Top -= gravite;
    _p2Top -= gravite;
    _p3Top -= gravite;

    _p0Top.rotateAboutZ(rotation);
    _p1Top.rotateAboutZ(rotation);
    _p2Top.rotateAboutZ(rotation);
    _p3Top.rotateAboutZ(rotation);

    _p0Top += gravite;
    _p1Top += gravite;
    _p2Top += gravite;
    _p3Top += gravite;

    createMesh(_type);
}

Mesh EtageTwisted::generate(){
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
        smallerEtage();
        //sameEtage();
        return ourMesh;
    }else if(proba>pReduction && proba<=pToit){ //on fait un etage plus petit
        smallerEtage();
        return ourMesh;
    }else{
        toit();
        return ourMesh;
    }
}


void EtageTwisted::toit(void){
    Vector3D newp0(_p0Top.x,_p0Top.y,_p0Top.z+_hauteur);
    Vector3D newp1(_p1Top.x,_p1Top.y,_p1Top.z+_hauteur);
    Vector3D newp2(_p2Top.x,_p2Top.y,_p2Top.z+_hauteur);
    Vector3D newp3(_p3Top.x,_p3Top.y,_p3Top.z+_hauteur);

    Toit toit(newp0,newp1,newp2,newp3,_noEtage ,_hauteur, _par);
    _par->updateEtageLePlusHaut(Vector3D(),_noEtage);
    Mesh m = toit.generate();
    ourMesh.merge(m);
}

void EtageTwisted::smallerEtage(void){
    Vector3D newp0(_p0Top.x,_p0Top.y,_p0Top.z+_hauteur);
    Vector3D newp1(_p1Top.x,_p1Top.y,_p1Top.z+_hauteur);
    Vector3D newp2(_p2Top.x,_p2Top.y,_p2Top.z+_hauteur);
    Vector3D newp3(_p3Top.x,_p3Top.y,_p3Top.z+_hauteur);

    EtageTwisted etage(newp0,newp1,newp2,newp3,_hauteur, _par,_noEtage+1,ER);
    ourMesh.merge(etage.generate());
}

void EtageTwisted::sameEtage(void){
    Vector3D newp0(_p0Top.x,_p0Top.y,_p0Top.z+_hauteur);
    Vector3D newp1(_p1Top.x,_p1Top.y,_p1Top.z+_hauteur);
    Vector3D newp2(_p2Top.x,_p2Top.y,_p2Top.z+_hauteur);
    Vector3D newp3(_p3Top.x,_p3Top.y,_p3Top.z+_hauteur);

    EtageTwisted etage(newp0,newp1,newp2,newp3,_hauteur, _par,_noEtage+1,E);
    ourMesh.merge(etage.generate());
}

void EtageTwisted::createMesh(int type){
    if(type == ER){
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

