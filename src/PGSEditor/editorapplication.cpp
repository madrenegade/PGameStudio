#include "editorapplication.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/FileSystemFactory.h"

#include "Core/Events/EventManager.h"
#include "Core/Scene/SceneManager.h"
#include "Core/TaskScheduler.h"
#include "Graphics/Window.h"
#include "Platform/PlatformManager.h"

#include <QApplication>
#include <chrono>

using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Utilities::IO;
using namespace Core::Events;
using namespace Platform;

EditorApplication::EditorApplication(Controller* controller)
    : controller(controller), properties(new PropertyManager())
{
    properties->parse(QApplication::argc(), QApplication::argv());

    MemoryTracker::Ptr memoryTracker(new DebugMemoryTracker());
    memoryManager = MemoryManager::create(memoryTracker);
}

EditorApplication::~EditorApplication()
{

}

void EditorApplication::onInitialize()
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
//    initializeScriptManager();
}

void EditorApplication::onInitialized()
{

}

void EditorApplication::onRun()
{
}

typedef std::chrono::duration<double, std::ratio < 1, 1 >> sec;

bool EditorApplication::onUpdate()
{
    auto start = std::chrono::system_clock::now();

//    BEGIN_NEW_FRAME(memoryManager);

//    platformManager->handleOSEvents();
//    eventManager->handleEvents();

    auto scene = sceneManager->getCurrentScene();

    if(scene != 0)
    {
        taskScheduler->executeTasks(scene);
    }

    auto end = std::chrono::system_clock::now();

    const double frametime = std::chrono::duration_cast<sec> (end - start).count();

    properties->set("Frametime", frametime);

    return true;
}

void EditorApplication::onShutdown()
{

}

void EditorApplication::setGLWidget(QGLWidget* glWidget)
{
    assert(glWidget != 0);
    this->glWidget = glWidget;
    properties->set("GL_WIDGET", glWidget);
}

void EditorApplication::loadScene(const char *const name)
{
    sceneManager->loadScene(name);
    sceneManager->switchScene(name);
}

void EditorApplication::initializeOptions()
{
    VLOG(1) << "Initializing program settings";

    MemoryPoolSettings defaultSettings(8 * KByte, 8 * KByte, 64 * Byte,
                                       8 * KByte, 8 * KByte, 256 * Byte,
                                       8 * KByte, 8 * KByte, 512 * Byte);
    defaultSettings.addOptionsTo(properties, "Default");

    PlatformManager::addOptionsTo(properties);
    FileSystem::addOptionsTo(properties);
    Graphics::Window::addOptionsTo(properties);
    Core::TaskScheduler::addOptionsTo(properties);
//    Scripting::ScriptManager::addOptionsTo(properties);

    properties->parse("settings.ini");
}

void EditorApplication::initializeDefaultMemoryPool()
{
    VLOG(1) << "Initializing default memory pool";

    boost::shared_ptr<Pool> pool = Pool::create("Default", MemoryPoolSettings::loadFrom(properties, "Default"));
    memoryManager->registerMemoryPool(pool);
}

void EditorApplication::initializeFileSystem()
{
    VLOG(1) << "Initializing filesystem";

    fileSystem = FileSystemFactory::create(memoryManager, properties);
}

void  EditorApplication::initializeEventManager()
{
    VLOG(1) << "Initializing event management";

    eventManager = memoryManager->construct(EventManager(memoryManager));

    eventManager->registerEvent("QUIT");

    eventManager->registerEvent("KEY_PRESSED");
    eventManager->registerEvent("KEY_RELEASED");
    eventManager->registerEvent("MOUSE_BUTTON_PRESSED");
    eventManager->registerEvent("MOUSE_BUTTON_RELEASED");
    eventManager->registerEvent("MOUSE_MOVED");
    eventManager->registerEvent("CENTER_MOUSE");
}

void  EditorApplication::initializePlatformManager()
{
    VLOG(1) << "Initializing platform manager";

    platformManager = memoryManager->construct(PlatformManager(memoryManager, eventManager, properties));
}

void EditorApplication::initializeWindow()
{
    VLOG(1) << "Creating window";

    window = platformManager->createWindow();
}

void EditorApplication::initializeTaskScheduler()
{
    VLOG(1) << "Initializing task scheduler";

    taskScheduler.reset(new Core::TaskScheduler(properties));
}

void EditorApplication::initializeSceneManager()
{
    VLOG(1) << "Initializing scene manager";

    sceneManager = memoryManager->construct(Core::SceneManager(memoryManager,
                                                               fileSystem, platformManager, eventManager, properties));
}
