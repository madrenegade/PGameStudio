/* 
 * File:   StereoViewCamera.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 4:54 PM
 */

#include "Graphics/StereoViewCamera.h"

#include <glog/logging.h>

namespace Graphics
{
    const unsigned int StereoViewCamera::LEFT = 0;
    const unsigned int StereoViewCamera::RIGHT = 1;

    StereoViewCamera::StereoViewCamera(double fieldOfView, double aspectRatio, double zNear, double zFar)
    : MultiViewCamera(fieldOfView, aspectRatio, zNear, zFar)
    {
    }

    StereoViewCamera::~StereoViewCamera()
    {
    }

    unsigned int StereoViewCamera::getViewCount() const
    {
        return 2;
    }

    void StereoViewCamera::activateView(unsigned int index)
    {
        Math::Vector3 p(getPosition());
        Math::Vector3 l(getLookAt());
        
        switch (index)
        {
            case LEFT:
                updateViewMatrix(Math::Matrix4::LookAt(Math::Vector3(p.X - 1, p.Y, p.Z), Math::Vector3(l.X - 1, l.Y, l.Z), getUp()));
                break;

            case RIGHT:
                updateViewMatrix(Math::Matrix4::LookAt(Math::Vector3(p.X + 1, p.Y, p.Z), Math::Vector3(l.X + 1, l.Y, l.Z), getUp()));
                break;

            default:
                LOG(FATAL) << "Invalid view index for stereo view: " << index;
                break;
        }
    }
}

