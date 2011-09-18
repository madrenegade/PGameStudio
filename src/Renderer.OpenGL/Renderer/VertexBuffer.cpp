/* 
 * File:   VertexBuffer.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 8:25 AM
 */

#include "Renderer/VertexBuffer.h"

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

    void VertexBuffer::render()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, positionType, format.getVertexSize(), (const GLvoid*) format.getPositionOffset());

        if (format.hasTexCoords())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, texCoordType, format.getVertexSize(), (const GLvoid*) format.getTexCoordOffset());
        }

        if (format.hasNormal())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(normalType, format.getVertexSize(), (const GLvoid*) format.getNormalOffset());
        }

        //        if(this->m_pIndexBuffer)
        //        {
        //            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexBuffer->GetBufferID());
        //            glDrawElements(this->m_primitiveType, m_pIndexBuffer->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
        //            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //        }
        //        else
        //        {
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        //        }
        
        if (format.hasNormal())
        {
            glDisableClientState(GL_NORMAL_ARRAY);
        }

        if (format.hasTexCoords())
        {
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
