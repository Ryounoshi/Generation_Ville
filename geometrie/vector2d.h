#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>
#include <iostream>


#define XY(p)   p.x, p.y
#define XY0(p)  p.x, p.y, 0

//! \class Vector2D Vector2D.h
//! \brief Cette classe définit des vecteurs et des sommets dans l'espace.
class Vector2D
{
public:
    float x,y; //!< Coordinates

    Vector2D(): Vector2D(0,0) { } //! Empty
    Vector2D(float a, float b): x(a), y(b)  {}
    Vector2D(const Vector2D& v): x(v.x), y(v.y)  {}
    Vector2D(Vector2D&& v): x(v.x), y(v.y)  {}

    void operator=(const Vector2D& v) {     x=v.x;  y=v.y;    }
    void operator=(Vector2D&& v) {          x=v.x;  y=v.y;    }

    void set(float a, float b);

    float scalareProduct(const Vector2D & v) const;
    float dotProduct(const Vector2D& v) const;

    //c'est l'orthogonal
    Vector2D vectorProduct() const;
    Vector2D crossProduct() const;

    Vector2D negate() const;

    float getNorm() const;
    float getNorm2() const;

    void normalise();
    Vector2D normalised() const;

    // Functions to access Vector2D class components
    float& operator[] (int i);
    float operator[] (int i) const;

    // Unary operators
    Vector2D operator+ () const;
    Vector2D operator- () const;

    // Boolean functions
    int operator==(const Vector2D&) const;
    int operator!=(const Vector2D&) const;
    int operator<(const Vector2D&) const;
    int operator>(const Vector2D&) const;
    int operator<=(const Vector2D&) const;
    int operator>=(const Vector2D&) const;

    // Assignment operators
    void operator+= (const Vector2D&);
    void operator+= (float);
    void operator-= (const Vector2D&);
    void operator-= (float);
    void operator*= (const Vector2D&);
    void operator*= (float);
    void operator/= (const Vector2D&);
    void operator/= (float);


    // Binary operators
    friend Vector2D operator+ (const Vector2D&, const Vector2D&);
    friend Vector2D operator+ (const Vector2D&, float);
    friend Vector2D operator+ (float, const Vector2D&);
    friend Vector2D operator- (const Vector2D&, const Vector2D&);
    friend Vector2D operator- (const Vector2D&, float);
    friend Vector2D operator- (float, const Vector2D&);

    friend Vector2D operator* (const Vector2D&, const Vector2D&);
    friend Vector2D operator* (const Vector2D&, float);
    friend Vector2D operator* (float, const Vector2D&);
    friend Vector2D operator/ (const Vector2D&, const Vector2D&);
    friend Vector2D operator/ (const Vector2D&, float);
    friend Vector2D operator/ (float, const Vector2D&);


    friend Vector2D min(const Vector2D&,const Vector2D&);
    friend Vector2D max(const Vector2D&,const Vector2D&);


    friend float dot(const Vector2D& u, const Vector2D& v);
    friend Vector2D Orthogonal(const Vector2D&);

    // Norm
    friend float Norm(const Vector2D&);
    friend float Norm2(const Vector2D&);
    friend Vector2D Normalized(const Vector2D&);

    friend float distance(const Vector2D& u, const Vector2D& v);
    friend float distance2(const Vector2D& u, const Vector2D& v);

    friend Vector2D Random2D();
    friend float orientation(const Vector2D& a, const Vector2D& b, const Vector2D& c);


    friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
};

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

// Binary operators
/*Vector2D operator+ (const Vector2D& u, const Vector2D& v);
Vector2D operator- (const Vector2D& u, const Vector2D& v);
Vector2D operator* (const Vector2D& u, const Vector2D& v);
Vector2D operator* (const Vector2D& u,float a);
Vector2D operator* (float a, const Vector2D& v);
Vector2D operator/ (const Vector2D& u, const Vector2D& v);
Vector2D operator/ (const Vector2D& u, float a);

// Boolean functions
int operator== (const Vector2D& u,const Vector2D& v);
int operator!= (const Vector2D& u,const Vector2D& v);

float Norm(const Vector2D& u);
Vector2D Normalized(const Vector2D& u);

int operator<(const Vector2D& a,const Vector2D& b);
int operator>(const Vector2D& a,const Vector2D& b);

Vector2D min(const Vector2D& a,const Vector2D& b);
Vector2D max(const Vector2D& a,const Vector2D& b);

float distance(const Vector2D& u, const Vector2D& v);
float distance2(const Vector2D& u, const Vector2D& v);

Vector2D Random();*/



