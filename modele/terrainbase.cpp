#include "terrainbase.h"

TerrainBase::TerrainBase(float longueur, float largeur):
        longueur(longueur),  largeur(largeur)
{
    //QuarQuad* quad = new QuarQuad(Vector2D(0,0), Vector2D(0,longueur), Vector2D(largeur, longueur), Vector2D(largeur,0));
    //quartiers.push_back(quad);
}

TerrainBase::~TerrainBase()
{
    for(unsigned int i = 0;  i < quartiers.size();  i++)
        delete quartiers[i];
}

void TerrainBase::decoupeSimple()
{
    int i2 =0;
    int i = 0;
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();
        std::cout << aire << std::endl;
        if(aire < AIRE_QUARTIER_MAX)    {
            i++;
            std::cout << std::endl;
        }
        else
        {
            std::pair<Quartier*,Quartier*> quar2 = quartier->decoupeSimple();


            delete quartier;
            quartiers[i] = quar2.first;
            quartiers.push_back(quar2.second);
            i2++;
        }
    }
}


void TerrainBase::decoupe()
{
    int i2 =0;
    int i = 0;
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();
        std::cout << aire << std::endl;
        if(aire < AIRE_QUARTIER_MAX)    {
            i++;
            std::cout << std::endl;
        }
        else
        {
            std::pair<Quartier*,Quartier*> quar2 = quartier->decoupe();


            delete quartier;
            quartiers[i] = quar2.first;
            quartiers.push_back(quar2.second);
            i2++;
        }
    }
}


void TerrainBase::shrink(float f)
{
    for(Quartier* q: quartiers)
        q->shrink(f);
}
