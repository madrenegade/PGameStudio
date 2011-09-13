/* 
 * File:   Application.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 8:07 AM
 */

#ifndef GAME_APPLICATION_H
#define	GAME_APPLICATION_H

#include "Core/Application.h"
#include <boost/shared_ptr.hpp>

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
    
    namespace IO
    {
        class FileSystem;
    }
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
}

namespace Platform
{
    class PlatformManager;
}

namespace Game
{

    class Application : public Core::Application
    {
    public:
        Application(int argc, char** argv);
        virtual ~Application();
        
    protected:
        virtual void onInitialize();
        virtual void onInitialized();
        
        virtual void onRun();
        virtual bool onUpdate();
        virtual void onShutdown();
        
    private:
        boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<Core::Events::EventManager> eventManager;
        boost::shared_ptr<Platform::PlatformManager> platformManager;
        
        void initializeOptions();
        void initializeDefaultMemoryPool();
        void initializeFileSystem();
        void initializeEventManager();
        void initializePlatformManager();
    };
}


#endif	/* GAME_APPLICATION_H */

