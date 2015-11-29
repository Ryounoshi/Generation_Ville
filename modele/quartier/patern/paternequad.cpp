#include "paternequad.h"

Mesh PaterneQuad::generate()
{

    Mesh m1;
    faireTrotoir(m1);
    faireSol(m1);

    // Taille aléatoire
    _profondeurBatiment = (rand()%100) / 100.0;
    _profondeurBatiment = _par->minLargeurBatiment + _profondeurBatiment*(coeffShrinkMax()-_par->minLargeurBatiment-_par->largeurRuelle);
    //


    Quadrangle batimentsCoin[4];

    for(int i=0; i<4; i++){
        retour.merge(remplissageCoin(i, batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[i][3] ));
    }

    for(int i=0; i<4; i++){
        retour.merge(remplissageBord(batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[(i+1)%4][2], batimentsCoin[(i+1)%4][3] ));
    }


    //int aleatoire = rand()%100;

    /*
    //détermination si le quartier est assez grand pour contenir des batiments avec ruelle
    if(_par->minLargeurBatiment < coeffShrinkMax() && ratioDiametre() < 4 ){
        if(_par->minLargeurBatiment < coeffShrinkMax()/1.5 ){
            if(aleatoire < 45){
                m1.merge(paternQuatreBatiment());
            }
            else if(aleatoire <= 90){
                m1.merge(paternTroisBatiment());
            }
            else{
                m1.merge(paternDeuxBatimentDiagonale());
            }
        }
        else{
            if(aleatoire < 60){
                m1.merge(paternQuatreBatiment());
            }
            else{
                m1.merge(paternTroisBatiment());
            }
        }
    }

    */

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

    Quadrangle batimentsCoin[4];

    for(int i=0; i<4; i++){
        retour.merge(remplissageCoin(i, batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[i][3] ));
    }

    for(int i=0; i<4; i++){
        retour.merge(remplissageBord(batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[(i+1)%4][2], batimentsCoin[(i+1)%4][3] ));
    }

    return retour;
}

Mesh PaterneQuad::paternTroisBatiment(){

    Mesh retour;

    Quadrangle batiments[4];

    determinationBatimentCoin(0, batiments[0][1], batiments[0][2], batiments[0][3]);
    determinationBatimentCoin(1, batiments[1][1], batiments[1][2], batiments[1][3]);

    retour.merge(remplissageCoin(2, batiments[2][1], batiments[2][2], batiments[2][3]));
    retour.merge(remplissageCoin(3, batiments[3][1], batiments[3][2], batiments[3][3]));

    Batiment b(Vector3D( XY((*this)[0]), 0), Vector3D( XY((*this)[1]), 0),
            Vector3D( XY(batiments[1][1]), 0), Vector3D( XY(batiments[0][3]), 0), _par);
    retour.merge(b.generate());

    retour.merge(remplissageBord(batiments[1][1], batiments[1][2], batiments[2][2], batiments[2][3] ));
    retour.merge(remplissageBord(batiments[2][1], batiments[2][2], batiments[3][2], batiments[3][3] ));
    retour.merge(remplissageBord(batiments[3][1], batiments[3][2], batiments[0][2], batiments[0][3] ));

    return retour;
}

/*
Mesh PaterneQuad::paternDeuxBatimentDiagonale(){

    Mesh retour;

    Quadrangle batimentsCoin[4];

    for(int i=0; i<4; i++){
        if(i==1 || i == 3)
            retour.merge( remplissageCoin( i, batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[i][3] ) );
        else
            determinationBatimentCoin(i, batimentsCoin[i][1], batimentsCoin[i][2], batimentsCoin[i][3] );
    }

    for(int i=0; i<4; i++){

        if(i == 0 || i == 2){
            Vector2D p1B0 = batimentsCoin[i][1] + ((*this)[(i+1)%4]-(*this)[i]).normalised() *_par->largeurRuelle/2 ,
                    p2B0 = batimentsCoin[i][2] + ((*this)[(i+1)%4]-(*this)[i]).normalised() *_par->largeurRuelle/2;

            retour.merge(remplissageBord(
                            batimentsCoin[i][1],
                            p2B0,
                            batimentsCoin[(i+1)%4][2],
                            batimentsCoin[(i+1)%4][3] ) ) ;
        }
        else{
            Vector2D p2B1 = batimentsCoin[(i+1)%4][2] + ((*this)[i]-(*this)[(i+1)%4]).normalised() *_par->largeurRuelle/2,
                    p3B1 = batimentsCoin[(i+1)%4][3] + ((*this)[i]-(*this)[(i+1)%4]).normalised() *_par->largeurRuelle/2;

            retour.merge(remplissageBord(
                            batimentsCoin[i][1],
                            batimentsCoin[i][2],
                            p2B1,
                            p3B1 ) );
        }
    }

    /*

    Vector2D p0p1 = ((*this)[1] - (*this)[0]).normalised();
    Vector2D p2p1 = ((*this)[2] - (*this)[1]).normalised();

    /*
    Batiment b = Batiment(
                Vector3D(notreQuadrangle[0].x + (-p1p0.x*(_par->largeurRuelle/2)) , notreQuadrangle[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
            Vector3D(p2B1.x, p2B1.y, 0),
            Vector3D(p2B1.x+((centre2Bis-p2B1).normalised()*coeffShrink).x, p2B1.y+((centre2Bis-p2B1).normalised()*coeffShrink).y, 0),
            Vector3D(centre[0].x + (-p1p0.x*(_par->largeurRuelle/2)), centre[0].y + (-p1p0.y*(_par->largeurRuelle/2)), 0),
            _par);
    */

    /*

    Batiment b = Batiment( Vector3D( XY( ( (*this)[0] + p0p1*_par->largeurRuelle/2 ) ), 0),
            Vector3D( XY( batimentsCoin[1][3] ), 0),
            Vector3D( XY( batimentsCoin[1][2] ), 0),
            Vector3D( XY( ( batimentsCoin[0][2] + p0p1*_par->largeurRuelle/2 ) ), 0),
            _par);
    retour.merge( b.generate() );


    /*
    b = Batiment(Vector3D(notreQuadrangle[1].x, notreQuadrangle[1].y, 0),
            Vector3D(notreQuadrangle[2].x + (p2p1.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (p2p1.y*(_par->largeurRuelle/2)), 0),
            Vector3D(centre2Bis.x, centre2Bis.y, 0),
            Vector3D(p2B1.x, p2B1.y, 0),
            _par);*/
