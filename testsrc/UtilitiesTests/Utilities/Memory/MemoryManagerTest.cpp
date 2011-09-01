#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace Utilities::Memory;

class MemoryManagerTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }
};

TEST_F(MemoryManagerTest, ctorShouldFailForMaxMemoryZero1)
{
    ASSERT_THROW(MemoryManager(MemoryManagerSettings(64, 0, 1)), std::invalid_argument);
}

TEST_F(MemoryManagerTest, ctorShouldFailForMaxMemoryZero2)
{
    ASSERT_THROW(MemoryManager(MemoryManagerSettings(64, 0, 1)), std::invalid_argument);
}

TEST_F(MemoryManagerTest, allocateShouldFailIfLimitForSmallObjectsIsExceeded)
{
    MemoryManager memory(MemoryManagerSettings(8, 1, 1));
    ASSERT_THROW(memory.allocate<int>(1), OutOfMemoryException);
}

TEST_F(MemoryManagerTest, allocateShouldFailIfLimitForLargeObjectsIsExceeded)
{
    MemoryManager memory(MemoryManagerSettings(8, 8, 8, 8, 8));
    pool_id id = memory.createPoolForLargeObjects(4);
    ASSERT_THROW(memory.allocate<int>(3, id), OutOfMemoryException);
}

TEST_F(MemoryManagerTest, allocateLargeObject)
{
    MemoryManager memory(MemoryManagerSettings(2, 1, 4, 8, 8));
    pool_id id = memory.createPoolForLargeObjects(4);

    int* ptr = memory.construct(static_cast<int> (5));

    EXPECT_EQ(5, *ptr);
}

//TEST_F(MemoryManagerTest, allocateSmallObject)
//{
//    MemoryManager memory(MemoryManagerSettings(4, 4, 1));
//
//    int* ptr = memory.construct(static_cast<int> (5));
//
//    EXPECT_EQ(5, *ptr);
//}

TEST_F(MemoryManagerTest, deallocateShouldUseCorrectManager)
{
    MemoryManager memory(MemoryManagerSettings(2, 16, 8, 16, 8));
    pool_id id = memory.createPoolForLargeObjects(8);
    
    long* ptr = memory.construct(5L, id);
    
    EXPECT_NO_THROW(memory.deallocate<long>(ptr, 1, id));
}