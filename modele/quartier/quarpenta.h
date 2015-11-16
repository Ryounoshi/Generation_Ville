#ifndef QUARPENTA_H
#define QUARPENTA_H

#include "quartier.h"

class QuarPenta: public Quartier, public Pentagone
{
public:

    QuarPenta();
    QuarPenta(const Vector2D &p0, const Vector2D &p1, const Vector2D &p2, const Vector2D& p3, const Vector2D& p4, BatParameter* par);


    std::pair<Quartier*,Quartier*> decoupeSimple();
    std::pair<Quartier*,Quartier*> decoupe();

    void split();


    void shrink(float f);
    float area() const;
    float perimetre() const;


    std::vector<Vector2D> getPoints() const;
    std::vector<Vector3D> getPoints3D() const;

private:
    inline void decoupePoint1(float perim, int& id1, float& t, float& distSeg);
    inline void decoupePoint2(float perim2, int id1, int& id2, float& t2, float& distSeg2);

};

#endif // QUARPENTA_H
