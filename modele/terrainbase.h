#ifndef TERRAINBASE_H
#define TERRAINBASE_H

#include <vector>
#include "quartier/quartier.h"

class TerrainBase
{
public:
    TerrainBase(float longueur, float largeur, BatParameter* par);
    ~TerrainBase();

    void decoupeSimple();   //ne fait que des triangles et quadrangle
    void decoupe();
    void shrink(float f);

    void supprPetitQuartier(float f);

        //à remettre en privé (c'est pour les tests)

    Mesh generate();

protected:
    float longueur, largeur;
    std::vector<Quartier*> quartiers;


    BatParameter* _par;
};

#endif // TERRAINBASE_H
