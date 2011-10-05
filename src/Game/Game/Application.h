/*
 * File:   Application.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 8:07 AM
 */

#ifndef GAME_APPLICATION_H
#define	GAME_APPLICATION_H

#include "Core/Application.h"
#include "Core/Events/typedefs.h"


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

    class TaskScheduler;
    class SceneManager;
}

namespace Platform
{
    class PlatformManager;
}

namespace Graphics
{
    class Window;
}

namespace Scripting
{
    class ScriptManager;
}

namespace tbb
{
    class task_list;
}

namespace Game
{
    class StateManager;

    class Application : public Core::Application
    {
    public:
        Application(int argc, char** argv);
        virtual ~Application();

        void onQuit(const Core::Events::EventID& event, const boost::any& data);

    protected:
        virtual void onInitialize();
        virtual void onInitialized();

        virtual void onRun();
        virtual bool onUpdate();
        virtual void onShutdown();

    private:
        std::shared_ptr<Utilities::Properties::PropertyManager> properties;
        std::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        std::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        std::shared_ptr<Core::Events::EventManager> eventManager;
        std::shared_ptr<Platform::PlatformManager> platformManager;
        std::shared_ptr<Graphics::Window> window;
        std::shared_ptr<Core::TaskScheduler> taskScheduler;
        std::shared_ptr<Scripting::ScriptManager> scriptManager;
        std::shared_ptr<Core::SceneManager> sceneManager;
        std::shared_ptr<StateManager> stateManager;

        bool running;

        void initializeOptions();
        void initializeDefaultMemoryPool();
        void initializeFileSystem();
        void initializeEventManager();
        void initializePlatformManager();
        void initializeWindow();
        void initializeTaskScheduler();
        void initializeStateManager();
        void initializeSceneManager();
        void initializeScriptManager();

        void registerFunctionsForScripting();
    };
}


#endif	/* GAME_APPLICATION_H */

