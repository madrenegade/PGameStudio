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

namespace Graphics
{
    class Window;
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }

    class SceneManager;
    class TaskScheduler;
}

namespace Platform
{
    class PlatformManager;
}

class TaskScheduler;
class QGLWidget;

class EditorApplication : public Core::Application
{
public:
    EditorApplication(Controller* controller);
    virtual ~EditorApplication();

    virtual void onRun();
    virtual bool onUpdate();
    virtual void onShutdown();

    void setGLWidget(QGLWidget* glWidget);
    void loadScene(const char* const name);

protected:
    virtual void onInitialize();
    virtual void onInitialized();

private:
    void initializeOptions();
    void initializeDefaultMemoryPool();
    void initializeFileSystem();
    void initializeEventManager();
    void initializePlatformManager();
    void initializeWindow();
    void initializeTaskScheduler();
    void initializeSceneManager();

    Controller* controller;

    boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
    boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
    boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
    boost::shared_ptr<Core::Events::EventManager> eventManager;
    boost::shared_ptr<Platform::PlatformManager> platformManager;
    boost::shared_ptr<Graphics::Window> window;
    boost::shared_ptr<Core::TaskScheduler> taskScheduler;
    boost::shared_ptr<Core::SceneManager> sceneManager;

    QGLWidget* glWidget;
};

#endif // EDITORAPPLICATION_H
