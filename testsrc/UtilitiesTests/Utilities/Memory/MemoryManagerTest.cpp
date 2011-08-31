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

TEST(MemoryManagerTest, allocate)
{
    MemoryManager memory(2, 1, 4);
    
    int* ptr = new(memory.allocate<int>(1)) int(5);
    
    EXPECT_EQ(5, *ptr);
}