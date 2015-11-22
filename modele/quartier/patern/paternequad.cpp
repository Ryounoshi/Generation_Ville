#include "paternequad.h"

Mesh PaterneQuad::generate()
{

    Mesh m1;
    faireTrotoir(m1);
    faireSol(m1);


    int aleatoire = rand()%100;

    //détermination si le quartier est assez grand pour contenir des batiments avec ruelle
    if(_par->minLargeurBatiment < coeffShrinkMax() && ratioDiametre() < 3 ){
        if(_par->minLargeurBatiment < coeffShrinkMax()/2 ){
            if(aleatoire < 29){
                m1.merge(paternQuatreBatiment());
            }
            else if(aleatoire <= 54){
                m1.merge(paternTroisBatiment());
            }
            else if(aleatoire <= 87){
                m1.merge(paternDeuxBatimentDiagonale());
            }
            else{
                m1.merge(paternQuartierPlein());
            }
        }
        else{
            if(aleatoire < 40){
                m1.merge(paternQuatreBatiment());
            }
            else if(aleatoire < 80){
                m1.merge(paternTroisBatiment());
            }            
            else{
                m1.merge(paternQuartierPlein());
            }
        }
    }
    else if(_par->minLargeurBatiment/2 < coeffShrinkMax()){
        m1.merge(paternQuartierPlein());
    }

    return m1;

}

void PaterneQuad::faireTrotoir(Mesh& m){

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

void PaterneQuad::faireSol(Mesh &m){

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

Mesh PaterneQuad::paternQuatreBatiment(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    centre.shrink( coeffShrinkMax()-_par->largeurRuelle );

    for(int i=0; i<4; i++){
        Vector2D shrink = centre[i] - notreQuadrangle[i];
        Vector2D pIpIm1 = notreQuadrangle[(i-1)%4] - notreQuadrangle[i];
        Vector2D pIpIp1 = notreQuadrangle[(i+1)%4] - notreQuadrangle[i];

        pIpIm1.normalise(); pIpIp1.normalise();

        float dpIpIm1 = shrink.scalareProduct(pIpIm1);
        dpIpIm1 = shrink.getNorm()*shrink.getNorm() / (dpIpIm1*2);

        if(dpIpIm1 >= (notreQuadrangle[(i-1)%4] - notreQuadrangle[i]).getNorm()/2)
            dpIpIm1 = (notreQuadrangle[(i-1)%4] - notreQuadrangle[i]).getNorm()/2 - _par->largeurRuelle/2;

        float dpIpIp1 = shrink.scalareProduct(pIpIp1);
        dpIpIp1 = shrink.getNorm()*shrink.getNorm() / (dpIpIp1*2);

        if(dpIpIp1 >= (notreQuadrangle[(i+1)%4] - notreQuadrangle[i]).getNorm()/2)
            dpIpIp1 = (notreQuadrangle[(i+1)%4] - notreQuadrangle[i]).getNorm()/2 - _par->largeurRuelle/2;

        Vector2D p2 = notreQuadrangle[i] + pIpIp1*dpIpIp1;
        Vector2D p4 = notreQuadrangle[i] + pIpIm1*dpIpIm1;
        Batiment b = Batiment(Vector3D(notreQuadrangle[i].x, notreQuadrangle[i].y, 0),
                              Vector3D(p2.x, p2.y, 0),
                              Vector3D(centre[i].x, centre[i].y, 0),
                              Vector3D(p4.x, p4.y, 0),
                              _par);
        retour.merge( b.generate() );
    }

    return retour;
}

Mesh PaterneQuad::paternTroisBatiment(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    centre.shrink( (coeffShrinkMax())-_par->largeurRuelle );

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
    dp0p3 = (centre[0]-notreQuadrangle[0]).getNorm()*(centre[0]-notreQuadrangle[0]).getNorm() / (dp0p3*2);

    if(dp0p3 >= (notreQuadrangle[3]-notreQuadrangle[0]).getNorm()/2)
        dp0p3 = (notreQuadrangle[3]-notreQuadrangle[0]).getNorm()/2 - _par->largeurRuelle/2;

    float dp1p2 = (centre[1]-notreQuadrangle[1]).scalareProduct(p1p2);
    dp1p2 = (centre[1]-notreQuadrangle[1]).getNorm()*(centre[1]-notreQuadrangle[1]).getNorm() / (dp1p2*2);

    if(dp1p2 >= (notreQuadrangle[2]-notreQuadrangle[1]).getNorm()/2)
        dp1p2 = (notreQuadrangle[2]-notreQuadrangle[1]).getNorm()/2 - _par->largeurRuelle/2;

    float dp2p1 = (centre[2]-notreQuadrangle[2]).scalareProduct(p2p1);
    dp2p1 = (centre[2]-notreQuadrangle[2]).getNorm()*(centre[2]-notreQuadrangle[2]).getNorm() / (dp2p1*2);

    if(dp2p1 >= (notreQuadrangle[1] - notreQuadrangle[2]).getNorm()/2)
        dp2p1 = (notreQuadrangle[1] - notreQuadrangle[2]).getNorm()/2 - _par->largeurRuelle/2;

    float dp2p3 = (centre[2]-notreQuadrangle[2]).scalareProduct(p2p3);
    dp2p3 = (centre[2]-notreQuadrangle[2]).getNorm()*(centre[2]-notreQuadrangle[2]).getNorm() / (dp2p3*2);

    if(dp2p3 >= (notreQuadrangle[3] - notreQuadrangle[2]).getNorm()/2)
        dp2p3 = (notreQuadrangle[3] - notreQuadrangle[2]).getNorm()/2 - _par->largeurRuelle/2;

    float dp3p2 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p2);
    dp3p2 = (centre[3]-notreQuadrangle[3]).getNorm()*(centre[3]-notreQuadrangle[3]).getNorm() / (dp3p2*2);

    if(dp3p2 >= (notreQuadrangle[2] - notreQuadrangle[3]).getNorm()/2)
        dp3p2 = (notreQuadrangle[2] - notreQuadrangle[3]).getNorm()/2 - _par->largeurRuelle/2;

    float dp3p0 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p0);
    dp3p0 = (centre[3]-notreQuadrangle[3]).getNorm()*(centre[3]-notreQuadrangle[3]).getNorm() / (dp3p0*2);

    if(dp3p0 >= (notreQuadrangle[0] - notreQuadrangle[3]).getNorm()/2)
        dp3p0 = (notreQuadrangle[0] - notreQuadrangle[3]).getNorm()/2 - _par->largeurRuelle/2;

    Vector2D p3B1 = notreQuadrangle[1] + p1p2*dp1p2;
    Vector2D p4B1 = notreQuadrangle[0] + p0p3*dp0p3;
    Batiment b = Batiment(Vector3D(notreQuadrangle[0].x, notreQuadrangle[0].y, 0),
            Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0),
            Vector3D(p3B1.x, p3B1.y, 0),
            Vector3D(p4B1.x, p4B1.y, 0),
            _par);
    retour.merge( b.generate() );

    Vector2D p2B2 = notreQuadrangle[2] + p2p3*dp2p3;
    Vector2D p4B2 = notreQuadrangle[2] + p2p1*dp2p1;
    b = Batiment(Vector3D(notreQuadrangle[2].x, notreQuadrangle[2].y, 0),
            Vector3D(p2B2.x, p2B2.y, 0),
            Vector3D(centre[2].x, centre[2].y, 0),
            Vector3D(p4B2.x, p4B2.y, 0),
            _par);
    retour.merge( b.generate() );

    Vector2D p2B3 = notreQuadrangle[3] + p3p0*dp3p0;
    Vector2D p4B3 = notreQuadrangle[3] + p3p2*dp3p2;
    b = Batiment(Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            Vector3D(centre[3].x, centre[3].y, 0),
            Vector3D(p4B3.x, p4B3.y, 0),
            _par);
    retour.merge( b.generate() );

    return retour;
}

