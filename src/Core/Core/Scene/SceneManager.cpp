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

    SceneManager::SceneManager(Utilities::Memory::MemoryManager* const memoryManager,
                               Utilities::IO::FileSystem* const fileSystem,
                               Platform::PlatformManager* const platform,
                               Events::EventManager* const eventManager,
                               Utilities::Properties::PropertyManager* const properties)
        : memoryManager(memoryManager), fileSystem(fileSystem),
          platform(platform), eventManager(eventManager), properties(properties)
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::loadScene(const char* const name)
    {
        String sceneFile(SCENE_PATH.c_str(), SCENE_PATH.size());
        sceneFile.append("/");
        sceneFile.append(name);
        sceneFile.append(".scene");

        const SceneLoader loader(fileSystem, memoryManager, platform, eventManager, properties);

        const ScenePtr scene = loader.loadScene(sceneFile.c_str());

        const auto& systemScenes = scene->getSystemScenes();

        std::for_each(systemScenes.begin(), systemScenes.end(), [name, &loader](const std::shared_ptr<SystemScene>& systemScene) {
            String systemSceneFile(SCENE_PATH.c_str(), SCENE_PATH.size());
            systemSceneFile.append("/");
            systemSceneFile.append(name);
            systemSceneFile.append(".");
            systemSceneFile.append(systemScene->getSceneFileExtension());

            loader.loadSystemScene(systemScene.get(), systemSceneFile.c_str());
        });

        loadedScenes[name] = scene;
    }

    void SceneManager::switchScene(const char* const name)
    {
        LOG(INFO) << "Switching to scene " << name;
        currentScene = loadedScenes.at(name);
    }

    Scene* SceneManager::getCurrentScene() const
    {
        return currentScene.get();
    }
}
