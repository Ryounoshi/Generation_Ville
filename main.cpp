#include <iostream>

#include "geometrie/Triangle.h"
#include "geometrie/quadrangle.h"
#include "geometrie/vector2d.h"
#include "modele/batiment/rezdechausse.h"
#include <qdebug.h>
#include "modele/batiment/batiment.h"
#include "modele/mesh.h"
#include "geometrie/vector3d.h"
#include "import_export/objmanager.h"
#include "rendu/mywindow.h"
#include "modele/quartier/patern/paternequad.h"
#include "QDebug"

#include "modele/terrainbase.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
    Mesh m1;
    int largeur,longueur;
    largeur = 40;
    longueur = 40;
    for(int i=-largeur/2;i<largeur/2;i+=2){
        for(int j=-longueur/2; j<longueur/2; j+=2){
            cout << "Batiment " << i << "," << j << " :" << endl;
            Batiment test(Vector3D(i+(rand()%100)*0.002,j+(rand()%100)*0.002,0),
                          Vector3D(i+(rand()%100)*0.002,j+1+(rand()%100)*0.002,0),
                          Vector3D(i+1+(rand()%100)*0.002,j+1+(rand()%100)*0.002,0),
                          Vector3D(i+1+(rand()%100)*0.002,j+(rand()%100)*0.002,0),
                          1,
                          Vector3D(4,4,0));
            m1.merge(test.generate());
        }
    }
    ObjManager::writeToObj("test1.obj", m1.getvertex(), m1.getface());
    */



    myWindow glWin;
    glWin.show();
    return app.exec();

    /*
    BatParameter par(Vector3D(0,0,0));
    par.etageLePlusHaut = 20;
    par.hauteurEtage = 3;
    par.influenceCentreVille = 100;
    par.largeurTrotoir = 2;
    par.largeurRuelle = 2;
    par.minLargeurBatiment = 6;
    par.maxLargeurBatiment = 15;

    std::vector<TerrainBase> bases;
    bases.push_back(TerrainBase(Triangle(Vector2D(0,200),Vector2D(200,-200),Vector2D(-200,-200)), &par));
    bases.push_back(TerrainBase(Quadrangle(Vector2D(0,200),Vector2D(200,400),Vector2D(400,200),Vector2D(200,-200)), &par));
    bases.push_back(TerrainBase(Quadrangle(Vector2D(200,-200),Vector2D(200,-400),Vector2D(-200,-400),Vector2D(-200,-200)), &par));
    bases.push_back(TerrainBase(Quadrangle(Vector2D(-200,-200),Vector2D(-400,200),Vector2D(-200,400),Vector2D(0,200)), &par));
    Mesh _mesh;
    for(TerrainBase& base : bases)
    {
        base.decoupeSimple(4000);
        base.shrink(2.f);
        _mesh.merge(base.generate());
    }

    std::cout << "fin de la création du mesh" << std::endl;    
    ObjManager::writeToObj("testTerrain.obj", _mesh.getVertex(), _mesh.getFace());

    //return 0;*/
}


//TerrainBase base(400,400, &par);
/*TerrainBase base(Triangle(Vector2D(0,200),Vector2D(200,-200),Vector2D(-200,-200)), &par);
base.decoupeSimple(4000);
base.shrink(2.f);
Mesh m = base.generate();*/

/*
    TerrainBase base(1000,1000);
    base.decoupe();
    base.shrink(1.f);
    return 0;
*/
