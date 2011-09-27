/* 
 * File:   Viewport.h
 * Author: madrenegade
 *
 * Created on September 25, 2011, 8:52 PM
 */

#ifndef RENDERER_VIEWPORT_H
#define RENDERER_VIEWPORT_H

#include <boost/shared_ptr.hpp>
#include <vector>

#include "Graphics/Camera.h"

namespace Renderer
{
    class FrameBuffer;
    class MultiViewCompositor;
    
    class Viewport
    {
    public:
        Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        ~Viewport();
        
        void activate() const;
        
        void setCamera(const boost::shared_ptr<Graphics::Camera>& camera);
        Graphics::Camera* getCamera() const;
        
        void attachFrameBuffer(const boost::shared_ptr<FrameBuffer>& frameBuffer);
        const FrameBuffer* getFrameBuffer() const;
        
        void setCompositor(const boost::shared_ptr<MultiViewCompositor>& compositor);
        const MultiViewCompositor* getCompositor() const;
        
    private:
        const unsigned int x;
        const unsigned int y;
        const unsigned int width;
        const unsigned int height;
        
        boost::shared_ptr<Graphics::Camera> camera;
        boost::shared_ptr<FrameBuffer> frameBuffer;
        boost::shared_ptr<MultiViewCompositor> compositor;
    };
}


#endif	/* RENDERER_VIEWPORT_H */

