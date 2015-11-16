#include "quartier.h"


Quartier::Quartier(BatParameter* par):    _par(par)
{
    generator = std::default_random_engine(4546);
}

Mesh Quartier::generate()
{
    /*if(batiments.empty())
        return Mesh();

    Mesh m = batiments[0].generate();
    for(size_t i = 1;  i < batiments.size();   i++)
        m.merge(batiments[i].generate());
    return m;*/
    const std::vector<Vector3D>& points = getPoints3D();
    std::vector<unsigned int> faces;
    faces.push_back(0); faces.push_back(1); faces.push_back(2);

    switch(points.size())
    {
        case 5:
            faces.push_back(0); faces.push_back(3); faces.push_back(4);
        case 4:
            faces.push_back(0); faces.push_back(2); faces.push_back(3);
            break;
    }
    return Mesh(points, faces);
}
