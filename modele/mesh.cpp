#include "mesh.h"


/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions utilitaires             */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

void Mesh::merge(const Mesh &delta)
{
    if(&delta != this){
        int taille = vertex.size();
        vertex.reserve(taille+delta.nbVertex());

        for(size_t i=0; i< delta.vertex.size(); i++){
            vertex.push_back(delta.vertex[i]);
        }

        face.reserve(this->nbFace()+delta.nbFace());
        for(size_t i=0; i< delta.face.size(); i++){
            face.push_back(delta.face[i] + taille );
        }
    }
}

/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions accessors               */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

std::vector<Vector3D> Mesh::getVertex() const{
    return vertex;
}

std::vector<unsigned int> Mesh::getFace() const{
    return face;
}

Vector3D Mesh::getVertex(int at) const{
    return vertex.at(at);
}

unsigned int Mesh::getFace(int at) const{
    return face.at(at);
}

void Mesh::addVertex(const Vector3D& _vertex)
{
    vertex.push_back(_vertex);
}

void Mesh::addFace(const unsigned int& refPointFace1, const unsigned int& refPointFace2, const unsigned int& refPointFace3)
{
    face.push_back(refPointFace1);
    face.push_back(refPointFace2);
    face.push_back(refPointFace3);
}

size_t Mesh::nbVertex() const
{
    return this->vertex.size();
}

size_t Mesh::nbFace() const
{
    return this->face.size();
}


void Mesh::translation(const float x, const float y, const float z)
{
    for(Vector3D& p: vertex){
        p.x+=x;
        p.y+=y;
        p.z+=z;
    }
}

void Mesh::rotation(const Vector3D& T){
    rotation(T.x, T.y, T.z);
}

void Mesh::rotation(const float rX, const float rY, const float rZ){

    for(size_t i=0; i<vertex.size(); i++){
        if(rX != 0)
            vertex[i].rotateAboutAxis(rX, Vector3D(1,0,0) );
        if(rY != 0)
            vertex[i].rotateAboutAxis(rY, Vector3D(0,1,0) );
        if(rZ != 0)
            vertex[i].rotateAboutAxis(rZ, Vector3D(0,0,1) );
    }
}

void Mesh::localRotation(const float rX, const float rY, const float rZ){
    float min = 1000000;
    Vector3D gravite;
    for(Vector3D& p:vertex){
        gravite = gravite + p;
        min = p.z < min ? p.z : min;
    }
    gravite /= vertex.size();
    gravite.changeZ(min);
    translation(-gravite.x,-gravite.y,-gravite.z);
    for(size_t i=0; i<vertex.size(); i++){
        if(rX != 0)
            vertex[i].rotateAboutAxis(rX, Vector3D(1,0,0) );
        if(rY != 0)
            vertex[i].rotateAboutAxis(rY, Vector3D(0,1,0) );
        if(rZ != 0)
            vertex[i].rotateAboutAxis(rZ, Vector3D(0,0,1) );
    }
    translation(gravite.x,gravite.y,gravite.z);
}

void Mesh::rescale(float scale)
{
    for(Vector3D& p: vertex){
        p *= scale;
    }
}

void Mesh::localrescale(float scale){
    float min = 1000000;
    Vector3D gravite;
    for(Vector3D& p:vertex){
        gravite = gravite + p;
        min = p.z < min ? p.z : min;
    }
    gravite /= vertex.size();
    gravite.changeZ(min);
    translation(-gravite.x,-gravite.y,-gravite.z);
    for(Vector3D& p: vertex){
        p *= scale;
    }
    translation(gravite.x,gravite.y,gravite.z);
}

void Mesh::localrescaleXY(float scale){
    Vector3D gravite;
    for(Vector3D& p:vertex){
        gravite = gravite + p;
    }
    gravite /= vertex.size();
    translation(-gravite.x,-gravite.y,-gravite.z);
    for(Vector3D& p: vertex){
        p.x *= scale;
        p.y *= scale;
    }
    translation(gravite.x,gravite.y,gravite.z);
}

/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            générateur de formes              */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

