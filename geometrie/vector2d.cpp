#include "vector2d.h"

void Vector2D::set(float a, float b){
    x = a;  y = b;
}

/****************************************************************************************/

float Vector2D::dotProduct(const Vector2D& v) const{
    return dot(*this, v);
}
float Vector2D::scalareProduct(const Vector2D & v) const{
    return dot(*this, v);
}


//c'est l'orthogonal
Vector2D Vector2D::vectorProduct() const{
    return Orthogonal(*this);
}
Vector2D Vector2D::crossProduct() const{
    return Orthogonal(*this);
}


Vector2D Vector2D::negate() const{
    return -*this;
}

/****************************************************************************************/

float Vector2D::getNorm() const{
    return Norm(*this);
}
float Vector2D::getNorm2() const{
    return Norm2(*this);
}

/****************************************************************************************/

void Vector2D::normalise(){
    float len = getNorm();
    #ifndef QT_NO_DEBUG
        if(len == 0)
            std::cerr << "erreur: normalisation d'un Vector2D de longueur 0" << std::endl;
    #endif
    *this/=len;
}

Vector2D Vector2D::normalised() const{
    float len = getNorm();
    #ifndef QT_NO_DEBUG
        if(len == 0)
            std::cerr << "erreur: normalisation d'un Vector2D de longueur 0" << std::endl;
    #endif
    return *this/len;
}

/****************************************************************************************/

// Functions to access Vector2D class components
float& Vector2D::operator[] (int i) {
    if (i == 0) return x;
    else        return y;
}
float Vector2D::operator[] (int i) const {
    if (i == 0) return x;
    else        return y;
}

/******************************************************************************/


// Unary operators
Vector2D Vector2D::operator+ () const{
    return *this;
}

Vector2D Vector2D::operator- () const{
    return Vector2D(-x,-y);
}

// Assignment unary operators
void Vector2D::operator+= (const Vector2D& u){
    x+=u.x; y+=u.y;
}
void Vector2D::operator+= (float a){
    x+=a; y+=a;
}

void Vector2D::operator-= (const Vector2D& u){
    x-=u.x; y-=u.y;
}
void Vector2D::operator-= (float a){
    x-=a; y-=a;
}

void Vector2D::operator*= (const Vector2D& u){
    x*=u.x; y*=u.y;
}
void Vector2D::operator*= (float a){
    x*=a; y*=a;
}

void Vector2D::operator/= (const Vector2D& u){
    #ifndef QT_NO_DEBUG
        if(u.x==0.0 || u.y==0.0)
            std::cerr << "erreur: division d'un Vector3D avec 0" << std::endl;
    #endif
    x/=u.x; y/=u.y;
}
void Vector2D::operator/= (float a){
    #ifndef QT_NO_DEBUG
        if(a==0.0)
            std::cerr << "erreur: division d'un Vector2D avec 0" << std::endl;
    #endif
    x/=a; y/=a;
}

/****************************************************************************************/

int Vector2D::operator==(const Vector2D& v) const{
    return(x==v.x && y==v.y);
}
int Vector2D::operator!=(const Vector2D& v) const{
    return(!(*this==v));
}

int Vector2D::operator<(const Vector2D& v) const{
    return ((x<v.x) && (y<v.y));
}
int Vector2D::operator>(const Vector2D& v) const{
    return ((x>v.x) && (y>v.y));
}

int Vector2D::operator<=(const Vector2D& v) const{
    return ((x<=v.x) && (y<=v.y));
}
int Vector2D::operator>=(const Vector2D& v) const{
    return ((x>=v.x) && (y>=v.y));
}

/*****************************************************/



/*****************************************************/


std::ostream& operator<<(std::ostream& out,const Vector2D& vec){
    return out << "{" << vec.x << " " << vec.y << "}";
}
