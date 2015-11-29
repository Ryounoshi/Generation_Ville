#ifndef BATPARAMETER_H
#define BATPARAMETER_H
#include "geometrie/vector3d.h"
#define DEFAULT_MAX_ETAGE 12
#define DEFAULT_INFLUENCE_CENTREVILLE 1
#define DEFAULT_LARGEUR_TROTOIR 1
#define DEFAULT_LARGEUR_RUELLE 1
#define DEFAULT_HAUTEUR_ETAGE 3


//types d'étage
#define E 0     //etage normal
#define ES 1    //etage Splité
#define ET 2    //etage twisté
#define ER 3    //etage réduit
#define ER2 5    //etage réduit 2
#define ERS 4    //etage réduit smooth

//types de toit


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
    float largeurRuelle = DEFAULT_LARGEUR_RUELLE;

    float hauteurEtage = DEFAULT_HAUTEUR_ETAGE;
    float minLargeurBatiment = hauteurEtage*3;
    float maxLargeurBatiment = hauteurEtage*5;

    Vector3D hauteurEtageLePlusHaut;
    int etageLePlusHaut=0;

    void updateEtageLePlusHaut(Vector3D otherHauteur = Vector3D(), int otherEtage = 0);
    void resetEtageLePlusHaut();
};

#endif // BATPARAMETER_H
