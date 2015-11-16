#include "box.h"


Box::Box()  : min(Vector3D(FLT_MAX,FLT_MAX,FLT_MAX)), max(Vector3D(FLT_MIN,FLT_MIN,FLT_MIN))
{
}

Box::Box(const Vector3D &_min, const Vector3D &_max)    :   min(_min),  max(_max)
{
}

Box::Box(const std::vector<Vector3D>& points)
{
    parcourtPoints(points);
}


void Box::updatePoint(const Vector3D& p)
{
    update(p);
}

bool Box::inOut(const Vector3D& p) const
{
    if(p.x < min.x)
        return false;
    if(p.x > max.x)
        return false;

    if(p.y < min.y)
        return false;
    if(p.y > max.y)
        return false;

    if(p.z < min.z)
        return false;
    if(p.z > max.z)
        return false;

    return true;
}


bool Box::intersect(const Rayon &r, float &distanceMin, float &distanceMax) const
{
    if(this->inOut(r.getOrigine()))  {
        distanceMin = 0;
        distanceMax = intersectIn(r);
        return true;
    }

    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    float div;

    if(r.getDirection().x == 0)    {
        tmin = FLT_MIN;
        tmax = FLT_MAX;
    }
    else if(r.getDirection().x > 0)    {
        div = 1 / r.getDirection().x;
        tmin = (min.x - r.getOrigine().x) * div;
        tmax = (max.x - r.getOrigine().x) * div;
    }
    else    {
        div = 1 / r.getDirection().x;
        tmin = (max.x - r.getOrigine().x) * div;
        tmax = (min.x - r.getOrigine().x) * div;
    }

    if(r.getDirection().y == 0)    {
        tymin = FLT_MIN;
        tymax = FLT_MAX;
    }
    else if(r.getDirection().y >= 0)    {
        div = 1 / r.getDirection().y;
        tymin = (min.y - r.getOrigine().y) * div;
        tymax = (max.y - r.getOrigine().y) * div;
    }
    else    {
        div = 1 / r.getDirection().y;
        tymin = (max.y - r.getOrigine().y) * div;
        tymax = (min.y - r.getOrigine().y) * div;
    }

    if( (tmin > tymax) || (tymin > tmax) )
        return false;

    if(tymin > tmin)
        tmin = tymin;

    if(tymax < tmax)
        tmax = tymax;


    if(r.getDirection().z == 0)    {
        tzmin = FLT_MIN;
        tzmax = FLT_MAX;
    }
    else if(r.getDirection().z > 0)    {
        div = 1 / r.getDirection().z;
        tzmin = (min.z - r.getOrigine().z) * div;
        tzmax = (max.z - r.getOrigine().z) * div;
    }
    else    {
        div = 1 / r.getDirection().z;
        tzmin = (max.z - r.getOrigine().z) * div;
        tzmax = (min.z - r.getOrigine().z) * div;
    }

    if( (tmin > tzmax) || (tzmin > tmax) )
        return false;

    if(tzmin > tmin)
        tmin = tzmin;

    if(tzmax < tmax)
        tmax = tzmax;

    if(tmin>=0)
        distanceMin = tmin;

    if(tmax>0)
        distanceMax = tmax;

    return true;
}



inline float Box::intersectIn(const Rayon& r) const
{
    float tmax, tymax, tzmax;

    if(r.getDirection().x == 0)
        tmax = FLT_MAX;
    else if(r.getDirection().x > 0)
        tmax = (max.x - r.getOrigine().x) / r.getDirection().x;
    else
        tmax = (min.x - r.getOrigine().x) / r.getDirection().x;

    if(r.getDirection().y == 0)
        tymax = FLT_MAX;
    else if(r.getDirection().y >= 0)
        tymax = (max.y - r.getOrigine().y) / r.getDirection().y;
    else
        tymax = (min.y - r.getOrigine().y) / r.getDirection().y;

    if(tymax < tmax)
        tmax = tymax;


    if(r.getDirection().z == 0)
        return tmax;
    else if(r.getDirection().z > 0)
        tzmax = (max.z - r.getOrigine().z) / r.getDirection().z;
    else
        tzmax = (min.z - r.getOrigine().z) / r.getDirection().z;

    if(tzmax < tmax)
        return tzmax;
    return tmax;
}


/**********************inline********************/

inline void Box::setDefaultBox()
{
    min = Vector3D(FLT_MAX,FLT_MAX,FLT_MAX);
    max = Vector3D(FLT_MIN,FLT_MIN,FLT_MIN);
}

inline void Box::update(const Vector3D& p)
{
    updateMin(p);
    updateMax(p);
}

inline void Box::updateMin(const Vector3D& p)
{
    if(p.x < min.x)
        min.x = p.x;

    if(p.y < min.y)
        min.y = p.y;

    if(p.z < min.z)
        min.z = p.z;
}

inline void Box::updateMax(const Vector3D& p)
{
    if(p.x > max.x)
        max.x = p.x;

    if(p.y > max.y)
        max.y = p.y;

    if(p.z > max.z)
        max.z = p.z;
}

inline void Box::parcourtPoints(const std::vector<Vector3D>& points)
{
    if(points.empty())
        setDefaultBox();
    else if(points.size() == 1)
    {
        min = points[0];
        max = points[0];
    }
    else
    {
        std::vector<Vector3D>::const_iterator it = points.begin();
        min = *it;
        max = points[points.size()-1];

        ++it;
        for(;  it != points.end()-1; ++it)
            update(*it);
    }
}

float Box::diffZ() const
{
    return max.z-min.z;
}

void Box::merge(const Box& box2)
{
    updateMin(box2.min);
    updateMax(box2.max);
}


void Box::operator+=(const Vector3D& t)
{
    min += t;
    max += t;
}


/**************************************************************************/

float Box::distance(const Vector3D &p) const
{
    float dx = std::max(std::max(0.f, min.x - p.x), p.x - max.x); //soit en dessous de max, soit en dessus de min, soit entre les deux (dans ce cas, distance = 0)
    float dy = std::max(std::max(0.f, min.y - p.y), p.y - max.y);
    float dz = std::max(std::max(0.f, min.z - p.z), p.z - max.z);
    return sqrt(dx*dx + dy*dy + dz*dz);
}


Vector3D Box::getNormal(const Vector3D& p) const
{
    Vector3D cote = max-min; //taille des coté
    Vector3D centre(min+cote*0.5f);
    Vector3D n(p-centre);
    n /= cote;  //la normal point dans la direction du cote le plus proche du point
    Vector3D na = Vector3D(abs(n.x), abs(n.y), abs(n.z));

    int dir = 0;    //la normale est dans la direction de l'axe X
    if(na.x < na.y)
    {
        if(na.y < na.z)
            dir = 2;    //la normale est dans la direction de l'axe Z
        else
            dir = 1;    //la normale est dans la direction de l'axe Y
    }
    else if(na.x < na.z)
        dir = 2;        //la normale est dans la direction de l'axe Z

    switch(dir)
    {
    case 0: return (n.x < 0   ?   Vector3D(-1,0,0)    :   Vector3D(1,0,0));
    case 1: return (n.y < 0   ?   Vector3D(0,-1,0)    :   Vector3D(0,1,0));
    case 2: return (n.z < 0   ?   Vector3D(0,0,-1)    :   Vector3D(0,0,1));
    }
    return Vector3D(0,0,0);
}
