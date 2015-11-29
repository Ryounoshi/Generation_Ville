#include "terrainbase.h"

TerrainBase::TerrainBase(float longueur, float largeur, BatParameter *par):
        _par(par)
{
    float long2 = longueur/2, larg2 = largeur/2;
    QuarQuad* quad = new QuarQuad(Vector2D(-larg2,-long2), Vector2D(-larg2,long2), Vector2D(larg2, long2), Vector2D(larg2,-long2), _par);
    quartiers.push_back(quad);
}

TerrainBase::TerrainBase(const Quadrangle& q, BatParameter* par):
        _par(par)
{
    QuarQuad* quad = new QuarQuad(q.get(0),q.get(1),q.get(2),q.get(3), _par);
    quartiers.push_back(quad);
}

TerrainBase::TerrainBase(const Triangle& q, BatParameter* par):
        _par(par)
{
    QuarTri* tri = new QuarTri(q.get(0),q.get(1),q.get(2), _par);
    quartiers.push_back(tri);
}

//faire un std::vector<TerrainBase> appelle le destructeur lors du redimensionnement du vector si ce constructeur n'existe pas
TerrainBase::TerrainBase(TerrainBase&& base):
        _par(base._par),    quartiers(base.quartiers)
{
    base._par = nullptr;
    base.quartiers.clear();

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

/**retourne les sommets de tous les quartiers du terrain.
utilisé avant le découpage pour avoir la periphérie du terrain et pouvoir faire le support de route sur toute la surface*/
std::vector<Vector2D> TerrainBase::getPoints() const
{
    std::vector<Vector2D> points;
    points.reserve(quartiers.size()*4);
    for(const Quartier* q: quartiers)
    {
        std::vector<Vector2D> p2 = q->getPoints();
        for(Vector2D p: p2)
            points.push_back(p);
    }
    return points;
}

/**crée le mesh vertical de tous les trottoirs des quartiers.
à utiliser après la découpe et le shrink*/
/*Mesh TerrainBase::meshTrottoir(float hauteur)
{
    int ref = 0;
    Mesh m;
    m.vertex.reserve(quartiers.size()*8);   //2points*4arêtesVerticalesMax
    m.face.reserve(quartiers.size()*24);    //3ref*2faces*4côtésMax
    for(const Quartier* q: quartiers)
    {
        std::vector<Vector2D> points = q->getPoints();
        const int nbP = points.size();
        int ref2 = 0;
        for(const Vector2D& p: points)
        {
            m.addVertex(Vector3D(XY(p),hauteur));
            m.addVertex(Vector3D(XY(p),0));

            m.addFace(ref+ref2, ref+ref2+1, ref+(ref2+2)%nbP);
            m.addFace(reg+ref2, ref+(ref2+2)%nbP, ref+(ref2+3)%nbP);

            ref2+=2;
        }
        ref+=nbP;
    }
    return Mesh(pointsRes, faces);
}*/
