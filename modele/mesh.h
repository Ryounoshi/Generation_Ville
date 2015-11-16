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
    Mesh(std::vector<Vector3D> listvertex, std::vector<unsigned int> listface): vertex(listvertex), face(listface)  {}

    ~Mesh(){}

    void merge(const Mesh &delta);

    std::vector<Vector3D> getvertex() const;
    std::vector<unsigned int> getface() const;
    Vector3D getvertex(int at) const;
    unsigned int getface(int at) const;
    void setVertex(const std::vector<Vector3D> &vertex){this->vertex = vertex;}
    void setFace(const std::vector<unsigned int> &face){this->face = face;}
    void addVertex(const Vector3D& _vertex);
    void addFace(const unsigned int& refPointFace1, const unsigned int& refPointFace2, const unsigned int& refPointFace3);
    size_t nbvertex() const;
    size_t nbface() const;

	void translation(const float x, const float y, const float z);
    void rotation(const Vector3D T);
    void rotation(const float rX, const float rY, const float rZ);
    void localrotation(const float rX, const float rY, const float rZ);

    void localrescale(float scale);
    void localrescaleXY(float scale);
    void rescale(float scale);

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

    static Mesh createBox(const Vector3D& a, const Vector3D& b);

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
