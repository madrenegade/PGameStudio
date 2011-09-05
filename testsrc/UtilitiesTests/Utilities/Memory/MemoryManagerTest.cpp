#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"
#include "Utilities/Memory/MemoryTrackerMock.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <list>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace Utilities::Memory;

class MemoryManagerTest : public testing::Test
{
protected:
    boost::scoped_ptr<MemoryManager> memory;
    boost::shared_ptr<Pool> pool;
    boost::shared_ptr<MemoryTrackerMock> tracker;

    virtual void SetUp()
    {
        pool.reset(new Pool(MemoryPoolSettings()));
        tracker.reset(new MemoryTrackerMock());

        memory.reset(new MemoryManager(tracker));
    }
};

TEST_F(MemoryManagerTest, construct)
{
    memory->registerMemoryPool(pool);
    int i = 5;
    memory->construct(5);
}

TEST_F(MemoryManagerTest, allocateShouldFailIfPoolDoesNotExists)
{
    EXPECT_THROW((memory->allocate<short, 2 > ()), std::logic_error);
}

TEST_F(MemoryManagerTest, allocateShouldSucceedWithMockPool)
{
    pool_id id = memory->registerMemoryPool(pool);
    ASSERT_NO_THROW((memory->allocate<short, 2 > ()));
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
    memory->allocate<short, 2 > ();

    EXPECT_EQ(1, tracker->getAllocations());
}

TEST_F(MemoryManagerTest, deallocateShouldTrackDeallocation)
{
    EXPECT_EQ(0, tracker->getDeallocations());

    memory->registerMemoryPool(pool);

    {
        boost::shared_array<int> i = memory->allocate<int, 2 > ();
    }

    EXPECT_EQ(1, tracker->getDeallocations());
}