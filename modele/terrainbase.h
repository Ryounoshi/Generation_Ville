#ifndef TERRAINBASE_H
#define TERRAINBASE_H

#include <vector>
#include "quartier/quartier.h"

class TerrainBase
{
public:
    TerrainBase(float longueur, float largeur);
    ~TerrainBase();

    void decoupeSimple();   //ne fait que des triangles et quadrangle
    void decoupe();
    void shrink(float f);
        //à remettre en privé (c'est pour les tests)
    std::vector<Quartier*> quartiers;

    Mesh generate();

protected:
    float longueur, largeur;

};

#endif // TERRAINBASE_H
