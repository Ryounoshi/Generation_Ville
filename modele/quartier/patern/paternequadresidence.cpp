#include "paternequadresidence.h"

Mesh PaterneQuadResidence::generate()
{

    Mesh m1;

    faireTrotoir(m1);
    faireSol(m1);

    Quadrangle centre = *this, notreQuadrangle = *this;
    centre.shrink(largeurBatiment);

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

