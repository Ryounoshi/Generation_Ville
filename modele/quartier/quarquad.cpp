#include "quarquad.h"

QuarQuad::QuarQuad()
{
}

QuarQuad::QuarQuad(const Vector2D &p0, const Vector2D &p1, const Vector2D &p2, const Vector2D& p3):
        Quadrangle(p0,p1,p2,p3)
{
}

std::pair<Quartier*,Quartier*> QuarQuad::decoupeSimple()
{
    std::pair<Quartier*,Quartier*> res;

    int type = rand()%4;
    //0 = a->c      1 = milieu ab->milieu cd    2 = b->d    3 = milieu bc->milieu da

    switch(type)
    {
        case 0:
            res.first = new QuarTri(get(0), get(1), get(2),0);
            res.second = new QuarTri(get(0), get(2), get(3),0);
            break;
        case 1:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2,
                        mcd = get(2) + (get(3)-get(2))/2;
                res.first = new QuarQuad(mab, get(1), get(2), mcd);
                res.second = new QuarQuad(mab, mcd, get(3), get(0));
            }
            break;

        case 2:
            res.first = new QuarTri(get(1), get(2), get(3),0);
            res.second = new QuarTri(get(1), get(3), get(0),0);
            break;
        case 3:
            {
                Vector2D mbc = get(1) + (get(2)-get(1))/2,
                        mda = get(3) + (get(0)-get(3))/2;
                res.first = new QuarQuad(mbc, get(2), get(3), mda);
                res.second = new QuarQuad(mbc, mda, get(0), get(1));
            }
            break;
    }
    return res;
}

std::pair<Quartier*,Quartier*> QuarQuad::decoupe()
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

    int typeDec = id2-id1;
    if(typeDec < 0)
        typeDec += 4;

    Vector2D newP1 = get(id1)+ Normalized(get(id1+1)-get(id1))*t;
    Vector2D newP2 = get(id2)+ Normalized(get(id2+1)-get(id2))*t2;
    Vector2D p = newP1, p2 = newP2;
    if(p.x < 0 || p.x > 1000 || p.y < 0 || p.y > 1000 ||
       p2.x < 0 || p2.x > 1000 || p2.y < 0 || p2.y > 1000)
        std::cout << p << std::endl;

    if(typeDec == 1)
    {
        res.first = new QuarTri(newP1,
                            get(id1+1),
                            newP2,0);

        res.second = new QuarPenta(newP1,
                              newP2,
                              get(id2+1),
                              get(id2+2),
                              get(id2+3));
    }
    else if(typeDec == 2)
    {
        res.first = new QuarQuad(newP1,
                             get(id1+1),
                             get(id1+2),
                             newP2);

        res.second = new QuarQuad(newP1,
                              newP2,
                              get(id2+1),
                              get(id2+2));
    }
    else
    {
        res.first = new QuarPenta(newP1,
                              get(id1+1),
                              get(id1+2),
                              get(id1+3),
                              newP2);

        res.second = new QuarTri(newP1,
                             newP2,
                             get(id1),0);
    }
    return res;
}

inline void QuarQuad::decoupePoint1(float perim, int& id1, float& t, float& distSeg)
{
    float   d0 = distance(p0,p1),
            d1 = distance(p1,p2),
            d2 = distance(p2,p3),
            d3 = distance(p3,p0);

    float r1 = rand()/(float)RAND_MAX;
    r1 *= perim;    //à quel position on place le premier point de découpe. plus de chance de découper le segment le plus long.

    if(r1 < d0)    {
        id1 = 0;
        distSeg = d0;
        t = r1;
    }
    else if(r1 < d0+d1)    {
        id1 = 1;
        distSeg = d1;
        t = r1-d0;
    }
    else if(r1 < d0+d1+d2)    {
        id1 = 2;
        distSeg = d2;
        t = r1-d0-d1;
    }
    else    {
        id1 = 3;
        distSeg = d3;
        t = r1-d0-d1-d2;
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

inline void QuarQuad::decoupePoint2(float perim2, int id1, int& id2, float& t2, float& distSeg2)
{
    float   d0 = distance(p0,p1),
            d1 = distance(p1,p2),
            d2 = distance(p2,p3),
            d3 = distance(p3,p0);

    float r2 = rand()/(float)RAND_MAX;
    r2 *= perim2;    //à quel position on place le premier point de découpe. plus de chance de découper le segment le plus long.
    switch (id1) {
    case 0:
        if(r2 < d1) {
            id2 = 1;
            distSeg2 = d1;
            t2 = r2;
        }
        else if(r2 < d1+d2) {
            id2 = 2;
            distSeg2 = d2;
            t2 = r2-d1;
        }
        else    {
            id2 = 3;
            distSeg2 = d3;
            t2 = r2-d1-d2;
        }
        break;
    case 1:
        if(r2 < d0) {
            id2 = 0;
            distSeg2 = d0;
            t2 = r2;
        }
        else if(r2 < d0+d2)    {
            id2 = 2;
            distSeg2 = d2;
            t2 = r2-d0;
        }
        else    {
            id2 = 3;
            distSeg2 = d3;
            t2 = r2-d0-d2;
        }
        break;
    case 2:
        if(r2 < d0) {
            id2 = 0;
            distSeg2 = d0;
            t2 = r2;
        }
        else if(r2 < d0+d1)    {
            id2 = 1;
            distSeg2 = d1;
            t2 = r2-d0;
        }
        else    {
            id2 = 3;
            distSeg2 = d3;
            t2 = r2-d0-d1;
        }
        break;

    default:
        if(r2 < d0) {
            id2 = 0;
            distSeg2 = d0;
            t2 = r2;
        }
        else if(r2 < d0+d1)    {
            id2 = 1;
            distSeg2 = d1;
            t2 = r2-d0;
        }
        else    {
            id2 = 2;
            distSeg2 = d2;
            t2 = r2-d0-d1;
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

void QuarQuad::shrink(float l)
{
    return Quadrangle::shrink(l);
}
float QuarQuad::area() const
{
    return Quadrangle::area();
}
float QuarQuad::perimetre() const
{
    return Quadrangle::perimetre();
}
