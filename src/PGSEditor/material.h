#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Math/Vector4.h"

struct Material
{
    unsigned int index; // automatically set during export

    std::string name;

    Math::Vector4 diffuse;
    Math::Vector4 specular;

    std::vector<std::string> textures;
};

#endif // MATERIAL_H
