/* 
 * File:   OpenGLRenderer.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:22 PM
 */

#include "Renderer/OpenGLRenderer.h"
#include <GL/gl.h>

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
    
    void OpenGLRenderer::beginScene()
    {
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
        glVertex3d(0, 0, 0);
        glVertex3d(1, 0, 0);
        glVertex3d(0, 1, 0);
        glEnd();
    }
}
