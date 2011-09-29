/* 
 * File:   MultiViewCamera.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 4:52 PM
 */

#include "Graphics/MultiViewCamera.h"

namespace Graphics
{

    MultiViewCamera::MultiViewCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar)
    : PerspectiveCamera(fieldOfView, aspectRatio, zNear, zFar)
    {
    }

    MultiViewCamera::~MultiViewCamera()
    {
    }
}
