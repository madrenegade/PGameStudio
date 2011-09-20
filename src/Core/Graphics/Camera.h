/* 
 * File:   Camera.h
 * Author: madrenegade
 *
 * Created on September 20, 2011, 8:13 AM
 */

#ifndef GRAPHICS_CAMERA_H
#define	GRAPHICS_CAMERA_H

#include "Math/Vector3.h"
#include "Math/Matrix4.h"

namespace Graphics
{

    class Camera
    {
    public:
        Camera(const Math::Vector3& position = Math::Vector3(0, 0, 0),
               const Math::Vector3& lookAt = Math::Vector3(0, 0, -1),
               const Math::Vector3& up = Math::Vector3(0, 1, 0));
        ~Camera();
        
        void setPosition(const Math::Vector3& position);
        void setLookAt(const Math::Vector3& lookAt);
        void setUp(const Math::Vector3& up);
        
        const Math::Vector3& getPosition() const;
        const Math::Vector3& getLookAt() const;
        const Math::Vector3& getUp() const;
        
        const Math::Matrix4 getViewMatrix() const;
        
    private:
        Math::Vector3 position;
        Math::Vector3 lookAt;
        Math::Vector3 up;
    };
}

#endif	/* GRAPHICS_CAMERA_H */

