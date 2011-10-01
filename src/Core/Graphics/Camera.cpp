/*
 * File:   Camera.cpp
 * Author: madrenegade
 *
 * Created on September 20, 2011, 8:13 AM
 */

#include "Graphics/Camera.h"
#include "Core/Events/EventManager.h"

namespace Graphics
{
    Camera::Camera()
        : viewMatrixDirty(false)
    {

    }

    Camera::~Camera()
    {
    }

    unsigned int Camera::getViewCount() const
    {
        return 1;
    }

    void Camera::activateView(const unsigned int)
    {

    }

    const Math::Matrix4& Camera::getViewMatrix() const
    {
        return view;
    }

    void Camera::setPosition(const Math::Vector3& position)
    {
        viewMatrixDirty = true;
        this->position = position;
    }

    const Math::Vector3& Camera::getPosition() const
    {
        return position;
    }

    void Camera::updateViewMatrix(const Math::Matrix4& m)
    {
        view = m;

        viewMatrixDirty = false;
    }

    void Camera::update()
    {

    }

    void Camera::registerEvents(Core::Events::EventManager* const eventManager)
    {
        Core::Events::EventID positionChanged = eventManager->registerEvent("CAMERA_POSITION_CHANGED");
        eventManager->registerEventHandler(positionChanged, boost::bind(&Camera::onPositionChanged, this, _1, _2));
    }

    void Camera::onPositionChanged(const Core::Events::EventID&, const boost::any& data)
    {
        setPosition(boost::any_cast<Math::Vector3>(data));
    }
}
