/*
 * File:   VertexBufferInitializer.cpp
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:25 PM
 */

#include "Renderer/VertexBufferInitializer.h"
#include "Renderer/VertexBufferRequest.h"
#include "Renderer/VertexBuffer.h"

namespace Renderer
{
    void VertexBufferInitializer::initialize(const std::shared_ptr<VertexBuffer>& vb, const VertexBufferRequest& request)
    {
        vb->setData(request.data.get(), request.numVertices, request.format);
    }
}


