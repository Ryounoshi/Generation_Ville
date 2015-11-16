#include "terrainbase.h"

TerrainBase::TerrainBase(float longueur, float largeur, BatParameter* par):
        longueur(longueur),  largeur(largeur),  _par(par)
{
    QuarQuad* quad = new QuarQuad(Vector2D(0,0), Vector2D(0,longueur), Vector2D(largeur, longueur), Vector2D(largeur,0), par);
    quartiers.push_back(quad);
}

TerrainBase::~TerrainBase()
{
    for(unsigned int i = 0;  i < quartiers.size();  i++)
        delete quartiers[i];
}

void TerrainBase::decoupeSimple()
{
    int i = 0;
#ifndef QT_NO_DEBUG
    int i2 = 0;
#endif
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();   
#ifndef QT_NO_DEBUG
        std::cout << aire << std::endl;
#endif
        if(aire < AIRE_QUARTIER_MAX)
            i++;
        else
        {
            std::pair<Quartier*,Quartier*> quar2 = quartier->decoupeSimple();

            delete quartier;
            quartiers[i] = quar2.first;
            quartiers.push_back(quar2.second);
#ifndef QT_NO_DEBUG
            i2++;
#endif
        }
    }
}


void TerrainBase::decoupe()
{
    int i = 0;
#ifndef QT_NO_DEBUG
    int i2 = 0;
#endif
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();
#ifndef QT_NO_DEBUG
        std::cout << aire << std::endl;
#endif
        if(aire < AIRE_QUARTIER_MAX)
            i++;
        else
        {
            std::pair<Quartier*,Quartier*> quar2 = quartier->decoupe();

            delete quartier;
            quartiers[i] = quar2.first;
            quartiers.push_back(quar2.second);
#ifndef QT_NO_DEBUG
            i2++;
#endif
        }
    }
}

/**redécoupe tous les quartiers en Bâtiments*/
void TerrainBase::split()
{
    for(Quartier* q: quartiers)
        q->split();
}

void TerrainBase::shrink(float f)
{
    for(Quartier* q: quartiers)
        q->shrink(f);
}

Mesh TerrainBase::generate()
{
    if(quartiers.empty())
        return Mesh();

    Mesh m = quartiers[0]->generate();
    for(size_t i = 1;  i < quartiers.size();   i++)
        m.merge(quartiers[i]->generate());
    return m;
}
