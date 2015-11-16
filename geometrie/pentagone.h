#ifndef PENTAGONE_H
#define PENTAGONE_H

#include "polygone.h"

class Pentagone : public Polygone
{
public:

    Pentagone() {}
    Pentagone(const Vector2D& _p0, const Vector2D& _p1, const Vector2D& _p2, const Vector2D& _p3, const Vector2D& _p4)
        : p0(_p0), p1(_p1), p2(_p2), p3(_p3), p4(_p4){}


    Vector2D& operator[] (int i);
    Vector2D operator[] (int i) const;


    void shrink(float f);
    float area() const;
    float perimetre() const;

    int nbPoints() const;

    friend std::ostream& operator<<(std::ostream& out, const Pentagone& p);



protected:
    Vector2D p0, p1, p2, p3, p4;
};


inline std::ostream& operator<<(std::ostream& out, const Pentagone& p){
    return out << "{" << p.p0 << " " << p.p1 << " " << p.p2 <<  " " << p.p3 << " " << p.p4 << "}" <<std::endl;
}

#endif // PENTAGONE_H
