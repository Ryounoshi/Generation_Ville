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
    myWindow glWin;
    glWin.show();
    return app.exec();
}
