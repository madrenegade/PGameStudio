/* 
 * File:   OpenGLRenderer.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:22 PM
 */

#include "Renderer/OpenGLRenderer.h"

namespace Renderer
{

    OpenGLRenderer::OpenGLRenderer()
    : vbID()
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
    }

    unsigned long OpenGLRenderer::requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                                                      unsigned int numVertices, const Graphics::VertexFormat& fmt)
    {
        unsigned long id = vbID.fetch_and_add(1);
        
        return id;
    }
}
