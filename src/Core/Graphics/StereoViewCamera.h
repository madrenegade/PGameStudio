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
        StereoViewCamera(const double fieldOfView, const double aspectRatio, const double zNear, const double zFar,
                         const double eyeSeparation);
        virtual ~StereoViewCamera();
        
        virtual unsigned int getViewCount() const;
        virtual void activateView(const unsigned int index);
        
    private:
        static const unsigned int LEFT;
        static const unsigned int RIGHT;
        
        const double OFFSET;
    };
}

#endif	/* STEREOVIEWCAMERA_H */

