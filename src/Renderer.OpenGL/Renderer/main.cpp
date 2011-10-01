#include "Renderer/OpenGLRenderer.h"
#include "Renderer/Manager.h"

#include "Renderer/VertexBufferRequest.h"
#include "Renderer/VertexBufferInitializer.h"
#include "Renderer/IndexBufferRequest.h"
#include "Renderer/IndexBufferInitializer.h"
#include "Renderer/EffectRequest.h"
#include "Renderer/EffectInitializer.h"
#include "Renderer/TextureRequest.h"
#include "Renderer/TextureInitializer.h"

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Properties/PropertyManager.h"

using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Renderer;

extern "C"
{
    boost::shared_ptr<Graphics::Renderer> createRenderer(const MemoryManager::Ptr& memory,
            const PropertyManager::Ptr& properties,
            pool_id pool)
    {
        auto vbManager = memory->construct(Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer>(memory, pool));
        auto ibManager = memory->construct(Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer>(memory, pool));
        auto effectManager = memory->construct(Manager<Effect, EffectRequest, EffectInitializer>(memory, pool));
        auto textureManager = memory->construct(Manager<Texture, TextureRequest, TextureInitializer>(memory, pool));

        boost::shared_ptr<Graphics::Renderer> renderer = memory->construct(OpenGLRenderer(memory, pool, properties, vbManager, ibManager, effectManager, textureManager), pool);

        return renderer;
    }
}
