#ifndef INTERFACE_VILLE_H
#define INTERFACE_VILLE_H

#include "modele/mesh.h"

class Interface_Ville
{
public:
    virtual Mesh generate() =0;
};

#endif // INTERFACE_VILLE_H
