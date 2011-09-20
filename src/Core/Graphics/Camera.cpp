/* 
 * File:   Camera.cpp
 * Author: madrenegade
 * 
 * Created on September 20, 2011, 8:13 AM
 */

#include "Graphics/Camera.h"

namespace Graphics
{

    Camera::Camera(const Math::Vector3& position,
                   const Math::Vector3& lookAt,
                   const Math::Vector3& up)
    : position(position), lookAt(lookAt), up(up)
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::setPosition(const Math::Vector3& position)
    {
        this->position = position;
    }

    void Camera::setLookAt(const Math::Vector3& lookAt)
    {
        this->lookAt = lookAt;
    }

    void Camera::setUp(const Math::Vector3& up)
    {
        this->up = up;
    }

    const Math::Vector3& Camera::getPosition() const
    {
        return position;
    }

    const Math::Vector3& Camera::getLookAt() const
    {
        return lookAt;
    }

    const Math::Vector3& Camera::getUp() const
    {
        return up;
    }

    const Math::Matrix4 Camera::getViewMatrix() const
    {
        return Math::Matrix4::LookAt(position, lookAt, up);
    }
}
