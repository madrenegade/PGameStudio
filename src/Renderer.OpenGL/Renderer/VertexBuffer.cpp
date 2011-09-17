/* 
 * File:   VertexBuffer.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 8:25 AM
 */

#include "Renderer/VertexBuffer.h"

#include <GL/glew.h>
#include <glog/logging.h>

namespace Renderer
{

    VertexBuffer::VertexBuffer()
    {
        glGenBuffers(1, &id);
    }

    VertexBuffer::~VertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &id);
    }
    
    void VertexBuffer::setData(const Utilities::Memory::byte_pointer data, unsigned int numVertices, const Graphics::VertexFormat& fmt)
    {
        this->numVertices = numVertices;
        format = fmt;
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, format.vertexSize() * numVertices, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::render()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, format.vertexSize(), 0);

        glDrawArrays(GL_TRIANGLES, 0, numVertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
