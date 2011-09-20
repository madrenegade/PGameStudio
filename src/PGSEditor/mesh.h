#ifndef MESH_H
#define MESH_H

#include "material.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <vector>

struct Face
{
    std::vector<unsigned int> indexes;
};

struct Mesh
{
    std::vector<Math::Vector3> positions;
    std::vector<Math::Vector3> normals;
    std::vector<Math::Vector3> tangents;
    std::vector<Math::Vector3> bitangents;

    std::vector<std::vector<Math::Vector2> > texCoords;

    std::vector<Face> faces;

    Material material;
};

#endif // MESH_H
