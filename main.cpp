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
#include "modele/quartier/patern/paternequadresidence.h"
#include "QDebug"

#include "modele/terrainbase.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
    Mesh m1;ss
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
    TerrainBase base(2000,2000,new BatParameter());
    base.decoupeSimple();
    base.shrink(6.f);
    Mesh m = base.generate();
    ObjManager::writeToObj("testTerrain.obj", m.getVertex(), m.getFace());
    return 0;
}




/*
    TerrainBase base(1000,1000);
    base.decoupe();
    base.shrink(1.f);
    return 0;
*/
