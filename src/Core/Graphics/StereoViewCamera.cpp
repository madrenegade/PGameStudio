/* 
 * File:   StereoViewCamera.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 4:54 PM
 */

#include "Graphics/StereoViewCamera.h"

namespace Graphics
{

    StereoViewCamera::StereoViewCamera(double fieldOfView, double aspectRatio, double zNear, double zFar)
    : MultiViewCamera(fieldOfView, aspectRatio, zNear, zFar)        
    {
    }

    StereoViewCamera::~StereoViewCamera()
    {
    }
}

