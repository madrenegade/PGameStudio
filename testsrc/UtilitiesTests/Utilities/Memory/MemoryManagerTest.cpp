#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/Memory/MemoryTrackerMock.h"
#include "Utilities/Memory/PoolMock.h"

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
    boost::shared_ptr<PoolMock> poolMock;
    boost::shared_ptr<MemoryTrackerMock> tracker;
    
    virtual void SetUp()
    {
        poolMock.reset(new PoolMock());
        tracker.reset(new MemoryTrackerMock());
        
        memory.reset(new MemoryManager(tracker));
    }
};

TEST_F(MemoryManagerTest, allocateShouldFailIfPoolDoesNotExists)
{
    EXPECT_THROW(memory->allocate<int>(1), std::logic_error);
}

TEST_F(MemoryManagerTest, allocateShouldSucceedWithMockPool)
{
    pool_id id = memory->registerMemoryPool(poolMock);
    ASSERT_NO_THROW(memory->allocate<int>(1));
}

TEST_F(MemoryManagerTest, registerPoolShouldFailIfPoolAlreadyExists)
{
    memory->registerMemoryPool(poolMock);
    EXPECT_THROW(memory->registerMemoryPool(poolMock), std::logic_error);
}

TEST_F(MemoryManagerTest, registerPoolShouldCreateUniqueIDs)
{
    std::map<pool_id, boost::shared_ptr<Pool> > ids;
    
    for(int i = 0; i < 100; ++i)
    {
        boost::shared_ptr<Pool> pool(new PoolMock());
        pool_id id = memory->registerMemoryPool(pool);
        
        EXPECT_TRUE(ids.find(id) == ids.end());
        
        ids[id] = pool;
    }
}

TEST_F(MemoryManagerTest, allocateShouldCallAllocateOnPool)
{
    EXPECT_EQ(0, poolMock->getAllocations());
    
    memory->registerMemoryPool(poolMock);
    memory->allocate<int>(1);
    
    EXPECT_EQ(1, poolMock->getAllocations());
}

TEST_F(MemoryManagerTest, deallocateShouldCallDeallocateOnPool)
{
    EXPECT_EQ(0, poolMock->getDeallocations());
    
    memory->registerMemoryPool(poolMock);
    int i = 1;
    memory->deallocate(&i, 1);
    
    EXPECT_EQ(1, poolMock->getDeallocations());
}

TEST_F(MemoryManagerTest, allocateShouldTrackAllocation)
{
    EXPECT_EQ(0, tracker->getAllocations());
    
    memory->registerMemoryPool(poolMock);
    memory->allocate<int>(1);
    
    EXPECT_EQ(1, tracker->getAllocations());
}

TEST_F(MemoryManagerTest, deallocateShouldTrackDeallocation)
{
    EXPECT_EQ(0, tracker->getDeallocations());
    
    memory->registerMemoryPool(poolMock);
    int i = 1;
    memory->deallocate(&i, 1);
    
    EXPECT_EQ(1, tracker->getDeallocations());
}