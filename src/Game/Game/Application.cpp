#include "Game/Application.h"

// TODO: Release memory tracker
//#ifdef DEBUG
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
//#endif

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/FileSystemFactory.h"

#include "Core/Events/EventManager.h"
#include "Core/TaskScheduler.h"
#include "Core/Scene/SceneManager.h"

#include "Platform/PlatformManager.h"

#include "Graphics/Window.h"
#include "Graphics/GraphicsContext.h"

#include "Scripting/ScriptManagerFactory.h"
#include "Scripting/ScriptManager.h"

#include <glog/logging.h>
#include <tbb/task.h>
#include <chrono>

using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Utilities::IO;
using namespace Core::Events;
using namespace Platform;

namespace Game
{

    Application::Application(int argc, char** argv)
    : properties(new PropertyManager), running(true)
    {
        properties->parse(argc, argv);

        // FIXME: prevents logging (seems to ignore env vars and command line options)
        //google::InitGoogleLogging(argv[0]);

        MemoryTracker::Ptr memoryTracker(new DebugMemoryTracker());
        memoryManager = MemoryManager::create(memoryTracker);

        BEGIN_NEW_FRAME(memoryManager);
    }

    Application::~Application()
    {

    }

    void Application::onQuit(const EventID&, const boost::any&)
    {
        running = false;
    }

    void Application::onInitialize()
    {
        LOG(INFO) << "Initializing game...";

        initializeOptions();

        initializeDefaultMemoryPool();
        initializeFileSystem();
        initializeEventManager();
        initializePlatformManager();
        initializeWindow();
        initializeTaskScheduler();
        initializeSceneManager();
        initializeScriptManager();
    }

    void Application::onInitialized()
    {
        LOG(INFO) << "Memory usage: " << memoryManager->getMemoryUsage();
        LOG(INFO) << "Loading startup script";

        scriptManager->runStartupScript();

        LOG(INFO) << "Game initialized";
    }

    void Application::onRun()
    {
        LOG(INFO) << "Starting game...";
    }

    typedef std::chrono::duration<double, std::ratio < 1, 1 >> sec;

    bool Application::onUpdate()
    {
        auto start = std::chrono::system_clock::now();

        BEGIN_NEW_FRAME(memoryManager);
        
        platformManager->handleOSEvents();
        eventManager->handleEvents();

        auto scene = sceneManager->getCurrentScene();
        
        if(scene != 0)
        {
            taskScheduler->executeTasks(scene);
        }

        auto end = std::chrono::system_clock::now();

        // maybe use EventManager for this
        const double framerate = std::chrono::duration_cast<sec> (end - start).count();
        
        properties->set("Frametime", framerate);
        
        VLOG_EVERY_N(3, 1000) << "Framerate: " << (1.0 / framerate);
        
        VLOG_EVERY_N(3, 1000) << "Memory usage: " << memoryManager->getMemoryUsage();

        return running;
    }

    void Application::onShutdown()
    {
        BEGIN_NEW_FRAME(memoryManager);

        LOG(INFO) << "Shutting down...";
    }

    void Application::initializeOptions()
    {
        VLOG(1) << "Initializing program settings";

        MemoryPoolSettings defaultSettings(1 * KByte, 1 * KByte, 128 * Byte,
                                           1 * KByte, 1 * KByte, 256 * Byte,
                                           1 * KByte, 1 * KByte, 512 * Byte);
        defaultSettings.addOptionsTo(properties, "Default");

        PlatformManager::addOptionsTo(properties);
        FileSystem::addOptionsTo(properties);
        Graphics::Window::addOptionsTo(properties);
        Core::TaskScheduler::addOptionsTo(properties);
        Scripting::ScriptManager::addOptionsTo(properties);

        properties->parse("settings.ini");
    }

    void Application::initializeDefaultMemoryPool()
    {
        VLOG(1) << "Initializing default memory pool";

        boost::shared_ptr<Pool> pool = Pool::create(MemoryPoolSettings::loadFrom(properties, "Default"));
        memoryManager->registerMemoryPool(pool);
    }

    void Application::initializeFileSystem()
    {
        VLOG(1) << "Initializing filesystem";

        fileSystem = FileSystemFactory::create(memoryManager, properties);
        File f(fileSystem->read("settings.ini"));
    }

    void Application::initializeEventManager()
    {
        VLOG(1) << "Initializing event management";

        eventManager = memoryManager->construct(EventManager(memoryManager));

        EventID quitEvent = eventManager->registerEvent("QUIT");
        eventManager->registerEventHandler(quitEvent, boost::bind(&Application::onQuit, this, _1, _2));
        
        eventManager->registerEvent("KEY_PRESSED");
        eventManager->registerEvent("KEY_RELEASED");
        eventManager->registerEvent("MOUSE_BUTTON_PRESSED");
        eventManager->registerEvent("MOUSE_BUTTON_RELEASED");
        eventManager->registerEvent("MOUSE_MOVED");
    }

    void Application::initializePlatformManager()
    {
        VLOG(1) << "Initializing platform manager";

        platformManager = memoryManager->construct(PlatformManager(memoryManager, eventManager, properties));
    }

    void Application::initializeWindow()
    {
        VLOG(1) << "Creating window";

        window = platformManager->createWindow();
    }

    void Application::initializeTaskScheduler()
    {
        VLOG(1) << "Initializing task scheduler";

        // cannot use memory manager because tbb task scheduler is copy protected
        taskScheduler.reset(new Core::TaskScheduler(properties));
    }

    void Application::initializeSceneManager()
    {
        VLOG(1) << "Initializing scene manager";

        sceneManager = memoryManager->construct(Core::SceneManager(memoryManager,
            fileSystem, platformManager, eventManager, properties));
    }

    void Application::initializeScriptManager()
    {
        VLOG(1) << "Initializing script manager";

        scriptManager = Scripting::ScriptManagerFactory::create(memoryManager,
            platformManager, fileSystem, properties);
        properties->set("SCRIPT_MANAGER", scriptManager.get());
        
        Core::Events::EventID runScript = eventManager->registerEvent("RUN_SCRIPT");
        eventManager->registerEventHandler(runScript, boost::bind(&Scripting::ScriptManager::runScript, scriptManager.get(), _1, _2));
        
        Core::Events::EventID setVar = eventManager->registerEvent("SET_SCRIPT_VAR");
        eventManager->registerEventHandler(setVar, boost::bind(&Scripting::ScriptManager::setVariable, scriptManager.get(), _1, _2));
        
        registerFunctionsForScripting();
    }

    void Application::registerFunctionsForScripting()
    {
        boost::function<long (const char*)> registerEvent = boost::bind(&EventManager::registerEvent, eventManager.get(), _1);
        boost::function<long (const char*)> getEventID = boost::bind(&EventManager::getEventID, eventManager.get(), _1);
        boost::function<void (long, const char* data)> pushEvent = boost::bind(&EventManager::pushEvent, eventManager.get(), _1, _2);
        
        scriptManager->registerFunction("registerEvent", registerEvent);
        scriptManager->registerFunction("getEventID", getEventID);
        scriptManager->registerFunction("pushEvent", pushEvent);

        boost::function<void (const char*) > loadScene = boost::bind(&Core::SceneManager::loadScene, sceneManager.get(), _1);
        boost::function<void (const char*) > switchScene = boost::bind(&Core::SceneManager::switchScene, sceneManager.get(), _1);

        scriptManager->registerFunction("loadScene", loadScene);
        scriptManager->registerFunction("switchScene", switchScene);
        
    }
}
