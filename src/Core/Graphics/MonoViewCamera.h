/*
 * File:   MonoViewCamera.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 4:56 PM
 */

#ifndef GRAPHICS_MONOVIEWCAMERA_H
#define	GRAPHICS_MONOVIEWCAMERA_H

#include "Graphics/MultiViewCamera.h"

namespace Graphics
{

    class MonoViewCamera : public MultiViewCamera
    {
    public:
        MonoViewCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar);
        virtual ~MonoViewCamera();
    };
}

#endif	/* GRAPHICS_MONOVIEWCAMERA_H */

