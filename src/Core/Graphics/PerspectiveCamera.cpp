/* 
 * File:   PerspectiveCamera.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 4:49 PM
 */

#include "Graphics/PerspectiveCamera.h"

namespace Graphics
{

    PerspectiveCamera::PerspectiveCamera(const double fieldOfView, const double aspectRation, const double zNear, const double zFar)
    : lookAt(0, 0, -1), up(0, 1, 0),
    projection(Math::Matrix4(Math::Matrix4::CreatePerspectiveFieldOfView(Math::PI * fieldOfView / 180.0, aspectRation, zNear, zFar)))
    {
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::setLookAt(const Math::Vector3& lookAt)
    {
        viewMatrixDirty = true;
        this->lookAt = lookAt;
    }

    void PerspectiveCamera::setUp(const Math::Vector3& up)
    {
        viewMatrixDirty = true;
        this->up = up;
    }

    const Math::Vector3& PerspectiveCamera::getLookAt() const
    {
        return lookAt;
    }

    const Math::Vector3& PerspectiveCamera::getUp() const
    {
        return up;
    }

    const Math::Matrix4& PerspectiveCamera::getProjectionMatrix() const
    {
        return projection;
    }
    
    void PerspectiveCamera::update()
    {
        if(viewMatrixDirty)
        {
            updateViewMatrix(Math::Matrix4::LookAt(getPosition(), lookAt, up));
        }
    }
}
