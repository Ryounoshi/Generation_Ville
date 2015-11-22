#include "terrainbase.h"

TerrainBase::TerrainBase(float longueur, float largeur, BatParameter *par):
        longueur(longueur),  largeur(largeur), _par(par)
{
    float long2 = longueur/2, larg2 = largeur/2;
    QuarQuad* quad = new QuarQuad(Vector2D(-larg2,-long2), Vector2D(-larg2,long2), Vector2D(larg2, long2), Vector2D(larg2,-long2), _par);
    quartiers.push_back(quad);
}

TerrainBase::~TerrainBase()
{
    for(unsigned int i = 0;  i < quartiers.size();  i++)
        delete quartiers[i];
}

void TerrainBase::decoupeSimple(float aireMax)
{
    #ifndef QT_NO_DEBUG
        int i2 =0;
    #endif
    int i = 0;
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();
        #ifndef QT_NO_DEBUG
            std::cout << aire << std::endl;
            if(aire < 10 && aire > 10000000)
                std::cout << "trop petit" << std::endl;
        #endif
        if(aire < aireMax)    {
            i++;
            #ifndef QT_NO_DEBUG
                std::cout << std::endl << i << std::endl;
            #endif
        }
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


void TerrainBase::decoupe(float aireMax)
{
    #ifndef QT_NO_DEBUG
        int i2 =0;
    #endif
    int i = 0;
    while(i < (int)quartiers.size())
    {
        Quartier* quartier = quartiers[i];
        float aire = quartier->area();
        #ifndef QT_NO_DEBUG
            std::cout << aire << std::endl;
            if(aire < 10 && aire > 10000000)
                std::cout << "trop petit" << std::endl;
        #endif
        if(aire < aireMax)    {
            i++;
            #ifndef QT_NO_DEBUG
                std::cout << std::endl << i << std::endl;
            #endif
        }
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


void TerrainBase::shrink(float f)
{
    for(Quartier* q: quartiers)
        q->shrink(f);
}

void TerrainBase::supprPetitQuartier(float f)
{
    std::vector<Quartier*> quartiers2;
    quartiers2.reserve(quartiers.size());
    for(Quartier* q: quartiers){
        if(q->quartierCorrect() || q->area() >= f)
            quartiers2.push_back(q);
        else
            delete q;
    }
    quartiers2.shrink_to_fit();
    quartiers = quartiers2;
}

Mesh TerrainBase::generate()
{
    if(quartiers.empty())
        return Mesh();

    Mesh m = quartiers[0]->generate();
    for(size_t i = 1;  i < quartiers.size();   i++){
        m.merge(quartiers[i]->generate());
    }
    return m;
}
