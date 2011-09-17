#include "Renderer/OpenGLRenderer.h"
#include "Renderer/VertexBufferManager.h"
#include "Renderer/EffectManager.h"

#include "Utilities/Memory/MemoryManager.h"

using namespace Utilities::Memory;

extern "C"
{
    boost::shared_ptr<Graphics::Renderer> createRenderer(const MemoryManager::Ptr& memory, pool_id pool)
    {
        boost::shared_ptr<Renderer::VertexBufferManager> vbManager = memory->construct(Renderer::VertexBufferManager(memory, pool));
        boost::shared_ptr<Renderer::EffectManager> effectManager = memory->construct(Renderer::EffectManager(memory, pool));
        
        boost::shared_ptr<Graphics::Renderer> renderer = memory->construct(Renderer::OpenGLRenderer(vbManager, effectManager), pool);
        
        return renderer;
    }
}