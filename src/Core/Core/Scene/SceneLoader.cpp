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
#include "Utilities/IO/FileSystem.h"
#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/IO/XmlReader.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include <glog/logging.h>

using namespace Utilities::Memory;
using namespace Utilities::IO;
using namespace Utilities::Properties;

namespace Core
{

    SceneLoader::SceneLoader()
    {

    }

    SceneLoader::SceneLoader(const boost::shared_ptr<FileSystem>& fileSystem,
                             const boost::shared_ptr<MemoryManager>& memoryManager,
                             const boost::shared_ptr<Platform::PlatformManager>& platform,
                             const boost::shared_ptr<Events::EventManager>& eventManager,
                             const boost::shared_ptr<PropertyManager>& properties)
        : fileSystem(fileSystem), memoryManager(memoryManager), platform(platform), eventManager(eventManager),
          properties(properties)
    {
    }

    SceneLoader::~SceneLoader()
    {
    }

    const boost::shared_ptr<Scene> SceneLoader::loadScene(const char* const filename) const
    {
        LOG(INFO) << "Loading scene " << filename;

        boost::shared_ptr<XmlReader> reader = fileSystem->readXml(filename);
        const XmlReader::Document* doc = reader->getDocument();

        SystemVector neededSystems;
        XmlReader::Node* systemNode = doc->first_node("scene")->first_node("systems")->first_node("system");

        for(XmlReader::Node* node = systemNode; node; node = node->next_sibling("system"))
        {
            neededSystems.push_back(node->first_attribute("name")->value());
        }

        const boost::shared_ptr<Scene> scene = memoryManager->construct(Scene());

        loadSystemLibraries(neededSystems, scene.get());

        return scene;
    }

    void SceneLoader::loadSystemScene(SystemScene* const systemScene, const char* const filename) const
    {
        LOG(INFO) << "Loading system scene " << filename;

        auto f = fileSystem->read(filename);
        systemScene->load(f);
    }

    typedef boost::shared_ptr<SystemScene> (*CreateFn)(const MemoryManager::Ptr&);

    void SceneLoader::loadSystemLibraries(const SystemVector& systems, Scene* const scene) const
    {
        for (auto i = systems.begin(); i != systems.end(); ++i)
        {
            const boost::shared_ptr<Platform::Library> lib = platform->libraries()->load(i->c_str());

            // NOTE: pointer-to-function and pointer-to-object conversion gives unfixable warning
            CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createSystemScene"));

            const auto systemScene = create(memoryManager);

            String iniFile(i->c_str(), i->size());
            iniFile.append(".ini");

            systemScene->addOptionsTo(properties);
            properties->parse(iniFile.c_str());

            systemScene->setMemoryManager(memoryManager);
            systemScene->setPlatformManager(platform);
            systemScene->setEventManager(eventManager);
            systemScene->setFileSystem(fileSystem);
            systemScene->setProperties(properties);

            const boost::shared_ptr<Pool> pool = Pool::create(i->c_str(), MemoryPoolSettings::loadFrom(properties.get(), i->c_str()));
            const pool_id systemPool = memoryManager->registerMemoryPool(pool);

            systemScene->setMemoryPool(systemPool);

            systemScene->initialize();

            scene->addSystemScene(systemScene);
        }
    }
}
