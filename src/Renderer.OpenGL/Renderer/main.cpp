#include "Renderer/OpenGLRenderer.h"
#include "Renderer/Manager.h"

#include "Renderer/VertexBufferRequest.h"
#include "Renderer/VertexBufferInitializer.h"
#include "Renderer/IndexBufferRequest.h"
#include "Renderer/IndexBufferInitializer.h"
#include "Renderer/EffectRequest.h"
#include "Renderer/EffectInitializer.h"

#include "Utilities/Memory/MemoryManager.h"

using namespace Utilities::Memory;
using namespace Renderer;

extern "C"
{
    boost::shared_ptr<Graphics::Renderer> createRenderer(const MemoryManager::Ptr& memory, pool_id pool)
    {
        auto vbManager = memory->construct(Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer>(memory, pool));
        auto ibManager = memory->construct(Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer>(memory, pool));
        auto effectManager = memory->construct(Manager<Effect, EffectRequest, EffectInitializer>(memory, pool));
        
        boost::shared_ptr<Graphics::Renderer> renderer = memory->construct(OpenGLRenderer(vbManager, ibManager, effectManager), pool);
        
        return renderer;
    }
}