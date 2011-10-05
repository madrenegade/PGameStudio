#include <gtest/gtest.h>
#include <glog/logging.h>
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/STLAllocator.h"

using namespace Utilities::Memory;

int main(int argc, char** argv)
{
//    std::shared_ptr<MemoryTracker> tracker(new DebugMemoryTracker);
//    std::shared_ptr<MemoryManager> memory = MemoryManager::create(tracker);
//    std::shared_ptr<Pool> pool(new Pool);
//
//    memory->registerMemoryPool(pool);
//
//    Utilities::Memory::STLAllocator<void>::memory = memory;

    ::testing::InitGoogleTest(&argc, argv);
    //google::InitGoogleLogging(argv[0]);

    return RUN_ALL_TESTS();
}
