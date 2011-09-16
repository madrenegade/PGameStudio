/* 
 * File:   OpenGLRenderer.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:22 PM
 */

#ifndef RENDERER_OPENGLRENDERER_H
#define	RENDERER_OPENGLRENDERER_H

#include "Graphics/Renderer.h"
#include <tbb/atomic.h>

namespace Renderer
{

    class OpenGLRenderer : public Graphics::Renderer
    {
    public:
        OpenGLRenderer();
        virtual ~OpenGLRenderer();

        virtual unsigned long requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                                                  unsigned int numVertices, const Graphics::VertexFormat& fmt);
        
        virtual void beginScene();
        
    private:
        tbb::atomic<unsigned long> vbID;
    };
}

#endif	/* RENDERER_OPENGLRENDERER_H */

