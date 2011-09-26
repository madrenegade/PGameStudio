/* 
 * File:   MultiViewCamera.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 4:52 PM
 */

#include "Graphics/MultiViewCamera.h"

namespace Graphics
{

    MultiViewCamera::MultiViewCamera(double fieldOfView, double aspectRatio, double zNear, double zFar)
    : PerspectiveCamera(fieldOfView, aspectRatio, zNear, zFar)
    {
    }

    MultiViewCamera::~MultiViewCamera()
    {
    }
}
