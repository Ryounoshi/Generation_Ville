#include "quartri.h"
#include <array>
#include "geometrie/vector3d.h"
#include <algorithm>

QuarTri::QuarTri()
{
    generator = std::default_random_engine(4546);
}

QuarTri::QuarTri(const Vector2D &p0, const Vector2D &p1, const Vector2D &p2, BatParameter *par):
        Quartier(par), Triangle(p0,p1,p2)
{
}

std::pair<Quartier*,Quartier*> QuarTri::decoupeSimple()
{
    std::pair<Quartier*,Quartier*> res;

    int type = rand()%6;
    //0 = a->milieu bc      1 = milieu ab->milieu bc    2 = milieu ab->c    3 = milieu ab->milieu ca    4 = b->milieu ca    5 = milieu bc->milieu ca
    float d0 = distance(p0,p1),
          d1 = distance(p1,p2),
          d2 = distance(p2,p0);
    float perim = perimetre();
    while((d0 < perim/4 && (type == 1 || type == 2 || type == 3)) ||
          (d1 < perim/4 && (type == 0 || type == 1 || type == 5)) ||
          (d2 < perim/4 && (type == 3 || type == 4 || type == 5)))
        type = rand()%6;

    switch(type)
    {
        case 0:
            {
                Vector2D mbc = get(1) + (get(2)-get(1))/2;
                res.first = new QuarTri(get(0), get(1), mbc, _par);
                res.second = new QuarTri(get(0), mbc, get(2), _par);
            }
            break;
        case 1:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2,
                        mbc = get(1) + (get(2)-get(1))/2;
                res.first = new QuarTri(mab, get(1), mbc, _par);
                res.second = new QuarQuad(mab, mbc, get(2), get(0), _par);
            }
            break;
        case 2:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2;
                res.first = new QuarTri(mab, get(1), get(2), _par);
                res.second = new QuarTri(get(0), mab, get(2), _par);
            }
            break;
        case 3:
            {
                Vector2D mab = get(0) + (get(1)-get(0))/2,
                        mca = get(2) + (get(0)-get(2))/2;
                res.first = new QuarQuad(mab, get(1), get(2), mca, _par);
                res.second = new QuarTri(mab, mca, get(0), _par);
            }
            break;
        case 4:
            {
                Vector2D mca = get(2) + (get(0)-get(2))/2;
                res.first = new QuarTri(get(1), get(2), mca,0);
                res.second = new QuarTri(get(1), mca, get(0), _par);
            }
            break;
        case 5:
            {
                Vector2D mbc = get(1) + (get(2)-get(1))/2,
                        mca = get(2) + (get(0)-get(2))/2;
                res.second = new QuarTri(mbc, get(2), mca, _par);
                res.first = new QuarQuad(mbc, mca, get(0), get(1), _par);
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
    #ifndef QT_NO_DEBUG
        Vector2D p = newP1, p2 = newP2;
        if(p.x < 0 || p.x > 1000 || p.y < 0 || p.y > 1000 ||
           p2.x < 0 || p2.x > 1000 || p2.y < 0 || p2.y > 1000)
            std::cout << p << std::endl;
    #endif

    if(id2-id1 == 1 || id2-id1 == -2)
    {
        res.first = new QuarTri(newP1,
                            get(id1+1),
                            newP2, _par);

        res.second = new QuarQuad(newP1,
                              newP2,
                              get(id2+1),
                              get(id2+2), _par);
    }
    else
    {
        res.first = new QuarQuad(newP1,
                             get(id1+1),
                             get(id1+2),
                             newP2, _par);

        res.second = new QuarTri(newP1,
                             newP2,
                             get(id1), _par);
    }
    return res;
}

