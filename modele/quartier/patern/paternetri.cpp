#include "paternetri.h"
#include <algorithm>
#include <array>


Mesh PaterneTri::generate()
{

    Mesh m1;
    faireTrotoir(m1);
    faireSol(m1);

    split();
    Mesh mBat;
    std::vector<Vector3D> v = getPoints3D();
    mBat.addTriangle(v[0],v[1],v[2]);
    for (Batiment& bat : batiments)
        mBat.merge(bat.generate());

    m1.merge(mBat);
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

constexpr float MIN_DIM_BAT = 5; // si modifié, doit quand même être > 0
constexpr float MAX_DIM_BAT = 15;

std::uniform_real_distribution<float> make_Unidistrib(float a, float b)
{
    return std::uniform_real_distribution<float>(a, b);
}

Vector3D to3D(const Vector2D& v)
{
    return Vector3D(v.x,v.y,0);
}

void PaterneTri::traiteTrapezeObtusStart(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4)
{
    /*
    *   p1       p4
    *    p2       p3
    */

    float hp = (to3D(p3 - p2) ^ to3D(p1 - p2)).getNorm() / (p3 - p2).getNorm();
    float triEndLength = (p4 - p3).scalareProduct(p2 - p3) / (p2 - p3).getNorm(); // longueur du projeté de p4 sur p3-p2
    Vector2D dir_coteTraite = Normalized(p3 - p2);
    Vector2D dir_height = Vector2D(dir_coteTraite.y,-dir_coteTraite.x);
    Vector2D waterMark = p2; // sera p2 ou après triangle
    auto distribution = make_Unidistrib(0, (p3 - waterMark).getNorm());
    do {
        float bat_length = distribution(generator);
        if (bat_length > (p3 - waterMark).getNorm() || bat_length > MAX_DIM_BAT) {
            bat_length = std::min((p3 - waterMark).getNorm(), MAX_DIM_BAT);
        }
        if (bat_length < MIN_DIM_BAT) {
            waterMark = waterMark + bat_length*dir_coteTraite;
            continue;
        }
        Vector2D wmark_candBat = waterMark + bat_length*dir_coteTraite;
        if (waterMark == p2)
        {
            if ((wmark_candBat-p2).getNorm() < (p3-p2).getNorm()-triEndLength) {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(wmark_candBat), to3D(wmark_candBat+hp*dir_height), _par));
                waterMark = wmark_candBat;
                continue;
            } else {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(p3), to3D(p4), _par));
                return;
            }
        } else {
            if ((wmark_candBat-p2).getNorm() < (p3-p2).getNorm()-triEndLength) {
                saveBatTrapeze(waterMark, wmark_candBat, hp, hp, dir_height);
                waterMark = wmark_candBat;
                continue;
            } else {
                batiments.push_back(Batiment(to3D(waterMark+hp*dir_height), to3D(waterMark), to3D(p3), to3D(p4), _par));
                return;
            }
        }
    } while ((waterMark - p3).getNorm() - MIN_DIM_BAT > 0);
}

void PaterneTri::traiteTrapezeObtusEnd(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4)
{
    /*
    *     p1       p4
    *    p2       p3
    */

    float hp = (to3D(p3 - p2) ^ to3D(p1 - p2)).getNorm() / (p3 - p2).getNorm();
    float triStartLength = (p1 - p2).scalareProduct(p3 - p2) / (p3 - p2).getNorm(); // longueur du projeté de p1 sur p2-p3
    Vector2D dir_coteTraite = Normalized(p3 - p2);
    Vector2D dir_height = Vector2D(dir_coteTraite.y,-dir_coteTraite.x);
    Vector2D waterMark = p2; // sera p2 ou après triangle
    auto distribution = make_Unidistrib(0, (p3 - waterMark).getNorm());
    do {
        float bat_length = distribution(generator);
        if (waterMark == p2 && bat_length <= triStartLength) { // on veut que des trapezes
            waterMark = p2 + triStartLength*dir_coteTraite;
            continue;
        }
        if (bat_length > (p3 - waterMark).getNorm() || bat_length > MAX_DIM_BAT) {
            bat_length = std::min((p3 - waterMark).getNorm(), MAX_DIM_BAT);
        }
        if (bat_length < MIN_DIM_BAT) {
            waterMark = waterMark + bat_length*dir_coteTraite;
            continue;
        }
        Vector2D wmark_candBat = waterMark + bat_length*dir_coteTraite;
        if (waterMark == p2)
        {
            if ((wmark_candBat-p2).getNorm() > (p3-p2).getNorm()) {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(p3), to3D(p4), _par));
                return;
            } else {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(wmark_candBat), to3D(wmark_candBat+hp*dir_height), _par));
                waterMark = wmark_candBat;
                continue;
            }
        } else {
            if ((wmark_candBat-p2).getNorm() > (p3-p2).getNorm()) {
                batiments.push_back(Batiment(to3D(waterMark+hp*dir_height), to3D(waterMark), to3D(p3), to3D(p4), _par));
                return;
            } else {
                saveBatTrapeze(waterMark, wmark_candBat, hp, hp, dir_height);
                waterMark = wmark_candBat;
                continue;
            }
        }
    } while ((waterMark - p3).getNorm() - MIN_DIM_BAT > 0);
}

