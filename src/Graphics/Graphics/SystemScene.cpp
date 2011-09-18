/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 2:35 PM
 */

#include "Graphics/SystemScene.h"
#include "Graphics/RenderTask.h"
#include "Graphics/Renderer.h"
#include "Graphics/VertexFormat.h"
#include "Graphics/Window.h"

#include "Graphics/MeshSceneNode.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Vertex.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/File.h"

#include "Math/Vector2.h"

using namespace Utilities::Memory;

namespace Graphics
{
    const std::string SystemScene::SCENE_FILE_EXTENSION("graphics");

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    typedef boost::shared_ptr<Renderer> (*CreateFn)(const MemoryManager::Ptr&, pool_id pool);

    void SystemScene::initialize()
    {
        boost::shared_ptr<Platform::Library> lib = platformManager->libraries()->load("Renderer.OpenGL");

        CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createRenderer"));
        
        renderer = create(memoryManager, 0);
        
        platformManager->getWindow()->getGraphicsContext()->MakeCurrent();
        renderer->initialize();
        platformManager->getWindow()->getGraphicsContext()->Release();

    }

    const char* SystemScene::getSceneFileExtension() const
    {
        return SCENE_FILE_EXTENSION.c_str();
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {
        boost::shared_array<char> data = memoryManager->allocate<char, 3 * sizeof(TexturedVertexWithNormal)>();
        
        TexturedVertexWithNormal* vertices = reinterpret_cast<TexturedVertexWithNormal*>(data.get());
        vertices[0].position = Math::Vector3(0, -1, -1);
        vertices[0].texcoords = Math::Vector2(0, 0);
        vertices[0].normal = Math::Vector3(0, 1, 0);
        
        vertices[1].position = Math::Vector3(0, 1, -5);
        vertices[1].texcoords = Math::Vector2(0, 1);
        vertices[1].normal = Math::Vector3(0, 1, 0);
        
        vertices[2].position = Math::Vector3(1, 0, -2);
        vertices[2].texcoords = Math::Vector2(1, 0.5);
        vertices[2].normal = Math::Vector3(0, 1, 0);
        
        unsigned long vbID = renderer->requestVertexBuffer(data, 3, VertexFormat::forTexturedVertexWithNormal<TexturedVertexWithNormal>());
        
        Utilities::IO::File effectFile(fileSystem->read("fx/default.cgfx"));
        
        unsigned long effectID = renderer->requestEffect(effectFile);

        scene.reset(new MeshSceneNode(vbID, effectID));
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) RenderTask(
            renderer.get(),
            platformManager->getWindow()->getGraphicsContext(),
            scene.get());
    }
}
