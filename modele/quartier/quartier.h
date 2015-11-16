#ifndef QUARTIER_H
#define QUARTIER_H

#include <vector>
#include "geometrie/Triangle.h"
#include "geometrie/quadrangle.h"
#include "geometrie/pentagone.h"

#define MIN_COTE 10
#define AIRE_QUARTIER_MAX 1000

class Quartier
{
public:
    Quartier()  {}


    virtual std::pair<Quartier*,Quartier*> decoupeSimple() = 0;
    virtual std::pair<Quartier*,Quartier*> decoupe() = 0;

    virtual void shrink(float l) = 0;
    virtual float area() const = 0;
    virtual float perimetre() const = 0;
};

#include "quarpenta.h"
#include "quartri.h"
#include "quarquad.h"


#endif // QUARTIER_H
