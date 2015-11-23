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
    /*
    Mesh m1;
    PaterneQuadResidence p1(Vector2D(0,0), Vector2D(0,10), Vector2D(10,10), Vector2D(10,0), 2.5);
    m1 = p1.generate();
*/
    /*myWindow glWin;
    glWin.show();
    return app.exec();*/

    BatParameter par(Vector3D(0,0,0));
    par.etageLePlusHaut = 20;
    par.hauteurEtage = 5;
    par.influenceCentreVille = 100;
    par.largeurTrotoir = 3;
    par.largeurRuelle = 2;
    par.minLargeurBatiment = 6;
    par.maxLargeurBatiment = 10;

    TerrainBase base(1000,1000, &par);
    base.decoupeSimple(4000);
    base.shrink(4.f);
    base.supprPetitQuartier(200);
    Mesh m = base.generate();

    std::cout << "fin de la création du mesh" << std::endl;
    ObjManager::writeToObj("testTerrain.obj", m.getVertex(), m.getFace());

    //return 0;
}




/*
    TerrainBase base(1000,1000);
    base.decoupe();
    base.shrink(1.f);
    return 0;
*/
