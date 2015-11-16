#ifndef BAT_PARAMETER_H
#define BAT_PARAMETER_H
#include "geometrie/vector3d.h"
#define DEFAULT_MAX_ETAGE 12
#define DEFAULT_INFLUENCE_CENTREVILLE 1


class Bat_Parameter
{
public:
    Bat_Parameter() {}
    Bat_Parameter(const Vector3D &centreVille) : centreVille(centreVille){}
    Vector3D centreVille;
    float influenceCentreVille = DEFAULT_INFLUENCE_CENTREVILLE;
    int maxEtage = DEFAULT_MAX_ETAGE;
};

#endif // BAT_PARAMETER_H
