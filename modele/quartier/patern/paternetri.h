#ifndef PATERNETRI_H
#define PATERNETRI_H

#include "modele/batiment/batiment.h"
#include "geometrie/Triangle.h"

class PaterneTri: public Interface_Ville, public Triangle
{
public:
    PaterneTri(){}
    PaterneTri(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, BatParameter *par) :
            Triangle(p0,p1,p2), _par(par){}

    BatParameter *_par;
    Mesh generate();

private:
    std::default_random_engine generator = std::default_random_engine();
    std::vector<Batiment> batiments;
    void faireTrotoir(Mesh &m);
    void faireSol(Mesh &m);
    Mesh paternConstruction() const;
	void split();
	std::pair<Vector2D, Vector2D> traiteCote(const Vector2D&, const Vector2D&, const Vector2D&);
    void traiteTrapeze(const Vector2D&, const Vector2D&, const Vector2D&, const Vector2D&);
    void traiteTrapezeObtusStart(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4);
    void traiteTrapezeObtusEnd(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4);
    void saveBatTrapeze(const Vector2D& pt1, const Vector2D& pt2, float depthPt1, float depthPt2, const Vector2D& dir_height);
    float findBatDepth(std::uniform_real_distribution<float> distri_BatDepth, float maxDepth);

    Mesh paternAngleTotal(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const;
    Mesh paternAngleCarre(int i, const Vector2D& v1, const Vector2D& v2) const;
    Mesh paternAngleCarre2(const Triangle& centre, int i, const Vector2D& v1, const Vector2D& v2) const;

    Mesh paternRebordAngle(int i, const Vector2D& v1, const Vector2D& v2, Vector2D& p2, Vector2D& p3, Vector2D& p4) const;
    Mesh paternRebord(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3, const Vector2D& p4, const Vector2D& v1) const;
};

#endif // PATERNETRI_H
