#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include "geometrie/vector3d.h"
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

namespace ObjManager
{
    void writeToObj(const std::string &name, const std::vector<Vector3D>& vertex, const std::vector<unsigned int>& face);
}

#endif // OBJMANAGER_H
