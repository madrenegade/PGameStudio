#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"
#include "Utilities/Memory/MemoryTrackerMock.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <list>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace Utilities::Memory;

const pool_id DEFAULT_POOL = 0;

class MemoryManagerTest : public testing::Test
{
protected:
    boost::shared_ptr<MemoryManager> memory;
    boost::shared_ptr<Pool> pool;
    boost::shared_ptr<MemoryTrackerMock> tracker;

    virtual void SetUp()
    {
        pool.reset(new Pool(MemoryPoolSettings()));
        tracker.reset(new MemoryTrackerMock());

        memory = MemoryManager::create(tracker);
    }
};

TEST_F(MemoryManagerTest, construct)
{
    memory->registerMemoryPool(pool);
    int i = 5;
    
    boost::shared_ptr<int> ptr = CONSTRUCT(memory, i, DEFAULT_POOL);
    
    EXPECT_EQ(i, *ptr);
}

TEST_F(MemoryManagerTest, allocateShouldFailIfPoolDoesNotExists)
{
    EXPECT_THROW((ALLOCATE(memory, short, 2, DEFAULT_POOL)), std::logic_error);
}

TEST_F(MemoryManagerTest, allocateShouldSucceedWithMockPool)
{
    pool_id id = memory->registerMemoryPool(pool);
    ASSERT_NO_THROW((ALLOCATE(memory, short, 2, DEFAULT_POOL)));
}

TEST_F(MemoryManagerTest, registerPoolShouldFailIfPoolAlreadyExists)
{
    memory->registerMemoryPool(pool);
    EXPECT_THROW(memory->registerMemoryPool(pool), std::logic_error);
}

TEST_F(MemoryManagerTest, registerPoolShouldCreateUniqueIDs)
{
    std::map<pool_id, boost::shared_ptr<Pool> > ids;

    for (int i = 0; i < 100; ++i)
    {
        boost::shared_ptr<Pool> pool(new Pool(MemoryPoolSettings()));
        pool_id id = memory->registerMemoryPool(pool);

        EXPECT_TRUE(ids.find(id) == ids.end());

        ids[id] = pool;
    }
}

TEST_F(MemoryManagerTest, allocateShouldTrackAllocation)
{
    EXPECT_EQ(0, tracker->getAllocations());

    memory->registerMemoryPool(pool);
    ALLOCATE(memory, short, 2, DEFAULT_POOL);

    EXPECT_EQ(1, tracker->getAllocations());
}

TEST_F(MemoryManagerTest, deallocateShouldTrackDeallocation)
{
    EXPECT_EQ(0, tracker->getDeallocations());

    memory->registerMemoryPool(pool);

    {
        boost::shared_array<int> i = ALLOCATE(memory, int, 2, DEFAULT_POOL);
    }

    EXPECT_EQ(1, tracker->getDeallocations());
}