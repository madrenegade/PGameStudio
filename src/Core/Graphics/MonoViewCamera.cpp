/*
 * File:   MonoViewCamera.cpp
 * Author: madrenegade
 *
 * Created on September 26, 2011, 4:56 PM
 */

#include "Graphics/MonoViewCamera.h"

namespace Graphics
{

    MonoViewCamera::MonoViewCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar)
        : MultiViewCamera(fieldOfView, aspectRatio, zNear, zFar)
    {
    }

    MonoViewCamera::~MonoViewCamera()
    {
    }
}

