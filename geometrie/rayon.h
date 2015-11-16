#ifndef RAYON_H
#define RAYON_H

#include <math.h>
#include "vector3d.h"

/**
 * @brief Classe représentant un rayon lumineux
 */
class Rayon
{
protected:
    /**
     * @brief position d'origine du rayon.
     */
    Vector3D _origine;
    /**
     * @brief direction du rayon.
     */
    Vector3D _direction;

public:

    Rayon();

    /**
     * @brief Constructeur paramètré.
     * @param[in] Position d'origine du rayon.
     * @param[in] Vecteur direction du rayon.
     */
    Rayon(const Vector3D& origine, const Vector3D& direction);

    /**
     * @brief Calcul la direction du rayon réfléchie par rapport à une surface.
     * @param[in] normal La normale à de la surface.
     * @return Le vecteur direction du rayon après réflection.
     */
    Vector3D Reflect(const Vector3D &normal);

    inline Vector3D getOrigine()const{return _origine;}

    inline Vector3D getDirection()const{return _direction;}
    inline void setDirection(const Vector3D& dir){ _direction = dir.normalized();   }

};

#endif // RAYON_H
