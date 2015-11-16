#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

//! \class Vector2D Vector2D.h
//! \brief Cette classe définit des vecteurs et des sommets dans l'espace.
class Vector2D
{
public:
      float x,y; //!< Coordinates

      Vector2D(): x(0), y(0) { } //! Empty
      Vector2D(float a, float b) { x=a; y=b; }
      Vector2D( Vector2D const& v){x = v.x; y = v.y;}

      float scalareProduct(const Vector2D & v) const{
          return x*v.x+y*v.y;
      }

      /*c'est l'orthogonal
       * Vector2D vectorProduct(){
          return Vector2D(y, -x);
      }*/

      Vector2D negate(){
          return Vector2D(-x, -y);
      }

      Vector2D& normalise(){
          float norme = getNorm();
          if(norme == 0)
          {
              x = 1000; y = 1000;
              return *this;  //////////////////////////////////////////////////////////////////////////
          }
          *this/=norme;
          return *this;
      }

      float getNorm() const{
          return sqrt(x*x+y*y);
      }
      float getNorm2() const{
          return x*x+y*y;
      }

      // Functions to access Vector2D class components
      float& operator[] (int i) {
        if (i == 0)    return x;
        else            return y;
      }

      float operator[] (int i) const {
        if (i == 0)    return x;
        else            return y;
      }

      // Unary operators
      Vector2D operator+ () const;
      Vector2D operator- () const;

      // Assignment operators
      Vector2D& operator+= (const Vector2D&);
      Vector2D& operator-= (const Vector2D&);
      Vector2D& operator*= (const Vector2D&);
      Vector2D& operator/= (const Vector2D&);
      Vector2D& operator*= (float);
      Vector2D& operator/= (float);

      // Binary operators
      friend Vector2D operator+ (const Vector2D&, const Vector2D&);
      friend Vector2D operator- (const Vector2D&, const Vector2D&);

      // Produit scalaire
      friend Vector2D operator* (const Vector2D&, const Vector2D&);

      friend Vector2D operator* (const Vector2D&, float);
      friend Vector2D operator* (float, const Vector2D&);
      friend Vector2D operator/ (const Vector2D&, float);

      // Produit Vectortiel
      friend Vector2D operator/ (const Vector2D&, const Vector2D&);

      // Boolean functions
      friend int operator==(const Vector2D&,const Vector2D&);
      friend int operator!=(const Vector2D&,const Vector2D&);
      friend int operator<(const Vector2D&,const Vector2D&);
      friend int operator>(const Vector2D&,const Vector2D&);
      //friend Vector2D min(const Vector2D&,const Vector2D&);
      //friend Vector2D max(const Vector2D&,const Vector2D&);

      friend std::ostream& operator<<(std::ostream&,const Vector2D&);

      friend Vector2D Orthogonal(const Vector2D&);

      // Norm
      friend float Norm(const Vector2D&);
      friend float Norm2(const Vector2D&);
      friend Vector2D Normalized(const Vector2D&);

      friend float distance(const Vector2D& u, const Vector2D& v);
      friend float distance2(const Vector2D& u, const Vector2D& v);
};


// Unary operators
inline Vector2D Vector2D::operator+ () const
{
  return *this;
}

inline Vector2D Vector2D::operator- () const
{
    return Vector2D(-x,-y);
}

// Assignment unary operators
inline Vector2D& Vector2D::operator+= (const Vector2D& u)
{
  x+=u.x; y+=u.y;
  return *this;
}

inline Vector2D& Vector2D::operator-= (const Vector2D& u)
{
  x-=u.x; y-=u.y;
  return *this;
}

inline Vector2D& Vector2D::operator*= (float a)
{
  x*=a; y*=a;
  return *this;
}

inline Vector2D& Vector2D::operator/= (float a)
{
  x/=a; y/=a;
  return *this;
}

