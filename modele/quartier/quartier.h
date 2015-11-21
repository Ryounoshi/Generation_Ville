#ifndef QUARTIER_H
#define QUARTIER_H

#include <vector>
#include "geometrie/Triangle.h"
#include "geometrie/quadrangle.h"
#include "geometrie/pentagone.h"
#include "modele/mesh.h"
#include "modele/batiment/batparameter.h"
#include "modele/batiment/batiment.h"

#define MIN_COTE 10
#define AIRE_QUARTIER_MAX 20000

class Quartier
{
public:
    Quartier()  {}
    Quartier(BatParameter* par):    _par(par)  {
        generator = std::default_random_engine(4546);
    }

    virtual ~Quartier() { delete _par;}

    virtual std::pair<Quartier*,Quartier*> decoupeSimple() = 0;
    virtual std::pair<Quartier*,Quartier*> decoupe() = 0;

    virtual void shrink(float l) = 0;
    virtual float area() const = 0;
    virtual float perimetre() const = 0;


    virtual std::vector<Vector2D> getPoints() const = 0;
    virtual std::vector<Vector3D> getPoints3D() const = 0;

    virtual Mesh generate() = 0;

    void setPar(BatParameter* par);

protected:
    BatParameter* _par;
    std::default_random_engine generator;
    std::vector<Batiment> batiments;
};

#include "quarpenta.h"
#include "quartri.h"
#include "quarquad.h"


#endif // QUARTIER_H