// Binary operators
inline Vector2D operator+ (const Vector2D& u, const Vector2D& v){
    return Vector2D(u.x+v.x, u.y+v.y);
}
inline Vector2D operator+ (const Vector2D& u,float a){
    return Vector2D(u.x+a, u.y+a);
}
inline Vector2D operator+ (float a, const Vector2D& v){
    return v+a;
}

inline Vector2D operator- (const Vector2D& u, const Vector2D& v){
    return Vector2D(u.x-v.x, u.y-v.y);
}
inline Vector2D operator- (const Vector2D& u,float a){
    return Vector2D(u.x-a, u.y-a);
}
inline Vector2D operator- (float a, const Vector2D& v){
    return Vector2D(a-v.x, a-v.y);
}

inline Vector2D operator* (const Vector2D& u, const Vector2D& v){
    return Vector2D(u.x*v.x, u.y*v.y);
}
inline Vector2D operator* (const Vector2D& u,float a){
    return Vector2D(u.x*a, u.y*a);
}
inline Vector2D operator* (float a, const Vector2D& v){
    return v*a;
}

inline Vector2D operator/ (const Vector2D& u, const Vector2D& v){
    #ifndef QT_NO_DEBUG
        if(v.x==0.0 || v.y==0.0)
            std::cerr << "erreur: division d'un Vector2D avec 0" << std::endl;
    #endif
    return Vector2D(u.x/v.x, u.y/v.y);
}
inline Vector2D operator/ (const Vector2D& u, float a){
    #ifndef QT_NO_DEBUG
        if(a == 0)
            std::cerr << "erreur: division d'un Vector2D avec 0" << std::endl;
    #endif
    return Vector2D(u.x/a, u.y/a);
}
inline Vector2D operator/ (float a, const Vector2D& v){
    #ifndef QT_NO_DEBUG
        if(v.x==0.0 || v.y==0.0)
            std::cerr << "erreur: division d'un Vector2D avec 0" << std::endl;
    #endif
    return Vector2D(a/v.x, a/v.y);
}

/****************************************************************************************/

/*!
\brief Compute the Euclidean norm of a Vector2D.
*/
inline float Norm(const Vector2D& u){
    return sqrt(Norm2(u));
}
/*!
\brief Compute the Euclidean square norm of a Vector2D.
*/
inline float Norm2(const Vector2D& u){
    return u.x*u.x + u.y*u.y;
}


/*!
\brief Compute the normalized Vector2D.
*/
inline Vector2D Normalized(const Vector2D& u)
{
    float len = Norm(u);
    #ifndef QT_NO_DEBUG
        if(len == 0)
            std::cerr << "erreur: normalisation d'un Vector2D de longueur 0" << std::endl;
    #endif
    return u/len;
}

/****************************************************************************************/

/*!
\brief Return a new Vector2D with coordinates set to the minimum coordinates
of the two argument Vec2s.
*/
inline Vector2D min(const Vector2D& a,const Vector2D& b){
    return Vector2D(a[0]<b[0] ? a[0]:b[0] , a[1]<b[1] ? a[1]:b[1]);
}

/*!
\brief Return a new Vector2D with coordinates set to the maximum coordinates
of the two argument Vec2s.
*/
inline Vector2D max(const Vector2D& a,const Vector2D& b){
    return Vector2D(a[0]>b[0] ? a[0]:b[0] , a[1]>b[1] ? a[1]:b[1]);
}

/****************************************************************************************/

inline float dot(const Vector2D& u, const Vector2D& v){
    return u.x*v.x + u.y*v.y;
}
/*!
\brief Returns a new Vector2D orthogonal to the argument Vector2D.
*/
inline Vector2D Orthogonal(const Vector2D& u){
    return Vector2D(-u.y, u.x);
}

/****************************************************************************************/

inline float distance(const Vector2D& u, const Vector2D& v){
    return (v-u).getNorm();
}
inline float distance2(const Vector2D& u, const Vector2D& v){
    return (v-u).getNorm2();
}

/****************************************************************************************/

//! Generates a random Vector2D with precision 1e-3 within [0,1] interval
inline Vector2D Random2D()
{
    float x=rand()%1001/1000.0;
    float y=rand()%1001/1000.0;
    return Vector2D(x,y);
}

/**calcul l'orientation de bâc*/
inline float orientation(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    return (a.y - b.y) * (c.x - a.x) + (b.x - a.x) * (c.y - a.y);
    //if <0 : vers la gauche, if > 0: vers la droite, if == 0: aligné
}

#endif // VECTOR2D_H
