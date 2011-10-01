#include "editorapplication.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/FileSystemFactory.h"

#include "Core/Events/EventManager.h"
#include "Platform/PlatformManager.h"

#include <QApplication>

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
//    initializeWindow();
//    initializeTaskScheduler();
//    initializeSceneManager();
//    initializeScriptManager();
}

void EditorApplication::onInitialized()
{

}

void EditorApplication::onRun()
{

}

bool EditorApplication::onUpdate()
{
    return true;
}

void EditorApplication::onShutdown()
{

}

void EditorApplication::initializeOptions()
{
    VLOG(1) << "Initializing program settings";

    MemoryPoolSettings defaultSettings(1 * KByte, 1 * KByte, 64 * Byte,
                                       1 * KByte, 1 * KByte, 256 * Byte,
                                       1 * KByte, 1 * KByte, 512 * Byte);
    defaultSettings.addOptionsTo(properties, "Default");

    PlatformManager::addOptionsTo(properties);
    FileSystem::addOptionsTo(properties);
//    Graphics::Window::addOptionsTo(properties);
//    Core::TaskScheduler::addOptionsTo(properties);
//    Scripting::ScriptManager::addOptionsTo(properties);

    properties->parse("settings.ini");
}

void EditorApplication::initializeDefaultMemoryPool()
{
    VLOG(1) << "Initializing default memory pool";

    boost::shared_ptr<Pool> pool = Pool::create(MemoryPoolSettings::loadFrom(properties, "Default"));
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
}

void  EditorApplication::initializePlatformManager()
{
    VLOG(1) << "Initializing platform manager";

    platformManager = memoryManager->construct(PlatformManager(memoryManager, eventManager, properties));
}
