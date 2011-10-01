/*
 * File:   Viewport.cpp
 * Author: madrenegade
 *
 * Created on September 25, 2011, 8:52 PM
 */

#include "Renderer/Viewport.h"
#include "Renderer/FrameBuffer.h"
#include "MultiViewCompositor.h"

#include <GL/gl.h>

namespace Renderer
{

    Viewport::Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
        : x(x), y(y), width(width), height(height)
    {
    }

    Viewport::~Viewport()
    {
    }

    void Viewport::activate() const
    {
        glViewport(x, y, width, height);
    }

    void Viewport::setCamera(const boost::shared_ptr<Graphics::Camera>& camera)
    {
        this->camera = camera;
    }

    Graphics::Camera* Viewport::getCamera() const
    {
        return camera.get();
    }

    void Viewport::attachFrameBuffer(const boost::shared_ptr<FrameBuffer>& frameBuffer)
    {
        this->frameBuffer = frameBuffer;
    }

    const FrameBuffer* Viewport::getFrameBuffer() const
    {
        return frameBuffer.get();
    }

    void Viewport::setCompositor(const boost::shared_ptr<MultiViewCompositor>& compositor)
    {
        this->compositor = compositor;
    }

    const MultiViewCompositor* Viewport::getCompositor() const
    {
        return compositor.get();
    }
}
