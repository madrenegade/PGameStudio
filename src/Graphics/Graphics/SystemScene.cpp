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

#include "Graphics/GraphicsContext.h"
#include "Graphics/Vertex.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/File.h"
#include "Utilities/string.h"

#include "Math/Vector2.h"
#include "SceneLoader.h"

#include <sstream>

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
        Utilities::IO::File effectFile(fileSystem->read("fx/default.cgfx"));
        Utilities::IO::File finalEffectFile(fileSystem->read("fx/final.cgfx"));
        renderer->requestEffect(effectFile);
        renderer->requestEffect(finalEffectFile);

        SceneLoader loader(fileSystem, memoryManager, 0, renderer.get());
        scene = loader.loadFrom(file);
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) RenderTask(
            renderer.get(),
            platformManager->getWindow()->getGraphicsContext(),
            scene.get());
    }
}
