/* 
 * File:   IndexBuffer.cpp
 * Author: madrenegade
 * 
 * Created on September 18, 2011, 1:35 PM
 */

#include "Renderer/IndexBuffer.h"

#include <GL/glew.h>

namespace Renderer
{

    IndexBuffer::IndexBuffer()
    {
        glGenBuffers(1, &id);
    }

    IndexBuffer::~IndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::setData(const boost::shared_array<unsigned int>& data, unsigned int numIndexes)
    {
        this->numIndexes = numIndexes;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndexes * sizeof (unsigned int), data.get(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    unsigned int IndexBuffer::getID() const
    {
        return id;
    }
    
    unsigned int IndexBuffer::getNumIndexes() const
    {
        return numIndexes;
    }
}
