#include "paternetri.h"


Mesh PaterneTri::generate()
{

    Mesh m1;
    faireTrotoir(m1);
    faireSol(m1);

    m1.merge(paternConstruction());
    return m1;
}


void PaterneTri::faireTrotoir(Mesh& m){

    Triangle centre = *this, bords = *this;
    centre.shrink(_par->largeurTrotoir);

    for(int i=0; i<3; i++){
        m.addTriangle(  Vector3D(XY(bords[i])),
                        Vector3D(XY(bords[i-1])),
                        Vector3D(XY(centre[i])) );

        m.addTriangle(  Vector3D(XY(centre[i])),
                        Vector3D(XY(bords[i-1])),
                        Vector3D(XY(centre[i-1])) );
    }

    this->shrink(_par->largeurTrotoir);
}

void PaterneTri::faireSol(Mesh &m){
    m.addTriangle(  Vector3D(XY(get(0))),
                    Vector3D(XY(get(2))),
                    Vector3D(XY(get(1))));
}

Mesh PaterneTri::paternConstruction() const{

    Mesh retour;

    float larg = _par->largeurBatiment;

    Vector2D v1 = get(1)-get(0),
            v2 = get(2)-get(1),
            v3 = get(0)-get(2);
    float tv1 = v1.getNorm(),
          tv2 = v2.getNorm(),
          tv3 = v3.getNorm();
    if(tv1 < larg || tv2 < larg || tv3 < larg)
        return retour;

    /////////////////////////////////////////////////////////

    Triangle centre = *this;
    centre.shrink( larg ); //position du point de construction des bâtiments aux angles qui ne sont pas sur les bords du trotoir
    if(dot(v1,centre[1]-centre[0]) < 0 || dot(v2,centre[2]-centre[1]) < 0 || dot(v3,centre[0]-centre[2]) < 0)
        return retour;  //l'un des vecteurs c'est retourné

    v1/=tv1;
    v2/=tv2;
    v3/=tv3;

    Vector2D p11,p12,p13,p21,p22,p23,p31,p32,p33;

    retour =        paternRebordAngle(0, v1,-v3,p11,p12,p13);
    retour.merge(   paternRebordAngle(1, v2,-v1,p21,p22,p23));
    retour.merge(   paternRebordAngle(2, v3,-v2,p31,p32,p33));

    retour.merge(   paternRebord(p11,p23,p22,p12,v1));
    retour.merge(   paternRebord(p21,p33,p32,p22,v2));
    retour.merge(   paternRebord(p31,p13,p12,p32,v3));


    return retour;
}

Mesh PaterneTri::paternAngleTotal(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const
{
    //Mesh retour;

    //float larg = _par->largeurBatiment;

    Vector2D shrink = centre[i] - get(i);

    float sc1 = dot(v1, shrink);
    float sc2 = dot(v2, shrink);

    //if(sc1 > tv1-sc3)   //si l'on essaye de construire les bâtiments dans les angles mais qu'ils vont se supperposer

    Batiment b = Batiment(Vector3D(XY(get(i))),
                          Vector3D(XY((get(i)+v1*sc1))),
                          Vector3D(XY(centre[i])),
                          Vector3D(XY((get(i)+v2*sc2))),
                          _par);
    return b.generate();
}

Mesh PaterneTri::paternAngleCarre2(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const
{
    //Mesh retour;

    float larg = _par->largeurBatiment;

    Vector2D shrink = centre[i] - get(i);

    float sc1 = dot(v1, shrink);
    Vector2D v1o = -v1.vectorProduct();
    float sc2 = (1/dot(v1o, v2))*larg;



    //if(sc1 > tv1-sc3)   //si l'on essaye de construire les bâtiments dans les angles mais qu'ils vont se supperposer

    Batiment b = Batiment(Vector3D(XY(get(i))),
                          Vector3D(XY((get(i)+v1*sc1))),
                          Vector3D(XY(centre[i])),
                          Vector3D(XY((get(i)+v2*sc2))),
                          _par);
    return b.generate();
}

Mesh PaterneTri::paternAngleCarre(int i, const Vector2D& v1, const Vector2D& v2) const
{
    //Mesh retour;

    float larg = _par->largeurBatiment;

    Vector2D v1o = -v1.vectorProduct();
    float sc2 = (1/dot(v1o, v2))*larg;

    Vector2D p = get(i)+v2*sc2+v1*larg;


    float sc1 = dot(v1, p-get(i));


    //if(sc1 > tv1-sc3)   //si l'on essaye de construire les bâtiments dans les angles mais qu'ils vont se supperposer

    Batiment b = Batiment(Vector3D(XY(get(i))),
                          Vector3D(XY((get(i)+v1*sc1))),
                          Vector3D(XY(p)),
                          Vector3D(XY((get(i)+v2*sc2))),
                          _par);
    return b.generate();
}

Mesh PaterneTri::paternRebordAngle(int i, const Vector2D& v1, const Vector2D& v2, Vector2D& p2, Vector2D& p3, Vector2D& p4) const
{
    float larg = _par->largeurBatiment;

    Vector2D v1o = -v1.vectorProduct();
    float sc2 = (1/dot(v1o, v2))*larg;

    p4 = get(i)+v2*sc2;
    p3 = p4+v1*larg;

    float sc1 = dot(v1, p3-get(i));
    p2 = get(i)+v1*sc1;

    Batiment b = Batiment(Vector3D(XY(get(i))),
                          Vector3D(XY(p2)),
                          Vector3D(XY(p3)),
                          Vector3D(XY(p4)),
                          _par);
    return b.generate();
}


Mesh PaterneTri::paternRebord(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4, const Vector2D& v1) const
{
    Mesh retour;
    float larg = _par->largeurBatiment;
    float rue = _par->largeurRuelle;


    Vector2D p11 = p1+v1*rue;
    Vector2D p44 = p4+v1*rue;

    float dist = distance(p11,p2);
    float dist2 = distance(p44, p3);

    if(dist < larg+2*rue || dist2 < larg+rue)
    {
        Vector2D p22 = p2-v1*rue;
        Vector2D p33 = p3-v1*rue;
        if(orientation(p44,p22,p33) >= 0)
            return retour;

        Batiment b = Batiment(Vector3D(XY(p11)),
                              Vector3D(XY(p22)),
                              Vector3D(XY(p33)),
                              Vector3D(XY(p44)),
                              _par);
        return b.generate();
    }
    else
    {
        Vector2D p22 = p11+v1*larg;
        Vector2D p33 = p44+v1*larg;
        if(orientation(p33,p2,p3) > 0)
        {
            p22 = p2-v1*rue;
            p33 = p3-v1*rue;
            Batiment b = Batiment(Vector3D(XY(p11)),
                                  Vector3D(XY(p22)),
                                  Vector3D(XY(p33)),
                                  Vector3D(XY(p44)),
                                  _par);
            return b.generate();
        }

        Batiment b = Batiment(Vector3D(XY(p11)),
                              Vector3D(XY(p22)),
                              Vector3D(XY(p33)),
                              Vector3D(XY(p44)),
                              _par);
        retour = b.generate();
        retour.merge(paternRebord(p22, p2, p3, p33, v1));
        return retour;
    }

}
