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

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/File.h"
#include "Graphics/GraphicsContext.h"

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
        double* rawData = new double[9];
        rawData[0] = 0.0;
        rawData[1] = -1.0;
        rawData[2] = -1.0;

        rawData[3] = 0.0;
        rawData[4] = 1.0;
        rawData[5] = -5.0;

        rawData[6] = 1.0;
        rawData[7] = 0.0;
        rawData[8] = -2.0;

        boost::shared_array<char> data(reinterpret_cast<char*> (rawData));

        unsigned long vbID = renderer->requestVertexBuffer(data, 3, VertexFormat());
        
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
