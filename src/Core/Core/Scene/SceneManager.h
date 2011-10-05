/*
 * File:   SceneManager.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 1:40 PM
 */

#ifndef CORE_SCENEMANAGER_H
#define	CORE_SCENEMANAGER_H

#include <map>

#include "Utilities/string.h"

namespace Utilities
{
    namespace IO
    {
        class FileSystem;
    }

    namespace Properties
    {
        class PropertyManager;
    }

    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Platform
{
    class PlatformManager;
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }

    class Scene;

    class SceneManager
    {
    public:
        SceneManager(const std::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                     const std::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                     const std::shared_ptr<Platform::PlatformManager>& platform,
                     const std::shared_ptr<Events::EventManager>& eventManager,
                     const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~SceneManager();

        void loadScene(const char* const name);
        void switchScene(const char* const name);

        Scene* getCurrentScene() const;

    private:
        static const std::string SCENE_PATH;

        const std::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        const std::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        const std::shared_ptr<Platform::PlatformManager> platform;
        const std::shared_ptr<Events::EventManager> eventManager;
        const std::shared_ptr<Utilities::Properties::PropertyManager> properties;

        typedef std::shared_ptr<Scene> ScenePtr;
        typedef std::pair<const String, ScenePtr> SceneMapEntry;
        typedef Utilities::Memory::STLAllocator<SceneMapEntry> SceneMapAllocator;
        typedef std::map<String, ScenePtr, std::less<String>, SceneMapAllocator> SceneMap;
        SceneMap loadedScenes;

        ScenePtr currentScene;
    };
}

#endif	/* CORE_SCENEMANAGER_H */

