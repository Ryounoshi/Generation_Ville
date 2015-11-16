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


    void split();
    void shrink(float f);
        //à remettre en privé (c'est pour les tests)
    std::vector<Quartier*> quartiers;

    Mesh generate();

protected:
    float longueur, largeur;
    BatParameter* _par;

};

#endif // TERRAINBASE_H