Mesh Mesh::createCylindre(const Vector3D &centreCercleA, const Vector3D &centreCercleB, const float& rayon, const int& resolution)
{
    Mesh m;
    m.vertex.reserve((resolution+1)*2);
    m.face.reserve(4*resolution);

    Vector3D normal = centreCercleB - centreCercleA;

    Vector3D axe1(normal.y,-normal.x,0), axe2(axe1.crossProduct(normal));

    axe1.normalize();
    axe1*=rayon;
    axe2.normalize();
    axe2*=rayon;

    //P = Rcos(t)u +Rsin(t)resolution × u + c;
    //M=C+A*cos(t)+B*sin(t)

    /*************************************/
    /* Génération points */
    /*************************************/

    float ecartRadiant = (2*M_PI2)/resolution;

    for(int i=0; i<resolution; i++){
        Vector3D p = axe1*cos(i*ecartRadiant) + axe2*sin(i*ecartRadiant) + centreCercleA;
        //std::cout << p << std::endl;
        m.addVertex(p);
        m.addFace(resolution*2, i, (i+1)%resolution);
    }

    for(int i=0; i<resolution; i++){
        m.addVertex( m.vertex[i]+normal );
        m.addFace(resolution*2+1, resolution+(i+1)%resolution, resolution+i);
        m.addFace(i, i+resolution, (i+1)%resolution);
        m.addFace(i+resolution, resolution+(i+1)%resolution, (i+1)%resolution);
    }

    m.addVertex(centreCercleA); // 2 resolution
    m.addVertex(centreCercleB); // 2 resolution+1


    //m.normalsTriangles();
    return m;
}

Mesh Mesh::createQuadrangle3D(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const float &height)
{
    Mesh m;
    m.vertex.push_back(a);
    m.vertex.push_back(b);
    m.vertex.push_back(c);
    m.vertex.push_back(d);
    Vector3D trans(0,0,height);
    m.vertex.push_back(a+trans);
    m.vertex.push_back(b+trans);
    m.vertex.push_back(c+trans);
    m.vertex.push_back(d+trans);

    m.addFace(2,6,3);
    m.addFace(6,7,3);
    m.addFace(3,7,4);
    m.addFace(3,4,0);
    m.addFace(5,4,6);
    m.addFace(6,4,7);
    m.addFace(1,0,5);
    m.addFace(0,4,5);
    m.addFace(1,5,6);
    m.addFace(1,6,2);
    m.addFace(1,2,0);
    m.addFace(2,3,0);

    return m;
}

Mesh Mesh::createBox(const Vector3D& a, const Vector3D& b)
{
    float height = b.z - a.z;
    Vector3D b_(a.x, b.y, a.z);
    Vector3D c_(b.x, b.y, a.z);
    Vector3D d_(b.x, a.y, a.z);
    return Mesh::createQuadrangle3D(a, b_, c_, d_, height);
}

/*Mesh Mesh::createCube(const Vector3D& a, const Vector3D& b)
{
    Vector3D b2(b.x, b.y, 0);
    float length = (b2 - a).length();
    Vector3D perp = Vector3D(a.y-b.y,b.x-a.x,0).normalized();
    Vector3D d(perp*length);
    Vector3D b_(a.x, b.y, a.z);
    Vector3D c_(b.x, b.y, a.z);
    Vector3D d_(b.x, a.y, a.z);
    return Mesh::createQuadrangle3D(a, b_, c_, d_, height);
}*/

Mesh Mesh::createPrism(const Vector3D& a, const Vector3D& b, const Vector3D& c, const float &height)
{
    Mesh m;
    m.vertex.push_back(a);
    m.vertex.push_back(b);
    m.vertex.push_back(c);
    Vector3D trans(0,0,height);
    m.vertex.push_back(a+trans);
    m.vertex.push_back(b+trans);
    m.vertex.push_back(c+trans);

    m.addFace(3,4,5);
    m.addFace(0,2,1);
    m.addFace(3,0,1);
    m.addFace(4,3,1);
    m.addFace(4,1,2);
    m.addFace(5,4,2);
    m.addFace(3,5,0);
    m.addFace(2,0,5);

    return m;
}

Mesh Mesh::createPyramidTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, const float& height)
{
    Vector3D base_center((a.x+b.x+c.x)/3, (a.y+b.y+c.y)/3, (a.z+b.z+c.z)/3);
    Vector3D top(base_center+Vector3D(0,0,height));

    Mesh m;
    m.vertex.push_back(a);
    m.vertex.push_back(b);
    m.vertex.push_back(c);
    m.vertex.push_back(top);

    m.addFace(0,3,1);
    m.addFace(1,3,2);
    m.addFace(2,3,0);
    m.addFace(1,2,0);

    return m;
}

Mesh Mesh::createPyramidQuadrangle(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const float& height)
{
    Vector3D base_center((a.x+b.x+c.x+d.x)/4, (a.y+b.y+c.y+d.y)/4, a.z);
    Vector3D top(base_center+Vector3D(0,0,height));

    Mesh m;
    m.vertex.push_back(a);
    m.vertex.push_back(b);
    m.vertex.push_back(c);
    m.vertex.push_back(d);
    m.vertex.push_back(top);

    m.addFace(0,4,1);
    m.addFace(1,4,2);
    m.addFace(2,4,3);
    m.addFace(3,4,0);
    m.addFace(3,0,1);
    m.addFace(3,1,2);

    return m;
}

void Mesh::addTriangle(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    int ref = nbVertex();
    addVertex(a);
    addVertex(b);
    addVertex(c);

    addFace(ref, ref+1, ref+2);
}
