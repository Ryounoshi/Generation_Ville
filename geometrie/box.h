#ifndef BOX_H
#define BOX_H

#include "float.h"  //FLT_MIN FLT_MAX
#include <iostream>
#include "rayon.h"
#include <vector>
#include "geometrie/vector3d.h"

/**
 * @brief Classe d'un objet géométrique de type boite. \n Il sert de boite englobante pour les objets.
 */
class Box
{
public:

    Box();

    Box(const Vector3D& _min, const Vector3D& _max);

    /**
     * @brief Constructeur qui utilisera un ensemble de points pour calculer la boite englobante correspondante. \n
     * Le constructeur passe le relai à la fonction parcourtPoints().
     * @param[in] points Tableau de position de points d'un objet.
     */
    Box(const std::vector<Vector3D>& points);

    /**
     * @brief Détermine si la boite englobante doit être modifiée pour comprendre le point \e p. \n
     * Si c'est le cas la boite s'adapte pour contenir le point. \n
     * Passe le relai à la méthode update().
     * @param[in] p un point dans l'espace x, y, z.
     */
    void updatePoint(const Vector3D& p);

    /**
     * @brief Test si le point \e p est dans l'espace compris de la boite.
     * @param[in] p un point dans l'espace x, y, z.
     * @return Le resultat du test. True = dedans, false = dehors.
     */
    bool inOut(const Vector3D& p) const;

    /**
     * @brief Test si un rayon traverse la boite. \n
     * Si c'est le cas, la methode retournera les distance d'intersection sur la boite. (cf. Rayon) \n
     * Utilise la méthode intersectIn().
     * @param[in] r Un rayon quelconque. (cf. Rayon)
     * @param[out] distanceMin coefficient de distance du premier impacte sur la boite par rapport à l'origine du rayon. \n
     * Le coefficient est dependant de la norme du vecteur direction du rayon.
     * @param[out] distanceMax coefficient de distance du second impacte sur la boite par rapport à l'origine du rayon. \n
     * Le coefficient est dependant de la norme du vecteur direction du rayon.
     * @return Le resultat du test. True = intersection, false = pas d'intersection.
     */
    bool intersect(const Rayon &r, float &distanceMin, float &distanceMax) const;

    /**
     * @brief Calcul la hauteur en \e z de la boite.
     * @return la hauteur en \e z.
     */
    float diffZ() const;

    /**
     * @brief Fait l'union entre deux boites, et redéfini min et max pour englober les deux boites.
     * @param[in] box2 Une seconde boite.
     */
    void merge(const Box& box2);

    /**
     * @brief Opère un translation rectiligne de la boite.
     * @param[in] t Vecteur de translation de la boite.
     */
    void operator+=(const Vector3D& t);

    /**
     * @brief distance
     * @param p un point de l'espace
     * @return la distance minimale entre la box et le point
     */
    float distance(const Vector3D &p) const;


    Vector3D getNormal(const Vector3D& p) const;


protected:

    /**
     * @brief min Position d'un des points de la boite.
     */
    Vector3D min;
    /**
     * @brief max Position du point opposé au point \a min sur la boite.
     */
    Vector3D max;


private:

    /**
     * @brief Initialise la boite avec des valeurs par defaut.
     */
    inline void setDefaultBox();

    /**
     * @brief Détermine si la boite englobante doit être modifiée pour comprendre le point \e p. \n
     * Si c'est le cas la boite s'adapte pour contenir le point. \n
     * Passe le relai à la méthode updateMin() et updateMax().
     * @param[in] p un point dans l'espace x, y, z.
     */
    inline void update(const Vector3D& p);

    /**
     * @brief Détermine si le point min doit être modifiée pour comprendre le point \e p. \n
     * Si c'est le cas le point min s'adapte pour contenir le point. \n
     * @param[in] p un point dans l'espace x, y, z.
     */
    inline void updateMin(const Vector3D& p);

    /**
     * @brief Détermine si le point max doit être modifiée pour comprendre le point \e p. \n
     * Si c'est le cas le point max s'adapte pour contenir le point. \n
     * @param[in] p un point dans l'espace x, y, z.
     */
    inline void updateMax(const Vector3D& p);

    /**
     * @brief Détermine la positions de min et max pour englober tous les points de \e points.
     * @param[in] points Un ensemble de points.
     */
    inline void parcourtPoints(const std::vector<Vector3D>& points);

    /**
     * @brief Test si le rayon r traverse la boite.
     * @param[in] r Un rayon quelconque. (cf. Rayon)
     * @return Le test d'intersection entre la boite et \e r.
     */
    inline float intersectIn(const Rayon& r) const;
};

#endif // BOX_H
