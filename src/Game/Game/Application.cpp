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

#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/helpers.h"

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
        const double frametime = std::chrono::duration_cast<sec> (end - start).count();

        properties->set("Frametime", frametime);
        scriptManager->setVariable("FRAMETIME", frametime);

        VLOG_EVERY_N(3, 1000) << "Framerate: " << (1.0 / frametime);

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

        scriptManager = Scripting::ScriptManagerFactory::create(memoryManager, fileSystem, properties);
        properties->set("SCRIPT_MANAGER", scriptManager.get());

        Core::Events::EventID setVar = eventManager->registerEvent("SET_SCRIPT_VAR");
        eventManager->registerEventHandler(setVar, boost::bind(&Scripting::ScriptManager::onSetVariable, scriptManager.get(), _1, _2));

        registerFunctionsForScripting();
    }

    void Application::registerFunctionsForScripting()
    {
        Scripting::State state = scriptManager->getState();

        module(state)
        [
            class_<Scripting::ScriptManager>("ScriptManager")
                .def("load", &Scripting::ScriptManager::load)
                .def("run", &Scripting::ScriptManager::runScript)
        ];

        scriptManager->setVariable("Script", scriptManager.get());

        module(state)
        [
            class_<EventManager>("EventManager")
                .def("register", &EventManager::registerEvent)
                .def("getID", &EventManager::getEventID)
                .def("push", &EventManager::pushEvent<int>)
                .def("push", &EventManager::pushEvent<Math::Vector3>)
        ];

        scriptManager->setVariable("Event", eventManager.get());

        module(state)
        [
            class_<Core::SceneManager>("SceneManager")
                .def("load", &Core::SceneManager::loadScene)
                .def("switchTo", &Core::SceneManager::switchScene)
        ];

        scriptManager->setVariable("Scene", sceneManager.get());

        module(state)
        [
            class_<Math::Vector3>("Vector3")
                .def(constructor<double, double, double>())
                .def_readwrite("x", &Math::Vector3::X)
                .def_readwrite("y", &Math::Vector3::Y)
                .def_readwrite("z", &Math::Vector3::Z)
                .def(self * double())
                .def(self / double())
                .def(self + self)
                .def(self - self)
                .def(tostring(self))
                .def("cross", &Math::Vector3::Cross)
                .def("normalize", &Math::Vector3::Normalize)
        ];

        module(state, "Math")
        [
            def("degreesToRadians", &Math::DegreesToRadians)
        ];

        module(state)
        [
            class_<Math::Quaternion>("Quaternion")
                .def(constructor<const Math::Vector3&, double>())
                .def(constructor<const Math::Quaternion&>())
                .def(tostring(self))
                .def("conjugate", &Math::Quaternion::Conjugate)
                .def(self * self)
                .def("getAxis", &Math::Quaternion::GetAxis)
                .scope
                [
                  def("fromAxisAngle", &Math::Quaternion::FromAxisAngle)
                ]
        ];
    }
}
