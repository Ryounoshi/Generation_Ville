#ifndef QUARTIER_H
#define QUARTIER_H

#include <vector>
#include "geometrie/Triangle.h"
#include "geometrie/quadrangle.h"
#include "geometrie/pentagone.h"
#include "modele/mesh.h"
#include "modele/batiment/batparameter.h"
#include "modele/batiment/batiment.h"
#include <random>

#define MIN_COTE 30
#define AIRE_QUARTIER_MAX 40000

class Quartier
{
public:
    Quartier()  {}
    Quartier(BatParameter* par);

    virtual ~Quartier() {}

    virtual std::pair<Quartier*,Quartier*> decoupeSimple() = 0;
    virtual std::pair<Quartier*,Quartier*> decoupe() = 0;

    virtual void shrink(float l) = 0;
    virtual float area() const = 0;
    virtual float perimetre() const = 0;

    virtual void split() = 0;


    virtual std::vector<Vector2D> getPoints() const = 0;
    virtual std::vector<Vector3D> getPoints3D() const = 0;

    Mesh generate();
protected:
    BatParameter* _par;
    std::default_random_engine generator;
    std::vector<Batiment> batiments;
};

#include "quarpenta.h"
#include "quartri.h"
#include "quarquad.h"


#endif // QUARTIER_H
