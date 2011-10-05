/*
 * File:   PlatformManager.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#ifndef PLATFORM_PLATFORMMANAGER_H
#define	PLATFORM_PLATFORMMANAGER_H


#include "Platform/LibraryManager.h"

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }

    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
}

namespace Graphics
{
    class Window;
}

namespace Platform
{

    class PlatformImpl;

    class PlatformManager
    {
    public:
        static void addOptionsTo(const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);

        PlatformManager(const std::shared_ptr<Utilities::Memory::MemoryManager>& memory,
                        const std::shared_ptr<Core::Events::EventManager>& eventManager,
                        const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~PlatformManager();

        /**
         * Handle all operating system events.
         */
        void handleOSEvents();

        /**
         * Get the id of the key with the specified name.
         * @param name - the name of the key
         * @return the key id
         */
        unsigned int getKeysym(const char* const name) const;

        /**
         * Creates a window, an renderer and a corresponding graphics context.
         * @return the created window
         */
        std::shared_ptr<Graphics::Window> createWindow();
        Graphics::Window* getWindow() const;

        /**
         * Get the manager object for dynamic libraries.
         * @return the manager object
         */
        LibraryManager* libraries() const;

    private:
        std::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        std::shared_ptr<Core::Events::EventManager> eventManager;
        std::shared_ptr<Utilities::Properties::PropertyManager> properties;
        std::shared_ptr<LibraryManager> libraryManager;
        std::shared_ptr<Library> platformLibrary;

        std::shared_ptr<PlatformImpl> impl;

        Graphics::Window* window;
    };
}

#endif	/* PLATFORM_PLATFORMMANAGER_H */

