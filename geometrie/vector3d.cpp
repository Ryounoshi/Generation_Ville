#include "vector3d.h"

float Vector3D::dotProduct(const Vector3D& vec2) const{
    return (x*vec2.x + y*vec2.y + z*vec2.z);
}

Vector3D Vector3D::crossProduct(const Vector3D& vec2) const{
    return Vector3D(y*vec2.z - z*vec2.y , x*vec2.z - z*vec2.x , x*vec2.y - y*vec2.x);
}

float Vector3D::norm() const{
    return sqrt(x*x+y*y+z*z);
}

float Vector3D::squareNorm() const
{
    return x*x+y*y+z*z;
}

void Vector3D::normalize(){
    float len=norm();
    if(len!=0){
        x/=len;
        y/=len;
        z/=len;
    }
}

Vector3D Vector3D::normalized() const{
    float len=norm();
    if(len!=0){
        return Vector3D(x/len, y/len, z/len);
    }
    return Vector3D(x, y, z);
}

void Vector3D::change(float a, float b, float c){
    x=a;
    y=b;
    z=c;
}

void Vector3D::change(const Vector3D& vec2){
    x=vec2.x;
    y=vec2.y;
    z=vec2.z;
}

void Vector3D::changeX(float a){
    x=a;
}

void Vector3D::changeY(float a){
    y=a;
}

void Vector3D::changeZ(float a){
    z=a;
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x,-y,-z);
}

Vector3D Vector3D::operator+(const float num) const{
    return Vector3D(x+num,y+num,z+num);
}

Vector3D Vector3D::operator-(const float num) const{
    return Vector3D(x-num,y-num,z-num);
}

Vector3D Vector3D::operator*(const float num) const{
    return Vector3D(x*num,y*num,z*num);
}

Vector3D Vector3D::operator/(const float num) const{
    if(num!=0.0)
        return Vector3D(x/num,y/num,z/num);
    else
        return Vector3D();
}

Vector3D Vector3D::operator+(const Vector3D& vec2) const{
    return Vector3D(x+vec2.x,y+vec2.y,z+vec2.z);
}

Vector3D Vector3D::operator-(const Vector3D& vec2) const{
    return Vector3D(x-vec2.x,y-vec2.y,z-vec2.z);
}

Vector3D Vector3D::operator*(const Vector3D& vec2) const{
    return Vector3D(x*vec2.x,y*vec2.y,z*vec2.z);
}

Vector3D Vector3D::operator/(const Vector3D& vec2) const{
    if(vec2.x!=0.0 && vec2.y!=0.0 && vec2.z!=0.0)
        return Vector3D(x*vec2.x,y*vec2.y,z*vec2.z);
    else
        return Vector3D();
}


Vector3D& Vector3D::operator+=(const float& num){
    x+=num;
    y+=num;
    z+=num;
    return *this;
}

Vector3D& Vector3D::operator-=(const float& num){
    x-=num;
    y-=num;
    z-=num;
    return *this;
}

Vector3D& Vector3D::operator*=(const float& num){
    x*=num;
    y*=num;
    z*=num;
    return *this;
}

Vector3D& Vector3D::operator/=(const float& num){
    if(num!=0){
        x/=num;
        y/=num;
        z/=num;
    }
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vec2){
    x+=vec2.x;
    y+=vec2.y;
    z+=vec2.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vec2){
    x-=vec2.x;
    y-=vec2.y;
    z-=vec2.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& vec2){
    x*=vec2.x;
    y*=vec2.y;
    z*=vec2.z;
    return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& vec2){
    if(vec2.x!=0.0 && vec2.y!=0.0 && vec2.z!=0.0){
        x/=vec2.x;
        y/=vec2.y;
        z/=vec2.z;
    }
    return *this;
}

bool Vector3D::operator==(const Vector3D vec2) const{
    return(x==vec2.x && y==vec2.y && z==vec2.z);
}

bool Vector3D::operator!=(const Vector3D vec2) const{
    return(!(*this==vec2));
}

Vector3D& Vector3D::rotateAboutX(const float& angle){
    float s = sinf(angle);
    float c = cosf(angle);

    float ny = c * y - s * z;
    float nz = c * z + s * y;

    y = ny;
    z = nz;

    return (*this);
}

Vector3D& Vector3D::rotateAboutY(const float& angle){
    float s = sinf(angle);
    float c = cosf(angle);

    float nx = c * x + s * z;
    float nz = c * z - s * x;

    x = nx;
    z = nz;

    return (*this);
}

Vector3D& Vector3D::rotateAboutZ(const float& angle){
    float s = sinf(angle);
    float c = cosf(angle);

    float nx = c * x - s * y;
    float ny = c * y + s * x;

    x = nx;
    y = ny;

    return (*this);
}

Vector3D& Vector3D::rotateAboutAxis(const float& angle, const Vector3D& axis){
    float s = sinf(angle);
    float c = cosf(angle);
    float k = 1.0F - c;

    float nx = x * (c + k * axis.x * axis.x) + y * (k * axis.x * axis.y - s * axis.z)
            + z * (k * axis.x * axis.z + s * axis.y);
    float ny = x * (k * axis.x * axis.y + s * axis.z) + y * (c + k * axis.y * axis.y)
            + z * (k * axis.y * axis.z - s * axis.x);
    float nz = x * (k * axis.x * axis.z - s * axis.y) + y * (k * axis.y * axis.z + s * axis.x)
            + z * (c + k * axis.z * axis.z);

    x = nx;
    y = ny;
    z = nz;

    return (*this);
}

float Vector3D::distance(const Vector3D &vec2) const
{
    return (vec2-*this).norm();
}

float Vector3D::Squaredistance(const Vector3D &vec2) const
{
    return (vec2-*this).squareNorm();
}

std::ostream& operator<<(std::ostream& out,const Vector3D& vec){
    return out << "{" << vec.x << " " << vec.y << " " << vec.z << "}" <<std::endl;
}
