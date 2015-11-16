#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
#include <cmath>


class Vector3D
{
public:

    float x,y,z;

    Vector3D():x(0.0),y(0.0),z(0.0){}
    Vector3D(float a, float b):x(a),y(b),z(0.0){}
    Vector3D(float a, float b, float c):x(a),y(b),z(c){}

    float dotProduct(const Vector3D& vec2) const;
    Vector3D crossProduct(const Vector3D& vec2) const;
    float norm() const;
    float squareNorm() const;
    void normalize();
    Vector3D normalized() const;

    void change(float a, float b, float c);
    void change(const Vector3D& vec2);
    void changeX(float a);
    void changeY(float a);
    void changeZ(float a);

    // Functions to access Vec3 class components
    float& operator[] (int i);
    float operator[] (int i) const;

    // Unary operators
    Vector3D operator-() const;

    // Binary operators
    Vector3D operator+(const float num) const;
    Vector3D operator-(const float num) const;
    Vector3D operator*(const float num) const;
    Vector3D operator/(const float num) const;

    Vector3D operator+(const Vector3D& vec2) const;
    Vector3D operator-(const Vector3D& vec2) const;
    Vector3D operator*(const Vector3D& vec2) const;
    Vector3D operator/(const Vector3D& vec2) const;

    // Assignment operators
    Vector3D& operator+=(const float& num);
    Vector3D& operator-=(const float& num);
    Vector3D& operator*=(const float& num);
    Vector3D& operator/=(const float& num);

    Vector3D& operator+=(const Vector3D& vec2);
    Vector3D& operator-=(const Vector3D& vec2);
    Vector3D& operator*=(const Vector3D& vec2);
    Vector3D& operator/=(const Vector3D& vec2);

    bool operator==(const Vector3D vec2) const;
    bool operator!=(const Vector3D vec2) const;

    /**
     * @brief rotateAboutX
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutX(const float& angle);

    /**
     * @brief rotateAboutY
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutY(const float& angle);

    /**
     * @brief rotateAboutZ
     * @param angle en radiants
     * @return
     */
    Vector3D& rotateAboutZ(const float& angle);
    Vector3D& rotateAboutAxis(const float& angle, const Vector3D& axis);

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& vec);

    float distance(const Vector3D& vec2) const;
    float Squaredistance(const Vector3D& vec2) const;


};

#endif // VECTOR3D_H
