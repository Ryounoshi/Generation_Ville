#include "polygone.h"

Polygone::Polygone()
{
}

void Polygone::shrinkPoly(int nb, float l)
{
    if(l == 0)
        return;

    Vector2D tab[nb];

    for(int i = 0;	i < nb;	i++)
    {
        Vector2D v1 = Orthogonal(get(i)-get(i+1)).normalise();
        Vector2D v2 = Orthogonal(get(i-1)-get(i)).normalise();

        Vector2D v = (v1+v2)/2;	//quand on augmente de 1 sur v1 ou v2, on augment de v.norm() sur le v.

        tab[i] = get(i)+Normalized(v)*(l/v.getNorm());
    }
    for(int i = 0;	i < nb;	i++)
         set(i, tab[i]);
}

Vector2D& Polygone::get(int i)
{
    return (*this)[i];
}
Vector2D Polygone::get(int i) const
{
    return (*this)[i];
}

void Polygone::set(int i, const Vector2D& p)
{
    (*this)[i] = p;
}

std::vector<Vector2D> Polygone::getPoints() const
{
    std::vector<Vector2D> res;
    int taille = nbPoints();
    res.reserve(taille);
    for(int i = 0;  i < taille; i++)
        res.push_back(get(i));
    return res;
}

std::vector<Vector3D> Polygone::getPoints3D() const
{
    std::vector<Vector3D> res;
    int taille = nbPoints();
    res.reserve(taille);
    for(int i = 0;  i < taille; i++)
        res.push_back(Vector3D(XY(get(i)),0));
    return res;
}

/*********************************************************************************************/

//préfère le mettre dans un fichier de calcul à part.
float areaTriangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2)
{
    Vector2D ab = p1-p0;
    Vector2D ac = p2-p0;
    float base = ab.getNorm();

    float d = ab.scalareProduct(ac)/base;
    float h = sqrt(ac.getNorm2()-d*d);
    return h*base*0.5;
}

/**
 * A=1/2*d1*d2*sin(alpha)
 *
 * http://onlinemschool.com/math/formula/area/#h5
 */
float areaQuad(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2, const Vector2D& p3)
{
    Vector2D d1 = p2-p0, d2 = p3-p1;
    float norm1 = d1.getNorm();
    float norm2 = d2.getNorm();
    d1.normalise();
    d2.normalise();
    float alpha = acosf(d1.scalareProduct(d2));
    return (norm1*norm2*sin(alpha))*0.5f;
}
