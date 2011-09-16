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
                    const boost::shared_ptr<Events::EventManager>& eventManager);
        ~SceneLoader();
        
        /**
         * Load the scene with the given name
         * @param name
         */
        boost::shared_ptr<Scene> loadScene(const char* filename);
        
        void loadSystemScene(SystemScene* systemScene, const char* filename);
        
    private:
        SceneLoader();
        
        typedef std::vector<String, Utilities::Memory::STLAllocator<String>> SystemVector;
        
        void loadSystemLibraries(const SystemVector& systems, Scene* scene);
        
        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        boost::shared_ptr<Platform::PlatformManager> platform;
        boost::shared_ptr<Events::EventManager> eventManager;
    };
}

#endif	/* CORE_SCENELOADER_H */

