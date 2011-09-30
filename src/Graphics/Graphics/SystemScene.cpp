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
using namespace Utilities::Properties;

namespace Graphics
{
    const std::string SystemScene::SCENE_FILE_EXTENSION("graphics");

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    void SystemScene::addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const
    {
        const MemoryPoolSettings graphicsPool(1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte);
        graphicsPool.addOptionsTo(properties, "Graphics");

        po::options_description options("Graphics options");

        options.add_options()
            ("Graphics.fieldOfView", po::value<double>()->default_value(60.0), "The field of view")
            ("Graphics.zNear", po::value<double>()->default_value(0.1), "The near clipping plane")
            ("Graphics.zFar", po::value<double>()->default_value(100.0), "The far clipping plane");

        properties->addOptions(options);
    }

    typedef boost::shared_ptr<Renderer> (*CreateFn)(const MemoryManager::Ptr&, const PropertyManager::Ptr&, pool_id pool);

    void SystemScene::initialize()
    {
        boost::shared_ptr<Platform::Library> lib = platformManager->libraries()->load("Renderer.OpenGL");

        // NOTE: pointer-to-function and pointer-to-object conversion gives unfixable warning
        CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createRenderer"));

        renderer = create(memoryManager, properties, pool);

        platformManager->getWindow()->getGraphicsContext()->MakeCurrent();
        renderer->initialize();
        platformManager->getWindow()->getGraphicsContext()->Release();

    }

    const char* SystemScene::getSceneFileExtension() const
    {
        return SCENE_FILE_EXTENSION.c_str();
    }

    void SystemScene::load(const Utilities::IO::File::Handle& file)
    {
        Utilities::IO::File::Handle effectFile = fileSystem->read("fx/default.cgfx");
        Utilities::IO::File::Handle finalEffectFile = fileSystem->read("fx/final.cgfx");
        Utilities::IO::File::Handle anaglyphCompositorEffectFile = fileSystem->read("fx/anaglyph_compositor.cgfx");
        Utilities::IO::File::Handle defaultCompositorEffectFile = fileSystem->read("fx/default_compositor.cgfx");
        renderer->requestEffect(effectFile);
        renderer->requestEffect(finalEffectFile);
        renderer->requestEffect(anaglyphCompositorEffectFile);
        renderer->requestEffect(defaultCompositorEffectFile);

        SceneLoader loader(fileSystem, memoryManager, pool, renderer.get());
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