/*
    b = Batiment( Vector3D( XY( (*this)[1] ), 0),
                Vector3D( XY( ( (*this)[2] + p2p1*_par->largeurRuelle/2 ) ), 0),
                Vector3D( XY( ( batimentsCoin[2][2] + p2p1*_par->largeurRuelle/2 ) ), 0),
                Vector3D( XY( batimentsCoin[1][3] ), 0),
                _par);
    retour.merge( b.generate() );


    Vector2D p2p3 = ((*this)[3] - (*this)[2]).normalised();
    Vector2D p0p3 = ((*this)[3] - (*this)[0]).normalised();

    /*
    b = Batiment(Vector3D(notreQuadrangle[2].x + (-p3p2.x*(_par->largeurRuelle/2)), notreQuadrangle[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            Vector3D(p2B3.x+((centre0Bis-p2B3).normalised()*coeffShrink).x, p2B3.y+((centre0Bis-p2B3).normalised()*coeffShrink).y, 0),
            Vector3D(centre[2].x + (-p3p2.x*(_par->largeurRuelle/2)), centre[2].y + (-p3p2.y*(_par->largeurRuelle/2)), 0),
            _par);*/
/*
    b = Batiment( Vector3D( XY( ( (*this)[2] + p2p3*_par->largeurRuelle/2 ) ), 0),
            Vector3D( XY( batimentsCoin[3][3] ), 0),
            Vector3D( XY( batimentsCoin[3][2] ), 0),
            Vector3D( XY( ( batimentsCoin[2][2] + p2p3*_par->largeurRuelle/2 ) ), 0),
            _par);
    retour.merge( b.generate() );

    /*b = Batiment(Vector3D(notreQuadrangle[3].x, notreQuadrangle[3].y, 0),
            Vector3D(notreQuadrangle[0].x + (p0p3*(_par->largeurRuelle/2)).x, notreQuadrangle[0].y + (p0p3*(_par->largeurRuelle/2)).y, 0),
            Vector3D(centre0Bis.x, centre0Bis.y, 0),
            Vector3D(p2B3.x, p2B3.y, 0),
            _par);*/
/*
    b = Batiment( Vector3D( XY( (*this)[3] ), 0),
                Vector3D( XY( ( (*this)[0] + p0p3*_par->largeurRuelle/2 ) ), 0),
                Vector3D( XY( ( batimentsCoin[0][2] + p0p3*_par->largeurRuelle/2 ) ), 0),
                Vector3D( XY( batimentsCoin[3][3] ), 0),
                _par);
    retour.merge( b.generate() );



    return retour;

}*/

void PaterneQuad::determinationBatimentCoin(const int &indicePointCoin, Vector2D &point1Batiment, Vector2D &pointCentre, Vector2D &point3Batiment)
{
    /*
    point1  X----X  point2
            |    |
            |    |
    point0  X----X  point3
    */

    Quadrangle centreTmp = *this;
    centreTmp.shrink( _profondeurBatiment );

    pointCentre = centreTmp[indicePointCoin];

    Vector2D shrink = pointCentre - get(indicePointCoin);
    Vector2D pIpIm1 = get((indicePointCoin-1)%4) - get(indicePointCoin);
    Vector2D pIpIp1 = get((indicePointCoin+1)%4) - get(indicePointCoin);

    pIpIm1.normalise(); pIpIp1.normalise();

    // disposition des points en losange

    float dpIpIm1 = shrink.scalareProduct(pIpIm1);

    float dpIpIp1 = shrink.scalareProduct(pIpIp1);

    point1Batiment = get(indicePointCoin) + pIpIp1*dpIpIp1;
    point3Batiment = get(indicePointCoin) + pIpIm1*dpIpIm1;
}

