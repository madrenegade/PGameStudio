/* 
 * File:   SceneManager.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 1:40 PM
 */

#ifndef CORE_SCENEMANAGER_H
#define	CORE_SCENEMANAGER_H

#include <boost/shared_ptr.hpp>
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
        SceneManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                     const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                     const boost::shared_ptr<Platform::PlatformManager>& platform,
                     const boost::shared_ptr<Events::EventManager>& eventManager,
                     const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~SceneManager();

        void loadScene(const char* name);
        void switchScene(const char* name);
        
        Scene* getCurrentScene() const;

    private:
        static const std::string SCENE_PATH;
        
        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<Platform::PlatformManager> platform;
        boost::shared_ptr<Events::EventManager> eventManager;
        boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
        
        typedef boost::shared_ptr<Scene> ScenePtr;
        
        typedef std::map<String, ScenePtr> SceneMap;
        SceneMap loadedScenes;
        
        ScenePtr currentScene;
    };
}

#endif	/* CORE_SCENEMANAGER_H */

