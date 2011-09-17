/* 
 * File:   VertexBufferManager.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 8:40 AM
 */

#ifndef RENDERER_VERTEXBUFFERMANAGER_H
#define	RENDERER_VERTEXBUFFERMANAGER_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Renderer
{
    class VertexBuffer;
    class VertexBufferRequest;
    
    class VertexBufferManager
    {
    public:
        VertexBufferManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                            Utilities::Memory::pool_id pool);
        
        ~VertexBufferManager();

        void createFrom(const VertexBufferRequest& request);
        
        bool isLoaded(unsigned long id) const;
        
        VertexBuffer* get(unsigned long id) const;

    private:
        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        Utilities::Memory::pool_id pool;
        
        typedef std::map<unsigned long, boost::shared_ptr<VertexBuffer >> VertexBufferMap;
        VertexBufferMap vertexBuffers;
    };
}

#endif	/* RENDERER_VERTEXBUFFERMANAGER_H */

