/* 
 * File:   SceneLoader.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 1:23 PM
 */

#ifndef CORE_SCENELOADER_H
#define	CORE_SCENELOADER_H

#include <boost/shared_ptr.hpp>
#include "Utilities/string.h"

namespace Utilities
{
    namespace IO
    {
        class FileSystem;
    }
    
    namespace Memory
    {
        class MemoryManager;
    }
    
    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Platform
{
    class PlatformManager;
}

namespace Core
{
    class Scene;
    class SystemScene;
    
    namespace Events
    {
        class EventManager;
    }
    
    class TaskScheduler;
    
    class SceneLoader
    {
    public:
        SceneLoader(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                    const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                    const boost::shared_ptr<Platform::PlatformManager>& platform,
                    const boost::shared_ptr<Events::EventManager>& eventManager,
                    const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~SceneLoader();
        
        /**
         * Load the scene with the given name
         * @param name
         */
        const boost::shared_ptr<Scene> loadScene(const char* const filename) const;
        
        void loadSystemScene(SystemScene* const systemScene, const char* const filename) const;
        
    private:
        SceneLoader();
        
        typedef std::vector<String, Utilities::Memory::STLAllocator<String>> SystemVector;
        
        void loadSystemLibraries(const SystemVector& systems, Scene* const scene) const;
        
        const boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        const boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        const boost::shared_ptr<Platform::PlatformManager> platform;
        const boost::shared_ptr<Events::EventManager> eventManager;
        const boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
    };
}

#endif	/* CORE_SCENELOADER_H */

