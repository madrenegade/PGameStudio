/*
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 2:28 PM
 */

#ifndef CORE_SYSTEMSCENE_H
#define	CORE_SYSTEMSCENE_H

#include <tbb/task.h>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/IO/File.h"

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }

    namespace IO
    {
        class FileSystem;
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
    namespace Events
    {
        class EventManager;
    }

    class SystemScene
    {
    public:
        virtual ~SystemScene();

        /**
         * Add needed option descriptions to the property manager. This typically contains memory and
         * system specific settings.
         * @param properties - the property manager to add the options to.
         */
        virtual void addOptionsTo(Utilities::Properties::PropertyManager* const properties) const = 0;

        /**
         * Return the extension of the scene file which is handled by this system.
         * @return the extension
         */
        virtual const char* getSceneFileExtension() const = 0;

        /**
         * Initialize the system.
         */
        virtual void initialize() = 0;

        /**
         * Load the system scene from the given file.
         * @param file
         */
        virtual void load(const Utilities::IO::File::Handle& file) = 0;

        /**
         * Set the memory manager which should be used by this system scene.
         * @param memoryManager - the memory manager to use
         */
        void setMemoryManager(Utilities::Memory::MemoryManager* const memoryManager);

        /**
         * Set the memory pool.
         * @param pool - the memory pool to be used by this system.
         */
        void setMemoryPool(const Utilities::Memory::pool_id& pool);

        /**
         * Make the platform manager available to this system scene.
         * @param platformManager
         */
        void setPlatformManager(const Platform::PlatformManager* const platformManager);
        void setEventManager(Events::EventManager* const eventManager);
        void setFileSystem(Utilities::IO::FileSystem* const fileSystem);
        void setProperties(const Utilities::Properties::PropertyManager* const properties);

        /**
         * Allocate a child task of the parent task and return it.
         * @param parent - the parent task
         * @return the allocated child task
         */
        virtual tbb::task* getTask(tbb::task* parent) = 0;

    protected:
        SystemScene();

        Utilities::Memory::MemoryManager* memoryManager;
        Utilities::Memory::pool_id pool;

        const Platform::PlatformManager* platformManager;
        Events::EventManager* eventManager;
        Utilities::IO::FileSystem* fileSystem;
        const Utilities::Properties::PropertyManager* properties;
    };
}

#endif	/* CORE_SYSTEMSCENE_H */