Mesh PaterneQuad::remplissageCoin(const int& indicePointCoin, Vector2D& point1Batiment, Vector2D& pointCentre, Vector2D& point3Batiment)
{
    /*
    point1  X----X  point2
            |    |
            |    |
    point0  X----X  point3
    */

    Quadrangle centreTmp = *this;
    centreTmp.shrink( _profondeurBatiment );

    pointCentre = centreTmp[indicePointCoin];

    Vector2D shrink = pointCentre - get(indicePointCoin);
    Vector2D pIpIm1 = get((indicePointCoin-1)%4) - get(indicePointCoin);
    Vector2D pIpIp1 = get((indicePointCoin+1)%4) - get(indicePointCoin);

    pIpIm1.normalise(); pIpIp1.normalise();

    // disposition des points en losange

    float dpIpIm1 = shrink.scalareProduct(pIpIm1);

    float dpIpIp1 = shrink.scalareProduct(pIpIp1);

    point1Batiment = get(indicePointCoin) + pIpIp1*dpIpIp1;
    point3Batiment = get(indicePointCoin) + pIpIm1*dpIpIm1;


    if( angleEntreVecteur( (*this)[(indicePointCoin-1)%4]-(*this)[indicePointCoin],
                           (*this)[(indicePointCoin+1)%4]-(*this)[indicePointCoin]) < 75 ||
            angleEntreVecteur( (*this)[(indicePointCoin-1)%4]-(*this)[indicePointCoin],
                               (*this)[(indicePointCoin+1)%4]-(*this)[indicePointCoin]) > 135 ){
        return Mesh();
    }

    Batiment b = Batiment(Vector3D(get(indicePointCoin).x, get(indicePointCoin).y, 0),
                          Vector3D(point1Batiment.x, point1Batiment.y, 0),
                          Vector3D(pointCentre.x, pointCentre.y, 0),
                          Vector3D(point3Batiment.x, point3Batiment.y, 0),
                          _par);
    return b.generate();

}

Mesh PaterneQuad::remplissageBord(Vector2D &point1Batiment0, Vector2D &point2Batiment0, Vector2D &point2Batiment1, Vector2D &point3Batiment1)
{
    Mesh retour;

    float dExterne = distance( point1Batiment0, point3Batiment1);
    float dInterne = distance( point2Batiment0, point2Batiment1);

    Vector2D vecteurDirectionExt = (point3Batiment1 - point1Batiment0).normalised();
    Vector2D vecteurDirectionInt = (point2Batiment1 - point2Batiment0).normalised();

    if(dExterne > _par->minLargeurBatiment && dInterne > _par->minLargeurBatiment){

        int nbminBat = dExterne/_par->maxLargeurBatiment;
        int nbmaxBat = dExterne/_par->minLargeurBatiment;
        float aleatoire = 0;

        if(nbminBat != nbmaxBat){
            aleatoire = nbminBat + 1 + (rand()%(nbmaxBat-nbminBat));
        }
        else{
            aleatoire = nbminBat;
        }

        float largeurBatiment = dExterne / aleatoire;

        for(int i=0; i < aleatoire; i++){

            Vector2D p0 = point1Batiment0 + vecteurDirectionExt*i*largeurBatiment;
            Vector2D p1 = point1Batiment0 + vecteurDirectionExt*(i+1)*largeurBatiment;
            Vector2D p2 = point2Batiment0 + vecteurDirectionInt*distance(p1, point1Batiment0)*dInterne/dExterne;
            Vector2D p3 = point2Batiment0 + vecteurDirectionInt*distance(p0, point1Batiment0)*dInterne/dExterne;

            Batiment m = Batiment( Vector3D(XY(p0)), Vector3D(XY(p1)), Vector3D(XY(p2)), Vector3D(XY(p3)), _par );
            retour.merge(m.generate());
        }
    }
    return retour;
}

float PaterneQuad::coeffShrinkMax() const
{
    float retour = FLT_MAX;

    //calcule longeur coté (évité effet triangle ou angle négatif)
    for(int i=0; i<4; i++){
        float d = ( (*this)[i]-(*this)[(i+1)%4] ).getNorm();
        if(d < retour){
            retour = d;
        }
    }

    //calcule hauteur
    for(int i=0; i<4; i++){
        Vector2D perpendiculaireReference = ( (*this)[(i-1)%4]-(*this)[i] ).crossProduct().normalised();

        float d1 = perpendiculaireReference.dotProduct((*this)[(i+1)%4]-(*this)[i]);
        float d2 = perpendiculaireReference.dotProduct((*this)[(i+2)%4]-(*this)[i]);

        if(d1 < retour){
            retour = d1;
        }
        if(d2 < retour){
            retour = d2;
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

float PaterneQuad::angleEntreVecteur(const Vector2D &v1, const Vector2D &v2) const
{
    return 180*acos( v1.normalised().dotProduct( v2.normalised() ) )/3.14;
}
