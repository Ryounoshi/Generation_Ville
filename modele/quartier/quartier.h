#ifndef QUARTIER_H
#define QUARTIER_H

#include <vector>
#include "geometrie/Triangle.h"
#include "geometrie/quadrangle.h"
#include "geometrie/pentagone.h"
#include "modele/mesh.h"

#define MIN_COTE 10
#define AIRE_QUARTIER_MAX 1000

class Quartier
{
public:
    Quartier()  {}

    virtual ~Quartier() {}

    virtual std::pair<Quartier*,Quartier*> decoupeSimple() = 0;
    virtual std::pair<Quartier*,Quartier*> decoupe() = 0;

    virtual void shrink(float l) = 0;
    virtual float area() const = 0;
    virtual float perimetre() const = 0;


    virtual std::vector<Vector2D> getPoints() const = 0;
    virtual std::vector<Vector3D> getPoints3D() const = 0;

    virtual Mesh generate() = 0;
};

#include "quarpenta.h"
#include "quartri.h"
#include "quarquad.h"


#endif // QUARTIER_H
