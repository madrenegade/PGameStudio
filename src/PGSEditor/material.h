#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Math/Vector4.h"

struct Material
{
    std::string name;

    Math::Vector4 diffuse;

    double shininess;
};

#endif // MATERIAL_H
