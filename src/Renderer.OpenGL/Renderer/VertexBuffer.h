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
        unsigned int id;
        
        unsigned int numVertices;
        Graphics::VertexFormat format;
    };
}

#endif	/* RENDERER_VERTEXBUFFER_H */

