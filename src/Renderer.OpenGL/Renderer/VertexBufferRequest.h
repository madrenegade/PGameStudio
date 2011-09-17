/* 
 * File:   VertexBufferRequest.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 8:07 AM
 */

#ifndef RENDERER_VERTEXBUFFERREQUEST_H
#define	RENDERER_VERTEXBUFFERREQUEST_H

#include "Graphics/VertexFormat.h"
#include <boost/shared_array.hpp>
#include "Utilities/Memory/typedefs.h"

namespace Renderer
{
    struct VertexBufferRequest
    {
        unsigned long id;
        boost::shared_array<Utilities::Memory::byte> data;
        unsigned int numVertices;
        Graphics::VertexFormat format;
    };
}

#endif	/* RENDERER_VERTEXBUFFERREQUEST_H */

