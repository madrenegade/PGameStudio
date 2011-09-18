/* 
 * File:   VertexBuffer.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 8:25 AM
 */

#ifndef RENDERER_VERTEXBUFFER_H
#define	RENDERER_VERTEXBUFFER_H

#include "Utilities/Memory/typedefs.h"
#include "Graphics/VertexFormat.h"

#include <GL/glew.h>

namespace Renderer
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();
        
        void setData(const Utilities::Memory::byte_pointer data, unsigned int numVertices, const Graphics::VertexFormat& fmt);
        
        void render();
        
    private:
        void detectPositionType();
        void detectTexCoordType();
        void detectNormalType();
        
        unsigned int id;
        
        unsigned int numVertices;
        Graphics::VertexFormat format;
        
        GLenum positionType;
        GLenum texCoordType;
        GLenum normalType;
    };
}

#endif	/* RENDERER_VERTEXBUFFER_H */

