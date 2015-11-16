#include "rayon.h"

Rayon::Rayon()
{

}

Rayon::Rayon(const Vector3D &origine, const Vector3D &direction):
        _origine(origine),  _direction(direction.normalized())
{
}

Vector3D Rayon::Reflect(const Vector3D& normal) {
    const float cosI = normal.dotProduct(_direction);
    return _direction + normal * 2*cosI;
}