inline Vector2D& Vector2D::operator*= (const Vector2D& u)
{
  x*=u.x; y*=u.y;
  return *this;
}

inline Vector2D& Vector2D::operator/= (const Vector2D& u)
{
  x/=u.x; y/=u.y;
  return *this;
}

// Binary operators
inline Vector2D operator+ (const Vector2D& u, const Vector2D& v)
{
  return Vector2D(u.x+v.x,u.y+v.y);
}

inline Vector2D operator- (const Vector2D& u, const Vector2D& v)
{
  return Vector2D(u.x-v.x,u.y-v.y);
}

// Scalar product
inline Vector2D operator* (const Vector2D& u, const Vector2D& v)
{
  return Vector2D(u.x*v.x,u.y*v.y);
}

inline Vector2D operator* (const Vector2D& u,float a)
{
  return Vector2D(u.x*a,u.y*a);
}

inline Vector2D operator* (float a, const Vector2D& v)
{
  return v*a;
}

// Cross product
inline Vector2D operator/ (const Vector2D& u, const Vector2D& v)
{
    return Vector2D(u.x/v.x, u.y/v.y);
    //????????????????????????????????
    //return Vector2D(u.y*v.y-u.y*v.y,u.y*v.x-u.x*v.y,u.x*v.y-u.y*v.x);
}

inline Vector2D operator/ (const Vector2D& u, float a)
{
  return Vector2D(u.x/a,u.y/a);
}

// Boolean functions
inline int operator== (const Vector2D& u,const Vector2D& v)
{
  return ((u.x==v.x)&&(u.y==v.y));
}

inline int operator!= (const Vector2D& u,const Vector2D& v)
{
  return (!(u==v));
}

/*!
\brief Compute the Euclidean norm of a Vector2D.
*/
inline float Norm(const Vector2D& u)
{
  return sqrt(u.x*u.x+u.y*u.y);
}
inline float Norm2(const Vector2D& u)
{
  return u.x*u.x+u.y*u.y;
}
/*!
\brief Compute the normalized Vector2D.
*/
inline Vector2D Normalized(const Vector2D& u)
{
    float norme = Norm(u);
    if(norme == 0)
        return Vector2D(1000,1000);  //////////////////////////////////////////////////////////////////////////
    return u/norme;
}

inline int operator<(const Vector2D& a,const Vector2D& b)
{
  return ((a.x<b.x)&&(a.y<b.y));
}

inline int operator>(const Vector2D& a,const Vector2D& b)
{
  return ((a.x>b.x)&&(a.y>b.y));
}

inline std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";

    return stream;
}

/*!
\brief Return a new Vector2D with coordinates set to the minimum coordinates
of the two argument Vec2s.
*/
inline Vector2D min(const Vector2D& a,const Vector2D& b)
{
  return Vector2D(a[0]<b[0]?a[0]:b[0],a[1]<b[1]?a[1]:b[1]);
}

/*!
\brief Return a new Vector2D with coordinates set to the maximum coordinates
of the two argument Vec2s.
*/
inline Vector2D max(const Vector2D& a,const Vector2D& b)
{
  return Vector2D(a[0]>b[0]?a[0]:b[0],a[1]>b[1]?a[1]:b[1]);
}

/*!
\brief Returns a new Vector2D orthogonal to the argument Vector2D.
*/
inline Vector2D Orthogonal(const Vector2D& u)
{
  return Vector2D(-u.y, u.x);
}

inline float distance(const Vector2D& u, const Vector2D& v)
{
    return (v-u).getNorm();
}
inline float distance2(const Vector2D& u, const Vector2D& v)
{
    return (v-u).getNorm2();
}

//! Generates a random Vector2D with precision 1e-3 within [0,1] interval
inline Vector2D Random()
{
  float x=rand()%1001/1000.0f;
  float y=rand()%1001/1000.0f;
  return Vector2D(x,y);
}

#endif // VEC2_H
