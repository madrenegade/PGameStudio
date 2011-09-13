#include "Game/Application.h"

// TODO: Release memory tracker
#ifdef DEBUG
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#endif

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/FileSystemFactory.h"

#include "Core/Events/EventManager.h"

#include "Platform/PlatformManager.h"

#include "Graphics/Window.h"
#include "Graphics/GraphicsContext.h"

#include <glog/logging.h>

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
    
    void Application::onQuit(const EventID& event, const boost::any& data)
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
    }

    void Application::onInitialized()
    {
        LOG(INFO) << "Game initialized";
    }

    void Application::onRun()
    {
        LOG(INFO) << "Starting game...";
    }

    bool Application::onUpdate()
    {
        BEGIN_NEW_FRAME(memoryManager);
        
        window->getGraphicsContext()->MakeCurrent();
        window->getGraphicsContext()->SwapBuffers();
        window->getGraphicsContext()->Release();
        
        platformManager->handleOSEvents();
        eventManager->handleEvents();

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
        
        // options for the default memory pool
        po::options_description options("Default memory pool options");

        options.add_options()
            ("Default.memory.smallObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the small object area in the default memory pool")
            ("Default.memory.smallObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the small object area in the default memory pool")
            ("Default.memory.smallObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the small object area in the default memory pool")

            ("Default.memory.mediumObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the medium object area in the default memory pool")
            ("Default.memory.mediumObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the medium object area in the default memory pool")
            ("Default.memory.mediumObjects.blockSize", po::value<size_t > ()->default_value(256 * Byte), "Block size for the medium object area in the default memory pool")

            ("Default.memory.largeObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the large object area in the default memory pool")
            ("Default.memory.largeObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the large object area in the default memory pool")
            ("Default.memory.largeObjects.blockSize", po::value<size_t > ()->default_value(512 * Byte), "Block size for the large object area in the default memory pool");

        properties->addOptions(options);

        FileSystem::addOptionsTo(properties);
        Graphics::Window::addOptionsTo(properties);

        properties->parse("settings.ini");
    }

    void Application::initializeDefaultMemoryPool()
    {
        VLOG(1) << "Initializing default memory pool";
        
        size_t soMax = properties->get<size_t > ("Default.memory.smallObjects.maxSize");
        size_t soPage = properties->get<size_t > ("Default.memory.smallObjects.pageSize");
        size_t soBlock = properties->get<size_t > ("Default.memory.smallObjects.blockSize");

        size_t moMax = properties->get<size_t > ("Default.memory.mediumObjects.maxSize");
        size_t moPage = properties->get<size_t > ("Default.memory.mediumObjects.pageSize");
        size_t moBlock = properties->get<size_t > ("Default.memory.mediumObjects.blockSize");

        size_t loMax = properties->get<size_t > ("Default.memory.largeObjects.maxSize");
        size_t loPage = properties->get<size_t > ("Default.memory.largeObjects.pageSize");
        size_t loBlock = properties->get<size_t > ("Default.memory.largeObjects.blockSize");

        MemoryPoolSettings defaultPoolSettings(
            soMax, soPage, soBlock,
            moMax, moPage, moBlock,
            loMax, loPage, loBlock);

        boost::shared_ptr<Pool> pool = Pool::create(defaultPoolSettings);
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
}