inline void QuarTri::decoupePoint1(float perim, int& id1, float& t, float& distSeg)
{
    float   d0 = distance(p0,p1),
            d1 = distance(p1,p2),
            d2 = distance(p2,p0);

    float r1 = (rand()%65536)/65536.0;
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

    float r2 = (rand()%65536)/65536.0;
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


constexpr float MIN_DIM_BAT = 10; // si modifié, doit quand même être > 0
constexpr float MAX_DIM_BAT = 25;

std::uniform_real_distribution<float> make_Unidistrib(float a, float b)
{
    return std::uniform_real_distribution<float>(a, b);
}

Vector3D to3D(const Vector2D& v)
{
    return Vector3D(v.x,v.y,0);
}

void QuarTri::split()
{
    std::array<Vector2D, 3> pts = { p0, p1, p2 };
    shuffle(pts.begin(), pts.end(), generator); // je ne sais pas si les points d'origine ont un pattern
    /*
          pp3
           |\
           | \
       pp2 |__\ pp1
    */

    //traite le coté pts[1]-pts[0]
    std::pair<Vector2D, Vector2D> tronq = traiteCote(pts[1], pts[0], pts[2]);

    //traite le coté "pts[0]-pts[2]"
    Vector2D tmp = tronq.first;
    tronq = traiteCote(tronq.second, pts[2], tmp);

    //traite le coté "pts[2]-pts[1]"
    traiteCote(tronq.second, tmp, tronq.first);
}

/**
 * Ne gère que les triangles acutangles
 */
std::pair<Vector2D, Vector2D> QuarTri::traiteCote(const Vector2D& pp2, const Vector2D& pp1, const Vector2D& pp3)
{
    /*
            pp3
             /\
            /  \
       pp2 /____\ pp1
    */
    float height3 = ((pp3 - pp1) / (pp2 - pp1)).getNorm() / (pp2 - pp1).getNorm();
    if (height3 <= 2 * MIN_DIM_BAT)
        return std::make_pair(pp1, pp2); // ou exclure la petite bande ?
    auto distribution = make_Unidistrib(MIN_DIM_BAT, height3 - MIN_DIM_BAT);
    float hp = distribution(generator); // BatDepth max
    auto distri_BatDepth = make_Unidistrib(MIN_DIM_BAT, hp*1.5f);
    Vector2D lambda = pp3 + (pp2 - pp3)*(height3 - hp) / height3; // parallèle à pp2-pp1 et entre pp3 et pp2
    Vector2D mu = pp3 + (pp1 - pp3)*(height3 - hp) / height3; // parallèle à pp2-pp1 et entre pp3 et pp1
    float triStartLength = (lambda - pp2).scalareProduct(pp2 - pp1) / (pp2 - pp1).getNorm(); // longueur du projeté de lambda sur pp2-pp1
    float triEndLength = (mu - pp1).scalareProduct(pp1 - pp2) / (pp2 - pp1).getNorm(); // longueur du projeté de mu sur pp2-pp1
    /*
                 __/_________\__
          lambda  /|         |\ mu
                 / |         | \
                /  |         |  \
               /   |         |   \
          pp2 /____|_________|____\ pp1
              |####|         |####|
          triStartLength    triEndLength
    */
    Vector2D waterMark = pp2;
    Vector2D dir_coteTraite = Normalized(pp1 - pp2);
    Vector2D dir_height = Normalized(Vector2D(pp1.y - pp2.y, pp2.x - pp1.x));
    do {
        /*
                     __/_________\__
              lambda  /  |        \ mu
                     /   |         \
                    /    | hp       \         bat_depth sera < hp mais aussi être assez petit pour que le sommet du batiment soit dans le quartier
                   /     |           \
              pp2 /______|____________\ pp1
                      |           |
                  waterMark  wmark_candBat  (les wmark sont des points potentiels de batiment et sont éloignés de bat_length)
        */
        distribution = make_Unidistrib(0, (waterMark - pp1).getNorm());
        float bat_length = distribution(generator);
        Vector2D wmark_candBat = waterMark + bat_length*dir_coteTraite; // determinera si batiment ou rien
        if (bat_length >= MIN_DIM_BAT) {
            //
            // Cas de début
            if (waterMark == pp2) {
                // Cas où wmark_candBat est dans le premier triangle
                if (bat_length <= triStartLength) {
                    if (height3*bat_length / triStartLength < MIN_DIM_BAT) {
                        waterMark = wmark_candBat;
                        continue;
                    }
                    // tous les cas ne sont pas gérés ici (pas de batiment triangles)
                    // mais si bat_depth == height3*bat_length/triStartLength alors point1 == point4
                    float bat_depth = make_Unidistrib(MIN_DIM_BAT, height3*bat_length / triStartLength)(generator);
                    Vector2D point1 = pp3 + (pp2 - pp3)*(height3 - bat_depth) / height3;
                    Vector2D point4 = wmark_candBat + bat_depth * dir_height;
                    batiments.push_back(Batiment(to3D(point1), to3D(pp2), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
                // Cas où wmark_candBat est dans le rectangle
                else if (bat_length <= (pp2 - pp1).getNorm() - triEndLength)
                {
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    Vector2D point1 = pp3 + (pp2 - pp3)*(height3 - bat_depth) / height3;
                    Vector2D point4 = wmark_candBat + bat_depth * dir_height;
                    batiments.push_back(Batiment(to3D(point1), to3D(pp2), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
                // Cas où wmark_candBat est dans le dernier triangle
                else if (bat_length < (pp2 - pp1).getNorm())
                {
                    // potentiellemnt pentagone
                }
                // Cas où wmark_candBat est le sommet de fin
                else {
                    // le batiment occupe tout le coté
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    Vector2D point1 = pp3 + (pp2 - pp3)*(height3 - bat_depth) / height3;
                    Vector2D point4 = pp3 + (pp1 - pp3)*(height3 - bat_depth) / height3;
                    batiments.push_back(Batiment(to3D(point1), to3D(pp2), to3D(pp1), to3D(point4), 1.f, _par));
                }
            }
            //
            // Cas où waterMark est dans le premier triangle
            else if ((waterMark - pp2).getNorm() < triStartLength)
            {
                // Cas où wmark_candBat est dans le premier triangle
                if ((wmark_candBat - pp2).getNorm() < triStartLength)
                {
                    if (height3*(waterMark - pp2).getNorm() / triStartLength < MIN_DIM_BAT) {
                        waterMark = wmark_candBat;
                        continue;
                    }
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    // pas de pentagone donc je choisis trapèze à la place
                    bat_depth = std::min(bat_depth, (wmark_candBat - pp2).getNorm() / triStartLength*hp);
                    Vector2D point4 = wmark_candBat + bat_depth * dir_height;
                    bat_depth = std::min(bat_depth, (waterMark - pp2).getNorm() / triStartLength*hp);
                    Vector2D point1 = waterMark + bat_depth * dir_height;
                    batiments.push_back(Batiment(to3D(point1), to3D(waterMark), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
                // Cas où wmark_candBat est dans le rectangle
                else if ((wmark_candBat - pp2).getNorm() <= (pp2 - pp1).getNorm() - triEndLength)
                {
                    // potentiellemnt pentagone
                }
                // Cas où wmark_candBat est dans le dernier triangle
                else if (wmark_candBat != pp1)
                {
                    // potentiellemnt hexagone
                }
                // Cas où wmark_candBat est le sommet de fin
                else {
                    // potentiellemnt pentagone
                }
            }
            //
            // Cas où waterMark est dans le rectangle
            else if ((waterMark - pp2).getNorm() < (pp2 - pp1).getNorm() - triEndLength)
            {
                // Cas où wmark_candBat est dans le rectangle
                if ((wmark_candBat - pp2).getNorm() < (pp2 - pp1).getNorm() - triEndLength)
                {
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    Vector2D point1 = waterMark + bat_depth * dir_height;
                    Vector2D point4 = wmark_candBat + bat_depth * dir_height;
                    batiments.push_back(Batiment(to3D(point1), to3D(waterMark), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
                // Cas où wmark_candBat est dans le dernier triangle
                else if (wmark_candBat != pp1)
                {
                    // potentiellemnt pentagone
                }
                // Cas où wmark_candBat est le sommet de fin
                else
                {
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    Vector2D point1 = waterMark + bat_depth * dir_height;
                    Vector2D point4 = pp3 + (pp1 - pp3)*(height3 - bat_depth) / height3;
                    batiments.push_back(Batiment(to3D(point1), to3D(waterMark), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
            }
            //
            // Cas où waterMark est dans le dernier triangle
            else {
                // Cas où wmark_candBat est dans le dernier triangle
                if (wmark_candBat != pp1)
                {
                    if (height3*(waterMark - pp3).getNorm() / triEndLength < MIN_DIM_BAT) {
                        waterMark = wmark_candBat;
                        continue;
                    }
                    float bat_depth = distri_BatDepth(generator);
                    if (bat_depth > hp) bat_depth = hp;
                    // pas de pentagone donc je choisis trapèze à la place
                    bat_depth = std::min(bat_depth, (waterMark - pp1).getNorm() / triEndLength*hp);
                    Vector2D point1 = wmark_candBat + bat_depth * dir_height;
                    bat_depth = std::min(bat_depth, (wmark_candBat - pp1).getNorm() / triEndLength*hp);
                    Vector2D point4 = waterMark + bat_depth * dir_height;
                    batiments.push_back(Batiment(to3D(point1), to3D(waterMark), to3D(wmark_candBat), to3D(point4), 1.f, _par));
                }
                // Cas où wmark_candBat est le sommet de fin
                else
                {
                    // potentiellemnt triangle
                }
            }
        }
        waterMark = wmark_candBat;
    } while ((waterMark - pp2).getNorm() < (pp2 - pp1).getNorm() - MIN_DIM_BAT);
    return std::make_pair(lambda, mu);
}


std::vector<Vector2D> QuarTri::getPoints() const
{
    return Polygone::getPoints();
}
std::vector<Vector3D> QuarTri::getPoints3D() const
{
    return Polygone::getPoints3D();
}
