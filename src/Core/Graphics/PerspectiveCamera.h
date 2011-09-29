/* 
 * File:   PerspectiveCamera.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 4:49 PM
 */

#ifndef GRAPHICS_PERSPECTIVECAMERA_H
#define	GRAPHICS_PERSPECTIVECAMERA_H

#include "Graphics/Camera.h"

#include "Math/Vector3.h"
#include "Math/Matrix4.h"

namespace Graphics
{

    class PerspectiveCamera : public Camera
    {
    public:
        virtual ~PerspectiveCamera();

        void setLookAt(const Math::Vector3& lookAt);
        void setUp(const Math::Vector3& up);

        const Math::Vector3& getLookAt() const;
        const Math::Vector3& getUp() const;
        
        virtual const Math::Matrix4& getProjectionMatrix() const;
        
        virtual void update();

    protected:
        PerspectiveCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar);

    private:
        Math::Vector3 lookAt;
        Math::Vector3 up;
        
        const Math::Matrix4 projection;
    };
}

#endif	/* GRAPHICS_PERSPECTIVECAMERA_H */

