#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace Utilities::Memory;

TEST(MemoryManagerTest, ctorShouldFailForMaxMemoryZero1)
{
    ASSERT_THROW(MemoryManager(64, 0, 1), std::invalid_argument);
}

TEST(MemoryManagerTest, ctorShouldFailForMaxMemoryZero2)
{
    ASSERT_THROW(MemoryManager(64, 1, 0), std::invalid_argument);
}

TEST(MemoryManagerTest, allocateShouldFailIfLimitForSmallObjectsIsExceeded)
{
    MemoryManager memory(8, 1, 1);
    ASSERT_THROW(memory.allocate<int>(1), OutOfMemoryException);
}

TEST(MemoryManagerTest, allocateShouldFailIfLimitForLargeObjectsIsExceeded)
{
    MemoryManager memory(8, 1, 1);
    ASSERT_THROW(memory.allocate<int>(3), OutOfMemoryException);
}

TEST(MemoryManagerTest, allocateLargeObject)
{
    MemoryManager memory(2, 1, 4);

    int* ptr = memory.construct(static_cast<int> (5));

    EXPECT_EQ(5, *ptr);
}

TEST(MemoryManagerTest, allocateSmallObject)
{
    MemoryManager memory(4, 4, 1);

    int* ptr = memory.construct(static_cast<int> (5));

    EXPECT_EQ(5, *ptr);
}

TEST(MemoryManagerTest, deallocateShouldUseCorrectManager)
{
    MemoryManager memory(2, 8, 8);
    
    long* ptr = memory.construct(5L);
    
    EXPECT_NO_THROW(memory.deallocate<long>(ptr, 1));
}