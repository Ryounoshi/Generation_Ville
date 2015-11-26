#include "quartri.h"
#include <array>
#include "geometrie/vector3d.h"
#include <algorithm>

QuarTri::QuarTri()
{
    generator = std::default_random_engine();
}

QuarTri::QuarTri(const Vector2D &p0, const Vector2D &p1, const Vector2D &p2, BatParameter *par):
        Quartier(par), Triangle(p0,p1,p2)
{
}

std::pair<Quartier*,Quartier*> QuarTri::decoupeSimple()
{
    std::pair<Quartier*,Quartier*> res;

    int type;
    //0 = a->milieu bc      1 = milieu ab->milieu bc    2 = milieu ab->c    3 = milieu ab->milieu ca    4 = b->milieu ca    5 = milieu bc->milieu ca


    Vector2D    sab = (get(1)-get(0)),
                sbc = (get(2)-get(1)),
                sca = (get(0)-get(2));

    float   ab = sab.getNorm(),
            bc = sbc.getNorm(),
            ca = sca.getNorm();
    float perim = (ab+bc+ca);
    float   c1 = 4*ab/perim,
            c2 = 4*bc/perim,
            c3 = 4*ca/perim;

    sab/=ab;
    sbc/=bc;
    sca/=ca;

    float   cab = 1+dot(sca,sab),
            abc = 1+dot(sab,sbc),
            bca = 1+dot(sbc,sca);

    c1*=c1*rand();
    c2*=c2*rand();
    c3*=c3*rand();
    cab*=cab*rand();
    abc*=abc*rand();
    bca*=bca*rand();

    float   t0 = (cab+c2),
            t1 = (c1+c2),
            t2 = (c1+bca),
            t3 = (c1+c3),
            t4 = (abc+c3),
            t5 = (c2+c3);

    if(t0>=t1 && t0>=t2 && t0>=t3 && t0>=t4 && t0>=t5)
        type = 0;
    if(t1>=t0 && t1>=t2 && t1>=t3 && t1>=t4 && t1>=t5)
        type = 1;
    if(t2>=t0 && t2>=t1 && t2>=t3 && t2>=t4 && t2>=t5)
        type = 2;
    if(t3>=t0 && t3>=t1 && t3>=t2 && t3>=t4 && t3>=t5)
        type = 3;
    if(t4>=t0 && t4>=t1 && t4>=t2 && t4>=t3 && t4>=t5)
        type = 4;
    else
        type = 5;


    switch(type)
    {
        case 0:
            {
                Vector2D mbc = get(1) + (get(2)-get(1))/2;
                res.first = new QuarTri(get(0), get(1), mbc,_par);
                res.second = new QuarTri(get(0), mbc, get(2),_par);
            }
            break;
        case 1:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2,
                        mbc = get(1) + (get(2)-get(1))/2;
                res.first = new QuarTri(mab, get(1), mbc,_par);
                res.second = new QuarQuad(mab, mbc, get(2), get(0), _par);
            }
            break;
        case 2:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2;
                res.first = new QuarTri(mab, get(1), get(2),_par);
                res.second = new QuarTri(get(0), mab, get(2),_par);
            }
            break;
        case 3:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2,
                        mca = get(2) + (get(0)-get(2))/2;
                res.first = new QuarQuad(mab, get(1), get(2), mca,_par);
                res.second = new QuarTri(mab, mca, get(0),_par);
            }
            break;
        case 4:
            {
                Vector2D mca = get(2) + (get(0)-get(2))/2;
                res.first = new QuarTri(get(1), get(2), mca,_par);
                res.second = new QuarTri(get(1), mca, get(0),_par);
            }
            break;

        case 5:
            {
                Vector2D mbc = get(1) + (get(2)-get(1))/2,
                        mca = get(2) + (get(0)-get(2))/2;
                res.first = new QuarTri(mbc, get(2), mca,_par);
                res.second = new QuarQuad(mbc, mca, get(0), get(1),_par);
            }
            break;
    }
    return res;
}


