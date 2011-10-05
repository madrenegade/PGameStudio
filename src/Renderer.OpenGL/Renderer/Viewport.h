/*
 * File:   Viewport.h
 * Author: madrenegade
 *
 * Created on September 25, 2011, 8:52 PM
 */

#ifndef RENDERER_VIEWPORT_H
#define RENDERER_VIEWPORT_H


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

        void setCamera(const std::shared_ptr<Graphics::Camera>& camera);
        Graphics::Camera* getCamera() const;

        void attachFrameBuffer(const std::shared_ptr<FrameBuffer>& frameBuffer);
        const FrameBuffer* getFrameBuffer() const;

        void setCompositor(const std::shared_ptr<MultiViewCompositor>& compositor);
        const MultiViewCompositor* getCompositor() const;

    private:
        const unsigned int x;
        const unsigned int y;
        const unsigned int width;
        const unsigned int height;

        std::shared_ptr<Graphics::Camera> camera;
        std::shared_ptr<FrameBuffer> frameBuffer;
        std::shared_ptr<MultiViewCompositor> compositor;
    };
}


#endif	/* RENDERER_VIEWPORT_H */

