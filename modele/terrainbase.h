#ifndef TERRAINBASE_H
#define TERRAINBASE_H

#include <vector>
#include "quartier/quartier.h"

class TerrainBase
{
public:
    TerrainBase(float longueur, float largeur, BatParameter* par);
    TerrainBase(const Quadrangle& q, BatParameter* par);
    TerrainBase(const Triangle& q, BatParameter* par);

    TerrainBase(TerrainBase&& base);
    ~TerrainBase();

    void decoupeSimple(float aireMax);   //ne fait que des triangles et quadrangle
    void decoupe(float aireMax);
    void shrink(float f);

    void supprPetitQuartier(float f);

        //à remettre en privé (c'est pour les tests)

    Mesh generate();

protected:
    BatParameter* _par;
    std::vector<Quartier*> quartiers;
};

#endif // TERRAINBASE_H
