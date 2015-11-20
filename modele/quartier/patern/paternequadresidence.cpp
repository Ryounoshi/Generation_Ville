#include "paternequadresidence.h"

Mesh PaterneQuadResidence::generate()
{

    Mesh m1;
    faireTrotoir(m1);
    faireSol(m1);

    int aleatoire = rand()%100;

    if(aleatoire < 33){
        m1.merge(paternQuatreBatiment());
    }
    else if(aleatoire <= 66){
        m1.merge(paternTroisBatiment());
    }
    else{
        m1.merge(paternDeuxBatimentDiagonale());
    }

    return m1;

}

void PaterneQuadResidence::faireTrotoir(Mesh& m){

    Quadrangle centre = *this, notreQuadrangle = *this;
    centre.shrink(_par->largeurTrotoir);

    for(int i=0; i<4; i++){
        m.addTriangle( Vector3D(notreQuadrangle[i].x, notreQuadrangle[i].y, 0),
                       Vector3D(notreQuadrangle[(i-1)%4].x, notreQuadrangle[(i-1)%4].y, 0),
                Vector3D(centre[i].x, centre[i].y, 0) );

        m.addTriangle( Vector3D(centre[i].x, centre[i].y, 0),
                       Vector3D(notreQuadrangle[(i-1)%4].x, notreQuadrangle[(i-1)%4].y, 0),
                Vector3D(centre[(i-1)%4].x, centre[(i-1)%4].y, 0) );
    }

    this->shrink(_par->largeurTrotoir);
}

void PaterneQuadResidence::faireSol(Mesh &m){

    Quadrangle notreQuadrangle = *this;

    m.addTriangle( Vector3D(notreQuadrangle[0].x, notreQuadrangle[0].y, 0),
            Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0) );

    m.addTriangle( Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0),
            Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(notreQuadrangle[2].x, notreQuadrangle[2].y, 0) );
}

//***********************//
//****** Paterns ********//
//***********************//

Mesh PaterneQuadResidence::paternQuatreBatiment(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    centre.shrink( (cotePlusCourt()/2)-_par->largeurRuelle );

    for(int i=0; i<4; i++){
        Vector2D shrink = centre[i] - notreQuadrangle[i];
        Vector2D pIpIm1 = notreQuadrangle[(i-1)%4] - notreQuadrangle[i];
        Vector2D pIpIp1 = notreQuadrangle[(i+1)%4] - notreQuadrangle[i];

        pIpIm1.normalise(); pIpIp1.normalise();

        float dpIpIm1 = shrink.scalareProduct(pIpIm1);
        float dpIpIp1 = shrink.scalareProduct(pIpIp1);

        Vector2D p2 = notreQuadrangle[i] + pIpIp1*dpIpIp1;
        Vector2D p4 = notreQuadrangle[i] + pIpIm1*dpIpIm1;
        Batiment b = Batiment(Vector3D(notreQuadrangle[i].x, notreQuadrangle[i].y, 0),
                              Vector3D(p2.x, p2.y, 0),
                              Vector3D(centre[i].x, centre[i].y, 0),
                              Vector3D(p4.x, p4.y, 0),
                              0.7,
                              _par);
        retour.merge( b.generate() );
    }

    return retour;
}

Mesh PaterneQuadResidence::paternTroisBatiment(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    centre.shrink( (cotePlusCourt()/2)-_par->largeurRuelle );

    Vector2D p0p3 = notreQuadrangle[3] - notreQuadrangle[0];
    Vector2D p1p2 = notreQuadrangle[2] - notreQuadrangle[1];

    Vector2D p2p1 = notreQuadrangle[1] - notreQuadrangle[2];
    Vector2D p2p3 = notreQuadrangle[3] - notreQuadrangle[2];

    Vector2D p3p2 = notreQuadrangle[2] - notreQuadrangle[3];
    Vector2D p3p0 = notreQuadrangle[0] - notreQuadrangle[3];

    p0p3.normalise(); p1p2.normalise();
    p2p1.normalise(); p2p3.normalise();
    p3p2.normalise(); p3p0.normalise();

    float dp0p3 = (centre[0]-notreQuadrangle[0]).scalareProduct(p0p3);
    float dp1p2 = (centre[1]-notreQuadrangle[1]).scalareProduct(p1p2);
    float dp2p1 = (centre[2]-notreQuadrangle[2]).scalareProduct(p2p1);
    float dp2p3 = (centre[2]-notreQuadrangle[2]).scalareProduct(p2p3);
    float dp3p2 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p2);
    float dp3p0 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p0);

    Vector2D p3B1 = notreQuadrangle[1] + p1p2*dp1p2;
    Vector2D p4B1 = notreQuadrangle[0] + p0p3*dp0p3;
    Batiment b = Batiment(Vector3D(notreQuadrangle[0].x, notreQuadrangle[0].y, 0),
            Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0),
            Vector3D(p3B1.x, p3B1.y, 0),
            Vector3D(p4B1.x, p4B1.y, 0),
            0.7,
            _par);
    retour.merge( b.generate() );

    Vector2D p2B2 = notreQuadrangle[2] + p2p3*dp2p3;
    Vector2D p4B2 = notreQuadrangle[2] + p2p1*dp2p1;
    b = Batiment(Vector3D(notreQuadrangle[2].x, notreQuadrangle[2].y, 0),
            Vector3D(p2B2.x, p2B2.y, 0),
            Vector3D(centre[2].x, centre[2].y, 0),
            Vector3D(p4B2.x, p4B2.y, 0),
            0.7,
            _par);
    retour.merge( b.generate() );

    Vector2D p2B3 = notreQuadrangle[3] + p3p0*dp3p0;
    Vector2D p4B3 = notreQuadrangle[3] + p3p2*dp3p2;
    b = Batiment(Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            Vector3D(centre[3].x, centre[3].y, 0),
            Vector3D(p4B3.x, p4B3.y, 0),
            0.7,
            _par);
    retour.merge( b.generate() );

    return retour;
}

