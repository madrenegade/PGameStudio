#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/string.h"
#include <gtest/gtest.h>

using namespace Utilities::Memory;

const pool_id DEFAULT_POOL = 0;

class STLAllocatorTest : public testing::Test
{
protected:
    boost::shared_ptr<MemoryTracker> tracker;
    boost::shared_ptr<MemoryManager> memory;
    boost::shared_ptr<Pool> pool;

    virtual void SetUp()
    {
        pool = Pool::create("Test");
        tracker.reset(new DebugMemoryTracker());

        memory = MemoryManager::create(tracker);
        memory->registerMemoryPool(pool);

        STLAllocator<void>::memory = memory;
    }
};

TEST_F(STLAllocatorTest, construct)
{
    std::vector<String, STLAllocator<String> > v;
    v.push_back("abcd");

    ASSERT_EQ("abcd", v.at(0));
}
