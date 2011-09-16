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

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"


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
        
        CreateFn create = reinterpret_cast<CreateFn>(lib->getFunction("createRenderer"));
        renderer = create(memoryManager, 0);
        
    }
    
    const char* SystemScene::getSceneFileExtension() const
    {
        return SCENE_FILE_EXTENSION.c_str();
    }
    
    void SystemScene::load(const Utilities::IO::File& file)
    {
        double* rawData = new double[9];
        rawData[0] = 0.0;
        rawData[1] = 0.0;
        rawData[2] = 0.0;
        
        rawData[3] = 0.0;
        rawData[4] = 1.0;
        rawData[5] = 0.0;
        
        rawData[6] = 1.0;
        rawData[7] = 0.0;
        rawData[8] = 0.0;
        
        boost::shared_array<char> data(reinterpret_cast<char*>(rawData));
        
        unsigned long vbID = renderer->requestVertexBuffer(data, 3, VertexFormat());
//        unsigned int vbID = renderer->requestVertexBuffer(data);
//        unsigned int ibID = renderer->requestIndexBuffer(data);
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) RenderTask(renderer.get(), platformManager->getWindow()->getGraphicsContext());
    }
}
