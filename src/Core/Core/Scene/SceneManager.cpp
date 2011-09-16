/* 
 * File:   SceneManager.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 1:40 PM
 */

#include "Core/Scene/SceneManager.h"
#include "Core/Scene/SceneLoader.h"
#include "SystemScene.h"
#include "Scene.h"

namespace Core
{
    const std::string SceneManager::SCENE_PATH("scenes");

    SceneManager::SceneManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                               const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                               const boost::shared_ptr<Platform::PlatformManager>& platform,
                               const boost::shared_ptr<Events::EventManager>& eventManager,
                               const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
    : memoryManager(memoryManager), fileSystem(fileSystem),
    platform(platform), eventManager(eventManager), properties(properties)
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::loadScene(const char* name)
    {
        std::string sceneFile(SCENE_PATH + "/" + name + ".scene");

        SceneLoader loader(fileSystem, memoryManager, platform, eventManager);

        ScenePtr scene = loader.loadScene(sceneFile.c_str());
        
        auto& systemScenes = scene->getSystemScenes();
        
        std::for_each(systemScenes.begin(), systemScenes.end(), [name, &loader](const boost::shared_ptr<SystemScene>& systemScene) {
            std::string systemSceneFile(SCENE_PATH + "/" + name + "." + systemScene->getSceneFileExtension());
            loader.loadSystemScene(systemScene.get(), systemSceneFile.c_str());
        });
        
        loadedScenes[name] = scene;
    }

    void SceneManager::switchScene(const char* name)
    {
        LOG(INFO) << "Switching to scene " << name;
        currentScene = loadedScenes.at(name);
    }
    
    Scene* SceneManager::getCurrentScene() const
    {
        return currentScene.get();
    }
}
