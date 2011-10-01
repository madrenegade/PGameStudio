#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Vector3.h"

struct Camera
{
    std::string name;

    Math::Vector3 position;
    Math::Vector3 lookAt;
    Math::Vector3 up;
};

#endif // CAMERA_H
