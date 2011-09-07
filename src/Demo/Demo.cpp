#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"

#include "Core/Events/EventHandler.h"

using namespace Utilities::Memory;
using namespace Core::Events;

int main(int argc, char** argv)
{
    MemoryTracker::Ptr memoryTracker(new DebugMemoryTracker());
    MemoryManager::Ptr memoryManager = MemoryManager::create(memoryTracker);
    
    boost::shared_ptr<Pool> pool(new Pool);
    pool_id poolID = memoryManager->registerMemoryPool(pool);
    
    boost::shared_ptr<EventHandler> eventHandler = CONSTRUCT(memoryManager, EventHandler(), poolID);
    
    return 0;
}