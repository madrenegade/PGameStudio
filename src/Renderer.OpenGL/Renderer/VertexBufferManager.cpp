/* 
 * File:   VertexBufferManager.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 8:40 AM
 */

#include "Renderer/VertexBufferManager.h"
#include "Renderer/VertexBufferRequest.h"
#include "Renderer/VertexBuffer.h"

#include "Utilities/Memory/MemoryManager.h"

namespace Renderer
{

    VertexBufferManager::VertexBufferManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                            Utilities::Memory::pool_id pool)
    : memory(memoryManager), pool(pool)
    {
    }

    VertexBufferManager::~VertexBufferManager()
    {
    }
    
    void VertexBufferManager::createFrom(const VertexBufferRequest& request)
    {
        boost::shared_ptr<VertexBuffer> vb = memory->construct(VertexBuffer(), pool);
        vb->setData(request.data.get(), request.numVertices, request.format);
        
        vertexBuffers[request.id] = vb;
    }
    
    bool VertexBufferManager::isLoaded(unsigned long id) const
    {
        return vertexBuffers.find(id) != vertexBuffers.end();
    }
    
    VertexBuffer* VertexBufferManager::get(unsigned long id) const
    {
        return vertexBuffers.at(id).get();
    }
}
