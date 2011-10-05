/*
 * File:   IndexBufferInitializer.cpp
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:29 PM
 */

#include "Renderer/IndexBufferInitializer.h"
#include "Renderer/IndexBufferRequest.h"
#include "Renderer/IndexBuffer.h"

namespace Renderer
{
    void IndexBufferInitializer::initialize(const std::shared_ptr<IndexBuffer>& ib, const IndexBufferRequest& request)
    {
        ib->setData(request.data, request.numIndexes);
    }
}

