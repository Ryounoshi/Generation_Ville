#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <math.h>
#include "float.h"
#include <algorithm>
#include "geometrie/vector3d.h"
#include "geometrie/quadrangle.h"

# define M_PI2		3.14159265358979323846

class Mesh{

protected:
    std::vector<Vector3D> vertex;
    std::vector<Vector3D> normalsPoints;
    std::vector<unsigned int> face;

public :

    Mesh(){}
    Mesh(const std::vector<Vector3D>& listvertex, const std::vector<unsigned int>& listface): vertex(listvertex), face(listface)  {}

    ~Mesh(){}

    void merge(const Mesh &delta);

    std::vector<Vector3D> getVertex() const;
    std::vector<unsigned int> getFace() const;
    Vector3D getVertex(int at) const;
    unsigned int getFace(int at) const;
    void setVertex(const std::vector<Vector3D> &vertex){this->vertex = vertex;}
    void setFace(const std::vector<unsigned int> &face){this->face = face;}
    void addVertex(const Vector3D& _vertex);
    void addFace(const unsigned int& refPointFace1, const unsigned int& refPointFace2, const unsigned int& refPointFace3);
    size_t nbVertex() const;
    size_t nbFace() const;

	void translation(const float x, const float y, const float z);
    void rotation(const Vector3D& T);
    void rotation(const float rX, const float rY, const float rZ);
    void localRotation(const float rX, const float rY, const float rZ);

    void localrescale(float scale);
    void localrescaleXY(float scale);
    void rescale(float scale);


    void addTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c);

    //********* Génération Primitive ***********//
    #define DEFAULT_RESOLUTION 32
    static Mesh createCylindre(const Vector3D &centreCercleA, const Vector3D &centreCercleB, const float& rayon, const int& resolution = DEFAULT_RESOLUTION);

    /**
     * @brief createQuadrangle3D
     * (a,b,c,d) must be convex
     * @param a
     * @param b
     * @param c
     * @param d
     * @param height
     * @return
     */
    static Mesh createQuadrangle3D(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const float& height);

    static Mesh createQuadrangle3DTwisted(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Vector3D &a2, const Vector3D &b2, const Vector3D &c2, const Vector3D &d2, const float& height);

    static Mesh createHexaangle3D(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d,const Vector3D& e, const Vector3D& f,  const float &height);

    static Mesh createBox(const Vector3D& a, const Vector3D& b);

    static Mesh createHexaangleTwisted(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Vector3D& e, const Vector3D& f, const Vector3D &a2, const Vector3D &b2, const Vector3D &c2, const Vector3D &d2, const Vector3D &e2, const Vector3D &f2, const float &height);

    //static Mesh createCube(const Vector3D& a, const Vector3D& b);

    /**
     * @brief createPrism
     * Base triangulaire horizontale
     * @param a
     * @param b
     * @param c
     * @param height
     * @return
     */
    static Mesh createPrism(const Vector3D& a, const Vector3D& b, const Vector3D& c, const float& height);

    /**
     * @brief createPyramidTriangle
     * Points can have different Z, but the top is always along Z
     * @param a
     * @param b
     * @param c
     * @param height
     * @return
     */
    static Mesh createPyramidTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, const float& height);

    /**
     * @brief createPyramidQuadrangle
     * Points should have the same Z
     * @param a
     * @param b
     * @param c
     * @param d
     * @param height
     * @return
     */
    static Mesh createPyramidQuadrangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const float& height);

protected:

};


#endif // MESH_H
