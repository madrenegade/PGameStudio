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
    class Library;
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
        SceneLoader(Utilities::IO::FileSystem* const fileSystem,
                    Utilities::Memory::MemoryManager* const memoryManager,
                    Platform::PlatformManager* const platform,
                    Events::EventManager* const eventManager,
                    Utilities::Properties::PropertyManager* const properties);
        ~SceneLoader();

        /**
         * Load the scene with the given name
         * @param name
         */
        const boost::shared_ptr<Scene> loadScene(const char* const filename) const;

        void loadSystemScene(SystemScene* const systemScene, const char* const filename) const;

    private:
        typedef std::vector<String, Utilities::Memory::STLAllocator<String>> SystemVector;

        void loadSystemLibraries(const SystemVector& systems, Scene* const scene) const;

        Utilities::IO::FileSystem* const fileSystem;
        Utilities::Memory::MemoryManager* const memoryManager;
        Platform::PlatformManager* const platform;
        Events::EventManager* const eventManager;
        Utilities::Properties::PropertyManager* const properties;
    };
}

#endif	/* CORE_SCENELOADER_H */