Mesh PaterneQuad::paternDeuxBatimentDiagonale(){

    Mesh retour;

    Quadrangle centre = *this, notreQuadrangle = *this;

    float coeffShrink = (coeffShrinkMax()/2);

    centre.shrink( coeffShrink );

    Vector2D p1p0 = notreQuadrangle[0] - notreQuadrangle[1];
    Vector2D p3p2 = notreQuadrangle[2] - notreQuadrangle[3];

    p1p0.normalise();
    p3p2.normalise();

    float dp1p0 = (centre[1]-notreQuadrangle[1]).scalareProduct(p1p0);
    float dp3p2 = (centre[3]-notreQuadrangle[3]).scalareProduct(p3p2);



    Vector2D p2p1 = notreQuadrangle[1] - notreQuadrangle[2];
    p2p1.normalise();

    Vector2D p2B1 = notreQuadrangle[1] + p1p0*dp1p0;
    Vector2D centre2Bis = centre[2] + (p2p1*(_par->largeurRuelle/2));

    Batiment b = Batiment(
                Vector3D(notreQuadrangle[0].x + (-p1p0.x*(_par->largeurRuelle/2)) , notreQuadrangle[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
            Vector3D(p2B1.x, p2B1.y, 0),
            Vector3D(p2B1.x+((centre2Bis-p2B1).normalised()*coeffShrink).x, p2B1.y+((centre2Bis-p2B1).normalised()*coeffShrink).y, 0),
            Vector3D(centre[0].x + (-p1p0.x*(_par->largeurRuelle/2)), centre[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
            _par);
    retour.merge( b.generate() );


    b = Batiment(Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0),
            Vector3D(notreQuadrangle[2].x + (p2p1.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (p2p1.y*(_par->largeurRuelle/2)), 0),
            Vector3D(centre2Bis.x, centre2Bis.y, 0),
            Vector3D(p2B1.x, p2B1.y, 0),
            _par);
    retour.merge( b.generate() );


    Vector2D p0p3 = notreQuadrangle[3] - notreQuadrangle[0];
    p0p3.normalise();

    Vector2D p2B3 = notreQuadrangle[3] + p3p2*dp3p2;
    Vector2D centre0Bis = centre[0] + (p0p3*(_par->largeurRuelle/2));

    b = Batiment(Vector3D(notreQuadrangle[2].x + (-p3p2.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            Vector3D(p2B3.x+((centre0Bis-p2B3).normalised()*coeffShrink).x, p2B3.y+((centre0Bis-p2B3).normalised()*coeffShrink).y, 0),
            Vector3D(centre[2].x + (-p3p2.x*(_par->largeurRuelle/2)), centre[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            _par);
    retour.merge( b.generate() );

    b = Batiment(Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(notreQuadrangle[0].x + (p0p3*(_par->largeurRuelle/2)).x, notreQuadrangle[0].y + (p0p3*(_par->largeurRuelle/2)).y, 0),
            Vector3D(centre0Bis.x, centre0Bis.y, 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            _par);
    retour.merge( b.generate() );

    return retour;

}

Mesh PaterneQuad::paternQuartierPlein()
{
    Mesh retour;

    /*
    point1  X----X  point2
            |    |
            |    |
            |    |
   milieu2  X    X  milieu3
            |    |
   milieu1  X    X  milieu4
            |    |
            |    |
            |    |
    point0  X----X  point3


    */

    Vector2D cote1, cote2;

    if( ((*this)[1] - (*this)[0]).getNorm2() >= ((*this)[2] - (*this)[1]).getNorm2() ){
        Vector2D cote1 = ((*this)[1] - (*this)[0]),
        cote2 = ((*this)[2] - (*this)[3]);

        Vector2D    milieu1 = (*this)[0] + cote1 * (0.5 - ( _par->largeurRuelle / cote1.getNorm() )),
                milieu2 = (*this)[0] + cote1 * (0.5 + ( _par->largeurRuelle / cote1.getNorm() )),
                milieu3 = (*this)[3] + cote2 * (0.5 + ( _par->largeurRuelle / cote2.getNorm() )),
                milieu4 = (*this)[3] + cote2 * (0.5 - ( _par->largeurRuelle / cote2.getNorm() ));


        Batiment b = Batiment(Vector3D( (*this)[0].x, (*this)[0].y, 0),
                Vector3D( milieu1.x, milieu1.y, 0),
                Vector3D( milieu4.x, milieu4.y, 0),
                Vector3D( (*this)[3].x, (*this)[3].y, 0 ),
                _par);
        retour.merge( b.generate() );

        b = Batiment(Vector3D( milieu2.x, milieu2.y, 0),
                     Vector3D( (*this)[1].x, (*this)[1].y, 0),
                Vector3D( (*this)[2].x, (*this)[2].y, 0 ),
                Vector3D( milieu3.x, milieu3.y, 0),
                _par);
        retour.merge( b.generate() );

    }
    else{
        Vector2D cote1 = ((*this)[2] - (*this)[1]),
        cote2 = ((*this)[3] - (*this)[0]);

        Vector2D    milieu1 = (*this)[1] + cote1 * (0.5 - ( _par->largeurRuelle / cote1.getNorm() )),
                milieu2 = (*this)[1] + cote1 * (0.5 + ( _par->largeurRuelle / cote1.getNorm() )),
                milieu3 = (*this)[0] + cote2 * (0.5 + ( _par->largeurRuelle / cote2.getNorm() )),
                milieu4 = (*this)[0] + cote2 * (0.5 - ( _par->largeurRuelle / cote2.getNorm() ));


        Batiment b = Batiment(Vector3D( (*this)[1].x, (*this)[1].y, 0),
                Vector3D( milieu1.x, milieu1.y, 0),
                Vector3D( milieu4.x, milieu4.y, 0),
                Vector3D( (*this)[0].x, (*this)[0].y, 0 ),
                _par);
        retour.merge( b.generate() );

        b = Batiment(Vector3D( milieu2.x, milieu2.y, 0),
                     Vector3D( (*this)[2].x, (*this)[2].y, 0),
                Vector3D( (*this)[3].x, (*this)[3].y, 0 ),
                Vector3D( milieu3.x, milieu3.y, 0),
                _par);
        retour.merge( b.generate() );
    }

    return retour;
}

float PaterneQuad::coeffShrinkMax() const
{
    float retour = FLT_MAX;

    for(int i=0; i<4; i++){
        float d = ( (*this)[i]-(*this)[(i+1)%4] ).getNorm();
        if(d < retour){
            retour = d;
        }
    }

    return retour/2;
}

float PaterneQuad::ratioDiametre() const
{
    float retour = ( (*this)[2]-(*this)[0] ).getNorm() / ( (*this)[1]-(*this)[3] ).getNorm();

    if(retour < 1)
        retour = 1/retour;

    return retour;
}
