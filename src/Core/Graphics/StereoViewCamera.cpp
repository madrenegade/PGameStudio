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

    StereoViewCamera::StereoViewCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar,
                                       const double eyeSeparation)
        : MultiViewCamera(fieldOfView, aspectRatio, zNear, zFar), OFFSET(eyeSeparation / 2.0)
    {
    }

    StereoViewCamera::~StereoViewCamera()
    {
    }

    unsigned int StereoViewCamera::getViewCount() const
    {
        return 2;
    }

    void StereoViewCamera::activateView(const unsigned int index)
    {
        const Math::Vector3 dir(getLookAt() - getPosition());

        Math::Vector3 left(dir.Cross(getUp()));
        left.Normalize();
        left *= OFFSET;

        switch (index)
        {
        case LEFT:
            updateViewMatrix(Math::Matrix4::LookAt(getPosition() - left, getLookAt(), getUp()));
            break;

        case RIGHT:
            updateViewMatrix(Math::Matrix4::LookAt(getPosition() + left, getLookAt(), getUp()));
            break;

        default:
            LOG(FATAL) << "Invalid view index for stereo view: " << index;
            break;
        }
    }
}

