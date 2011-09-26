/* 
 * File:   StereoViewCamera.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 4:54 PM
 */

#ifndef GRAPHICS_STEREOVIEWCAMERA_H
#define	GRAPHICS_STEREOVIEWCAMERA_H

#include "Graphics/MultiViewCamera.h"

namespace Graphics
{

    class StereoViewCamera : public MultiViewCamera
    {
    public:
        StereoViewCamera(double fieldOfView, double aspectRatio, double zNear, double zFar);
        virtual ~StereoViewCamera();
    };
}

#endif	/* STEREOVIEWCAMERA_H */

