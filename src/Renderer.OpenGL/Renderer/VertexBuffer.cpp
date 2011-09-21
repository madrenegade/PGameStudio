/* 
 * File:   VertexBuffer.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 8:25 AM
 */

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

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
        glBufferData(GL_ARRAY_BUFFER, format.getVertexSize() * numVertices, data, GL_STATIC_DRAW);

        detectPositionType();
        detectTexCoordType();
        detectNormalType();
    }

    void VertexBuffer::render(IndexBuffer* ib)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, positionType, format.getVertexSize(), (const GLvoid*) format.getPositionOffset());

        if (format.hasTexCoords())
        {
            glClientActiveTexture(GL_TEXTURE0);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, texCoordType, format.getVertexSize(), (const GLvoid*) format.getTexCoordOffset());
        }

        if (format.hasNormal())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(normalType, format.getVertexSize(), (const GLvoid*) format.getNormalOffset());
        }
        
        if(format.hasTangent())
        {
            glClientActiveTexture(GL_TEXTURE1);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(3, normalType, format.getVertexSize(), (GLvoid*) format.getTangentOffset());
        }
        
        if(format.hasBitangent())
        {
            glClientActiveTexture(GL_TEXTURE2);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(3, normalType, format.getVertexSize(), (GLvoid*) format.getBitangentOffset());
        }

        if (ib)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->getID());
            glDrawElements(GL_TRIANGLES, ib->getNumIndexes(), GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, numVertices);
        }
        
        if(format.hasBitangent())
        {
            glClientActiveTexture(GL_TEXTURE2);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        
        if(format.hasTangent())
        {
            glClientActiveTexture(GL_TEXTURE1);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if (format.hasNormal())
        {
            glDisableClientState(GL_NORMAL_ARRAY);
        }

        if (format.hasTexCoords())
        {
            glClientActiveTexture(GL_TEXTURE0);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void VertexBuffer::detectPositionType()
    {
        if (format.getPositionSize() / 3 == sizeof (double))
        {
            positionType = GL_DOUBLE;
        }
        else
        {
            LOG(FATAL) << "Only positions of type double allowed";
        }
    }

    void VertexBuffer::detectTexCoordType()
    {
        if (format.getTexCoordSize() / 2 == sizeof (double))
        {
            texCoordType = GL_DOUBLE;
        }
        else
        {
            LOG(FATAL) << "Only texcoords of type double allowed";
        }
    }

    void VertexBuffer::detectNormalType()
    {
        if (format.getNormalSize() / 3 == sizeof (double))
        {
            normalType = GL_DOUBLE;
        }
        else
        {
            LOG(FATAL) << "Only normal of type double allowed";
        }
    }
}
