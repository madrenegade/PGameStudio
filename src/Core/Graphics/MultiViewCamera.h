/* 
 * File:   MultiViewCamera.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 4:52 PM
 */

#ifndef GRAPHICS_MULTIVIEWCAMERA_H
#define	GRAPHICS_MULTIVIEWCAMERA_H

#include "Graphics/PerspectiveCamera.h"

namespace Graphics
{

    class MultiViewCamera : public PerspectiveCamera
    {
    public:

        virtual ~MultiViewCamera();

    protected:
        MultiViewCamera(double fieldOfView, double aspectRatio, double zNear, double zFar);
    };
}

#endif	/* GRAPHICS_MULTIVIEWCAMERA_H */

