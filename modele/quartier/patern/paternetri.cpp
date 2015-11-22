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

    float larg = _par->minLargeurBatiment;

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

    retour =        paternAngle(centre, 0, v1,-v3, tv1,tv3);
    retour.merge(   paternAngle(centre, 1, v2,-v1, tv2,tv1));
    retour.merge(   paternAngle(centre, 2, v3,-v2, tv3,tv2));


    return retour;
}

Mesh PaterneTri::paternAngle(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2, float tv1, float tv2) const
{
    //Mesh retour;

    //float larg = _par->minLargeurBatiment;

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
