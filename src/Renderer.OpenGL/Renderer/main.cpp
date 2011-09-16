#include "Renderer/OpenGLRenderer.h"
#include "Utilities/Memory/MemoryManager.h"

using namespace Utilities::Memory;

extern "C"
{
    boost::shared_ptr<Graphics::Renderer> createRenderer(const MemoryManager::Ptr& memory, pool_id pool)
    {
        boost::shared_ptr<Graphics::Renderer> renderer = memory->construct(Renderer::OpenGLRenderer(), pool);
        
        return renderer;
    }
}