Mesh PaterneQuadResidence::paternDeuxBatimentDiagonale(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    centre.shrink( (cotePlusCourt()/3) );

    Vector2D p1p0 = notreQuadrangle[0] - notreQuadrangle[1];
    Vector2D p3p2 = notreQuadrangle[2] - notreQuadrangle[3];    

    p1p0.normalise();
    p3p2.normalise();

    float dp1p0 = (centre[1]-notreQuadrangle[1]).scalareProduct(p1p0);
    float dp3p2 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p2);



    Vector2D p2p1 = notreQuadrangle[1] - notreQuadrangle[2];
    p2p1.normalise();

    Vector2D p2B1 = notreQuadrangle[1] + p1p0*dp1p0;
    Batiment b = Batiment(
                Vector3D(notreQuadrangle[0].x + (-p1p0.x*(_par->largeurRuelle/2)) , notreQuadrangle[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
                Vector3D(p2B1.x, p2B1.y, 0),
                Vector3D(centre[1].x, centre[1].y , 0),
                Vector3D(centre[0].x + (-p1p0.x*(_par->largeurRuelle/2)), centre[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
                0.7,
                _par);
    retour.merge( b.generate() );

    b = Batiment(Vector3D(notreQuadrangle[1].x + (p2p1.x*(_par->largeurRuelle/2)), notreQuadrangle[1].y + (p2p1.y*(_par->largeurRuelle/2)), 0),
            Vector3D(notreQuadrangle[2].x + (p2p1.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (p2p1.y*(_par->largeurRuelle/2)), 0),
            Vector3D(centre[2].x, centre[2].y, 0),
            Vector3D(p2B1.x, p2B1.y, 0),
            0.7,
            _par);
    retour.merge( b.generate() );


    Vector2D p0p3 = notreQuadrangle[3] - notreQuadrangle[0];
    p0p3.normalise();

    Vector2D p2B3 = notreQuadrangle[3] + p3p2*dp3p2;
    b = Batiment(Vector3D(notreQuadrangle[2].x + (-p3p2.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            Vector3D(centre[3].x, centre[3].y, 0),
            Vector3D(centre[2].x + (-p3p2.x*(_par->largeurRuelle/2)), centre[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            0.7,
            _par);
    retour.merge( b.generate() );

    b = Batiment(Vector3D(notreQuadrangle[3].x + (p0p3.x*(_par->largeurRuelle/2)), notreQuadrangle[3].y + (p0p3.x*(_par->largeurRuelle/2)), 0),
            Vector3D(notreQuadrangle[0].x + (p0p3.x*(_par->largeurRuelle/2)), notreQuadrangle[0].y + (p0p3.x*(_par->largeurRuelle/2)), 0),
            Vector3D(centre[0].x, centre[0].y, 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            0.7,
            _par);
    retour.merge( b.generate() );

    return retour;

}

Mesh PaterneQuadResidence::paternDeuxBatimentDiametre(){

    Mesh retour;

    /*
    Quadrangle centre = *this, notreQuadrangle = *this;
    centre.shrink(_par->largeurBatiment);

    for(int i=0; i<4; i++){
        Vector2D shrink = centre[i] - notreQuadrangle[i];
        Vector2D pIpIm1 = notreQuadrangle[(i-1)%4] - notreQuadrangle[i];
        Vector2D pIpIp1 = notreQuadrangle[(i+1)%4] - notreQuadrangle[i];

        pIpIm1 = pIpIm1.normalise(); pIpIp1 = pIpIp1.normalise();

        float dpIpIm1 = shrink.scalareProduct(pIpIm1);
        float dpIpIp1 = shrink.scalareProduct(pIpIp1);

        Vector2D p2 = notreQuadrangle[i] + pIpIp1*dpIpIp1;
        Vector2D p4 = notreQuadrangle[i] + pIpIm1*dpIpIm1;
        Batiment b = Batiment(Vector3D(notreQuadrangle[i].x, notreQuadrangle[i].y, 0),
                              Vector3D(p2.x, p2.y, 0),
                              Vector3D(centre[i].x, centre[i].y, 0),
                              Vector3D(p4.x, p4.y, 0),
                              0.7,
                              _par);
        m1.merge( b.generate() );
    }
    */

    return retour;
}

float PaterneQuadResidence::cotePlusCourt() const
{
    float retour = FLT_MAX;

    for(int i=0; i<4; i++){
        float d = ( (*this)[i]-(*this)[(i+1)%4] ).getNorm();
        if(d < retour){
            retour = d;
        }
    }

    return retour;
}
