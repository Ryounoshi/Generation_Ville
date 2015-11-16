#ifndef BATPARAMETER_H
#define BATPARAMETER_H
#include "geometrie/vector3d.h"
#define DEFAULT_MAX_ETAGE 12
#define DEFAULT_INFLUENCE_CENTREVILLE 1
#define DEFAULT_LARGEUR_TROTOIR 0.5
#define DEFAULT_LARGEUR_BATIMENT 3
#define DEFAULT_LARGEUR_RUELLE 1
#define DEFAULT_HAUTEUR_ETAGE 1


class BatParameter
{
public:
    BatParameter();
    BatParameter(Vector3D centreVille):_centreVille(centreVille){}
    Vector3D _centreVille;
    float influenceCentreVille = DEFAULT_INFLUENCE_CENTREVILLE;
    int maxEtage = DEFAULT_MAX_ETAGE;
    int splitPourcent = 50;

    float largeurTrotoir = DEFAULT_LARGEUR_TROTOIR;
    float largeurBatiment = DEFAULT_LARGEUR_BATIMENT;
    float largeurRuelle = DEFAULT_LARGEUR_RUELLE;

    float hauteurEtage = DEFAULT_HAUTEUR_ETAGE;

    //à changer de place !!! très moche ici !!!
    Vector3D hauteurEtageLePlusHaut;
    int etageLePlusHaut=0;

    void updateEtageLePlusHaut(Vector3D otherHauteur = Vector3D(), int otherEtage = 0);
    void resetEtageLePlusHaut();
};

#endif // BATPARAMETER_H
