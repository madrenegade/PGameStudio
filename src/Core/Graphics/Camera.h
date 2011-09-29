/* 
 * File:   Camera.h
 * Author: madrenegade
 *
 * Created on September 20, 2011, 8:13 AM
 */

#ifndef GRAPHICS_CAMERA_H
#define	GRAPHICS_CAMERA_H

#include "Math/Matrix4.h"

namespace Graphics
{

    class Camera
    {
    public:
        virtual ~Camera();

        virtual unsigned int getViewCount() const;
        virtual void activateView(const unsigned int index);

        const Math::Matrix4& getViewMatrix() const;
        virtual const Math::Matrix4& getProjectionMatrix() const = 0;

        void setPosition(const Math::Vector3& position);
        const Math::Vector3& getPosition() const;
        
        virtual void update();

    protected:
        Camera();
        
        void updateViewMatrix(const Math::Matrix4& m);
        
        bool viewMatrixDirty;

    private:
        Math::Vector3 position;
        
        Math::Matrix4 view;
    };
}

#endif	/* GRAPHICS_CAMERA_H */

