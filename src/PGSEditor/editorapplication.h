#ifndef EDITORAPPLICATION_H
#define EDITORAPPLICATION_H

#include "Core/Application.h"
#include <boost/shared_ptr.hpp>

class Controller;

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }

    namespace Memory
    {
        class MemoryManager;
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

class EditorApplication : public Core::Application
{
public:
    EditorApplication(Controller* controller);
    virtual ~EditorApplication();

    virtual void onRun();
    virtual bool onUpdate();
    virtual void onShutdown();

protected:
    virtual void onInitialize();
    virtual void onInitialized();

private:
    void initializeOptions();
    void initializeDefaultMemoryPool();
    void initializeFileSystem();
    void initializeEventManager();
    void initializePlatformManager();

    Controller* controller;

    boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
    boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
    boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
    boost::shared_ptr<Core::Events::EventManager> eventManager;
    boost::shared_ptr<Platform::PlatformManager> platformManager;
};

#endif // EDITORAPPLICATION_H
