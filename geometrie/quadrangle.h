#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include "polygone.h"

class Quadrangle : public Polygone
{
    /*
     *     p2      p3
     *      X-----X
     *      |     |
     *      |     |
     *      X-----X
     *    p1       p4
     */
protected:
    Vector2D p0, p1, p2, p3;

public:
    Quadrangle() : p0(0,0), p1(0,0), p2(0,0), p3(0,0){}
    Quadrangle(const Vector2D& _p0, const Vector2D& _p1, const Vector2D& _p2, const Vector2D& _p3)
        : p0(_p0), p1(_p1), p2(_p2), p3(_p3){}


    Vector2D& operator[] (int i);
    Vector2D operator[] (int i) const;


    void shrink(float l);
    float area() const;
    float perimetre() const;


    int nbPoints() const;

    friend std::ostream& operator<<(std::ostream& out, const Quadrangle& q);

};


inline std::ostream& operator<<(std::ostream& out, const Quadrangle& q){
    return out << "{" << q.p0 << " " << q.p1 <<  " " << q.p2 << " " << q.p3 << "}" <<std::endl;
}


#endif // QUADRANGLE_H