std::pair<Quartier*,Quartier*> QuarTri::decoupe()
{
    std::pair<Quartier*,Quartier*> res;
    float perim = this->perimetre();

    int id1;
    float t, distSeg;
    decoupePoint1(perim, id1, t, distSeg);

    float perim2 = perim-distSeg;

    int id2;
    float t2, distSeg2;
    decoupePoint2(perim2, id1, id2, t2, distSeg2);

    Vector2D newP1 = get(id1)+ Normalized(get(id1+1)-get(id1))*t;
    Vector2D newP2 = get(id2)+ Normalized(get(id2+1)-get(id2))*t2;
    Vector2D p = newP1, p2 = newP2;
    if(p.x < 0 || p.x > 1000 || p.y < 0 || p.y > 1000 ||
       p2.x < 0 || p2.x > 1000 || p2.y < 0 || p2.y > 1000)
        std::cout << p << std::endl;

    if(id2-id1 == 1 || id2-id1 == -2)
    {
        res.first = new QuarTri(newP1,
                            get(id1+1),
                            newP2,_par);

        res.second = new QuarQuad(newP1,
                              newP2,
                              get(id2+1),
                              get(id2+2), 0);
    }
    else
    {
        res.first = new QuarQuad(newP1,
                             get(id1+1),
                             get(id1+2),
                             newP2, 0);

        res.second = new QuarTri(newP1,
                             newP2,
                             get(id1),_par);
    }
    return res;
}

inline void QuarTri::decoupePoint1(float perim, int& id1, float& t, float& distSeg)
{
    float   d0 = distance(p0,p1),
            d1 = distance(p1,p2),
            d2 = distance(p2,p0);

    float r1 = rand()/(float)RAND_MAX;
    r1 *= perim;    //à quel position on place le premier point de découpe. plus de chance de découper le segment le plus long.
    if(r1 < d0)
    {
        id1 = 0;
        distSeg = d0;
        t = r1;
    }
    else if(r1 < d0+d1)
    {
        id1 = 1;
        distSeg = d1;
        t = r1-d0;
    }
    else
    {
        id1 = 2;
        distSeg = d2;
        t = r1-d0-d1;
    }


    if(distSeg < MIN_COTE)
        t = distSeg/2;
    else if(t < MIN_COTE)    {
        t = MIN_COTE;
    }
    else if(t > distSeg-MIN_COTE)  {
        t = distSeg-MIN_COTE;
    }


}

inline void QuarTri::decoupePoint2(float perim2, int id1, int& id2, float& t2, float& distSeg2)
{
    float   d0 = distance(p0,p1),
            d1 = distance(p1,p2),
            d2 = distance(p2,p0);

    float r2 = rand()/(float)RAND_MAX;
    r2 *= perim2;    //à quel position on place le premier point de découpe. plus de chance de découper le segment le plus long.
    switch (id1) {
    case 0:
        if(r2 < d1) {
            id2 = 1;
            distSeg2 = d1;
            t2 = r2;
        }
        else    {
            id2 = 2;
            distSeg2 = d2;
            t2 = r2-d1;
        }
        break;
    case 1:
        if(r2 < d0) {
            id2 = 0;
            distSeg2 = d0;
            t2 = r2;
        }
        else    {
            id2 = 2;
            distSeg2 = d2;
            t2 = r2-d0;
        }
        break;
    default:
        if(r2 < d0) {
            id2 = 0;
            distSeg2 = d0;
            t2 = r2;
        }
        else    {
            id2 = 1;
            distSeg2 = d1;
            t2 = r2-d0;
        }
        break;
    }

    if(distSeg2 < MIN_COTE)
        t2 = distSeg2/2;
    else if(t2 < MIN_COTE)    {
        t2 = MIN_COTE;
    }
    else if(t2 > distSeg2-MIN_COTE)  {
        t2 = distSeg2-MIN_COTE;
    }
}

void QuarTri::shrink(float l)
{
    Triangle::shrink(l);
}
float QuarTri::area() const
{
    return Triangle::area();
}
float QuarTri::perimetre() const
{
    return Triangle::perimetre();
}


constexpr float MIN_DIM_BAT = 5; // si modifié, doit quand même être > 0
constexpr float MAX_DIM_BAT = 25;

std::uniform_real_distribution<float> make_Unidistrib(float a, float b)
{
    return std::uniform_real_distribution<float>(a, b);
}



std::vector<Vector2D> QuarTri::getPoints() const
{
    return Polygone::getPoints();
}
std::vector<Vector3D> QuarTri::getPoints3D() const
{
    return Polygone::getPoints3D();
}

Mesh QuarTri::generate()
{
    PaterneTri pQR = PaterneTri( this->get(0), this->get(1), this->get(2), _par);
    return pQR.generate();
    /*
    split();
    Mesh m;
    std::vector<Vector3D> v = getPoints3D();
    m.addTriangle(v[0],v[1],v[2]);
    for (Batiment& bat : batiments)
        m.merge(bat.generate());

    return m;
    */
}


bool QuarTri::quartierCorrect() const
{
    if(orientation(get(0),get(1),get(2)) <= 0)
        return false;

    float cote2 = MIN_COTE*MIN_COTE;
    if(distance2(get(0),get(1)) < cote2 || distance2(get(1),get(2)) < cote2 || distance2(get(2),get(0)) < cote2)
        return false;
    return true;
}
