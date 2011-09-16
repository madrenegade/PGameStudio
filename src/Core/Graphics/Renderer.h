/* 
 * File:   Renderer.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:09 PM
 */

#ifndef GRAPHICS_RENDERER_H
#define	GRAPHICS_RENDERER_H

#include "Utilities/Memory/typedefs.h"
#include <boost/shared_array.hpp>

namespace Graphics
{
    class VertexFormat;
    
    class Renderer
    {
    public:
        virtual ~Renderer();
        
        virtual unsigned long requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data, unsigned int numVertices, const VertexFormat& fmt) = 0;
        
        virtual void beginScene() = 0;
        
    protected:
        Renderer();
    };
}

#endif	/* GRAPHICS_RENDERER_H */