void PaterneTri::traiteTrapeze(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4)
{
    if ((p1-p2).scalareProduct(p3-p2) < 0) {
        traiteTrapezeObtusStart(p1,p2,p3,p4);
        return;
    }
    if ((p4-p3).scalareProduct(p2-p3) < 0) {
        traiteTrapezeObtusEnd(p1,p2,p3,p4);
        return;
    }

    // cas gérés :
    /*
    *     p1     p4
    *    p2       p3
    *
    *    p1      p4
    *    p2       p3
    *
    *     p1      p4
    *    p2       p3
    */

    /*
                __/_________\__
             p1  /|         |\ p4
                / |         | \
               /  |         |  \
              /   |         |   \
          p2 /____|_________|____\ p3
             |####|         |####|
         triStartLength    triEndLength
    */
    /*
                __/_________\__
          p1     /  |        \ p4
                /   |         \
               /    | hp       \         bat_depth sera < hp mais aussi être assez petit pour que le sommet du batiment soit dans le quartier
              /     |           \
          p2 /______|____________\ p3
                 |           |
             waterMark  wmark_candBat  (les wmark sont des points potentiels de batiment et sont éloignés de bat_length)
    */

    float hp = (to3D(p3 - p2) ^ to3D(p1 - p2)).getNorm() / (p3 - p2).getNorm();
    float triStartLength = (p1 - p2).scalareProduct(p3 - p2) / (p3 - p2).getNorm(); // longueur du projeté de p1 sur p2-p3
    float triEndLength = (p4 - p3).scalareProduct(p2 - p3) / (p2 - p3).getNorm(); // longueur du projeté de p4 sur p3-p2
    Vector2D dir_coteTraite = Normalized(p3 - p2);
    Vector2D dir_height = Vector2D(dir_coteTraite.y,-dir_coteTraite.x);
    Vector2D waterMark = p2; // sera p2 ou après triangle
    auto distribution = make_Unidistrib(0, (p3 - waterMark).getNorm());
    do {
        float bat_length = distribution(generator);
        if (waterMark == p2 && bat_length <= triStartLength) { // on veut que des trapezes
            waterMark = p2 + triStartLength*dir_coteTraite;
            continue;
        }
        if (bat_length > (p3 - waterMark).getNorm() || bat_length > MAX_DIM_BAT) {
            bat_length = std::min((p3 - waterMark).getNorm(), MAX_DIM_BAT);
        }
        if (bat_length < MIN_DIM_BAT) {
            waterMark = waterMark + bat_length*dir_coteTraite;
            continue;
        }
        Vector2D wmark_candBat = waterMark + bat_length*dir_coteTraite;
        if (waterMark == p2)
        {
            if ((wmark_candBat-p2).getNorm() > (p3-p2).getNorm()-triEndLength) {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(p3), to3D(p4), _par));
                return;
            } else {
                batiments.push_back(Batiment(to3D(p1), to3D(p2), to3D(wmark_candBat), to3D(wmark_candBat+hp*dir_height), _par));
                waterMark = wmark_candBat;
                continue;
            }
        } else {
            if ((wmark_candBat-p2).getNorm() > (p3-p2).getNorm()) {
                batiments.push_back(Batiment(to3D(waterMark+hp*dir_height), to3D(waterMark), to3D(p3), to3D(p4), _par));
                return;
            } else {
                saveBatTrapeze(waterMark, wmark_candBat, hp, hp, dir_height);
                waterMark = wmark_candBat;
                continue;
            }
        }
    } while ((waterMark - p3).getNorm() - MIN_DIM_BAT > 0);
}

void PaterneTri::saveBatTrapeze(const Vector2D& pt1, const Vector2D& pt2, float depthPt1, float depthPt2, const Vector2D& dir_height)
{
    Vector2D point1 = pt1 + depthPt1 * dir_height;
    Vector2D point4 = pt2 + depthPt2 * dir_height;
    batiments.push_back(Batiment(to3D(point1), to3D(pt1), to3D(pt2), to3D(point4), _par));
}

