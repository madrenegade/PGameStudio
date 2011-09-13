#include "Game/Application.h"

using namespace Game;

int main(int argc, char** argv)
{
    Application app;
    app.initialize();
    app.run();
    
//    MemoryTracker::Ptr memoryTracker(new DebugMemoryTracker());
//    MemoryManager::Ptr memoryManager = MemoryManager::create(memoryTracker);
//
//    boost::shared_ptr<Pool> pool = Pool::create();
//    pool_id poolID = memoryManager->registerMemoryPool(pool);
//
//    BEGIN_NEW_FRAME(memoryManager);
//    
//    boost::shared_ptr<PropertyManager> properties(new PropertyManager);
//
//    properties->parse(argc, argv);
//    
//    boost::shared_ptr<FileSystem> fs = FileSystemFactory::create(memoryManager, properties, FileSystemBackend::PhysFS);
//    
//    properties->parse("settings.ini");
//    
//    fs->initialize();
//    
//    File f(fs->read("settings.ini"));
//    
//    boost::shared_ptr<EventManager> em = memoryManager->construct(EventManager(memoryManager), 0);
// 

    return 0;
}