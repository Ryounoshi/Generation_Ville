#include "batparameter.h"

BatParameter::BatParameter()
{

}

void BatParameter::updateEtageLePlusHaut(Vector3D otherHauteur, int otherEtage){
    hauteurEtageLePlusHaut = otherHauteur.z > hauteurEtageLePlusHaut.z ? otherHauteur : hauteurEtageLePlusHaut;
    etageLePlusHaut = otherEtage > etageLePlusHaut ? otherEtage : etageLePlusHaut;
}

void BatParameter::resetEtageLePlusHaut(){
    hauteurEtageLePlusHaut = Vector3D();
    etageLePlusHaut = 0;
}