void PaterneTri::split()
{
    std::array<Vector2D, 3> pts = { p0, p1, p2 };
    //shuffle(pts.begin(), pts.end(), generator); // je ne sais pas si les points d'origine ont un pattern
    /*
           p2
           |\
           | \
        p0 |__\ p1
    */

    //traite le coté pts[1]-pts[0]
    std::pair<Vector2D, Vector2D> tronq;
    if (orientation(pts[0], pts[1], pts[2]) < 0)
        tronq = traiteCote(pts[0], pts[1], pts[2]);
    else
        tronq = traiteCote(pts[1], pts[0], pts[2]);
    //tronq.first entre p0 et p2
    //tronq.second entre p1 et p2

    //traite le coté "pts[0]-pts[2]"
    Vector2D tmp = tronq.first;
    if (orientation(tronq.second, pts[2], tmp) < 0)
        tronq = traiteCote(tronq.second, pts[2], tmp);
    else
        tronq = traiteCote(pts[2], tronq.second, tmp);
    //tronq.first entre tmp et tronq.second précédent
    //tronq.second entre tmp et p2

    //traite le coté "pts[2]-pts[1]"
    if (orientation(tronq.second, tmp, tronq.first) < 0)
        traiteCote(tronq.second, tmp, tronq.first);
    else
        traiteCote(tmp, tronq.second, tronq.first);
}

float PaterneTri::findBatDepth(std::uniform_real_distribution<float> distri_BatDepth, float maxDepth)
{
    float bat_depth = distri_BatDepth(generator);
    if (bat_depth > maxDepth) bat_depth = maxDepth;
    return bat_depth;
}

std::pair<Vector2D, Vector2D> PaterneTri::traiteCote(const Vector2D& pp2, const Vector2D& pp1, const Vector2D& pp3)
{
    /*
            pp3
             /\
            /  \
       pp2 /____\ pp1
    */
    float height3 = (to3D(pp3 - pp1) ^ to3D(pp2 - pp1)).getNorm() / (pp2 - pp1).getNorm();
    if (height3 <= 2 * MIN_DIM_BAT) {
        return std::make_pair(pp2, pp1); // ou exclure la petite bande ?
    }
    auto distribution = make_Unidistrib(MIN_DIM_BAT, std::min(height3 - MIN_DIM_BAT, MAX_DIM_BAT));
    float hp = distribution(generator); // BatDepth max
    Vector2D lambda = pp3 + (pp2 - pp3)*(height3 - hp) / height3; // parallèle à pp2-pp1 et entre pp3 et pp2
    Vector2D mu = pp3 + (pp1 - pp3)*(height3 - hp) / height3; // parallèle à pp2-pp1 et entre pp3 et pp1
    Vector2D dir_coteTraite = Normalized(pp1-pp2);
    Vector2D dir_height = Vector2D(dir_coteTraite.y,-dir_coteTraite.x);
    if ((pp3-pp1).scalareProduct(dir_height) > 0)
        traiteTrapeze(lambda, pp2, pp1, mu);
    else
        traiteTrapeze(mu, pp1, pp2, lambda);
    return std::make_pair(lambda, mu);
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

Mesh PaterneTri::paternAngleCarre2(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const
{
    //Mesh retour;

    float larg = _par->minLargeurBatiment+(_par->maxLargeurBatiment-_par->minLargeurBatiment)*((rand()&0xFF)/0xFF);

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

    float larg = _par->minLargeurBatiment+(_par->maxLargeurBatiment-_par->minLargeurBatiment)*((rand()&0xFF)/0xFF);

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
    float larg = _par->minLargeurBatiment+(_par->maxLargeurBatiment-_par->minLargeurBatiment)*((rand()&0xFF)/(float)0xFF);

    Vector2D v1o = -v1.vectorProduct();
    float sc2 = (1/dot(v1o, v2))*larg;
    if(sc2 < larg)
        sc2 = larg;

    p4 = get(i)+v2*sc2;
    p3 = p4+v1*larg;

    float sc1 = dot(v1, p3-get(i));
    if(sc1 < larg)
        sc1 = larg;
    p2 = get(i)+v1*sc1;
    if(sc1 == larg)
        p3 = p2+v1o*larg;

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
    float larg = _par->minLargeurBatiment+(_par->maxLargeurBatiment-_par->minLargeurBatiment)*(((rand()&0xFF)/(float)0xFF));
    float rue = _par->largeurRuelle*(rand()&0x1);


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
