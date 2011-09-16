/* 
 * File:   SceneLoader.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 1:23 PM
 */

#include "Core/Scene/SceneLoader.h"
#include "Core/Scene/Scene.h"
#include "Core/Scene/SystemScene.h"

#include "Utilities/Memory/STLAllocator.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"
#include "Utilities/IO/FileSystem.h"

#include <glog/logging.h>

using namespace Utilities::Memory;
using namespace Utilities::IO;

namespace Core
{

    SceneLoader::SceneLoader()
    {

    }

    SceneLoader::SceneLoader(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                             const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                             const boost::shared_ptr<Platform::PlatformManager>& platform,
                             const boost::shared_ptr<Events::EventManager>& eventManager)
    : fileSystem(fileSystem), memoryManager(memoryManager), platform(platform), eventManager(eventManager)
    {
    }

    SceneLoader::~SceneLoader()
    {
    }

    boost::shared_ptr<Scene> SceneLoader::loadScene(const char* filename)
    {
        LOG(INFO) << "Loading scene " << filename;

        SystemVector neededSystems;
        neededSystems.push_back("Graphics");

        boost::shared_ptr<Scene> scene = memoryManager->construct(Scene());

        loadSystemLibraries(neededSystems, scene.get());

        return scene;
    }

    void SceneLoader::loadSystemScene(SystemScene* systemScene, const char* filename)
    {
        LOG(INFO) << "Loading system scene " << filename;

        File f = fileSystem->read(filename);
        systemScene->load(f);
    }

    typedef boost::shared_ptr<SystemScene> (*CreateFn)(const MemoryManager::Ptr&, pool_id pool);

    void SceneLoader::loadSystemLibraries(const SystemVector& systems, Scene* scene)
    {
        for (auto i = systems.begin(); i != systems.end(); ++i)
        {
            boost::shared_ptr<Platform::Library> lib = platform->libraries()->load(i->c_str());

            CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createSystemScene"));

            // TODO: seperate pools for each system
            auto systemScene = create(memoryManager, 0);
            systemScene->setMemoryManager(memoryManager);
            systemScene->setPlatformManager(platform);
            systemScene->setEventManager(eventManager);
            
            systemScene->initialize();

            scene->addSystemScene(systemScene);
        }
    }
}
