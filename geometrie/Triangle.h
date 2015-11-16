#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygone.h"

class Triangle: public Polygone
{
public:
    Triangle() {}

	Triangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2):
			p0(p0),	p1(p1),	p2(p2)
	{
    }


	Vector2D& operator[] (int i);
	Vector2D operator[] (int i) const;


    void shrink(float f);
    float area() const;
    float perimetre() const;

    int nbPoints() const;

	friend std::ostream& operator<<(std::ostream& out, const Triangle& t);


protected:
	Vector2D p0, p1, p2;

};


inline std::ostream& operator<<(std::ostream& out, const Triangle& t){
	return out << "{" << t.p0 << " " << t.p1 <<  " " << t.p2 << "}" <<std::endl;
}

#endif
