#include "Utilities/Memory/Allocators/SmallObjectAllocator.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Memory/constants.h"

#include <gtest/gtest.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <chrono>
#include <boost/scoped_ptr.hpp>
#include <google/profiler.h>
#include <stdexcept>

#include "Utilities/StopWatch.h"

using namespace Utilities::Memory;

const size_t maxSize = 16 * MByte;
const size_t pageSize = 32 * KByte;
const size_t blockSize = 128 * Byte;

class SmallObjectAllocatorTest : public testing::Test
{
protected:
    boost::scoped_ptr<SmallObjectAllocator> allocator;
    size_t allocations;

    virtual void SetUp()
    {
        const size_t usableBlocksPerPage = (pageSize / blockSize) - 1;
        const size_t availablePages = maxSize / pageSize;
        allocations = availablePages * usableBlocksPerPage;
        
        allocator.reset(new SmallObjectAllocator(PageManager::create(maxSize, pageSize), blockSize));
    }
};

TEST_F(SmallObjectAllocatorTest, assertBlockSizeIsBigEnough)
{
    PageManager::Ptr pageManager = PageManager::create(4 * KByte, 4 * KByte);
    
    EXPECT_THROW({
        boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(pageManager, 16 * Byte));
    }, std::logic_error);
}

#ifdef DEBUG

TEST_F(SmallObjectAllocatorTest, allocateShouldCheckThatRequestedSizeFitsInOneBlock)
{
    EXPECT_THROW(allocator->allocate(blockSize + 1), std::logic_error);
}
#endif

TEST_F(SmallObjectAllocatorTest, getMemoryUsage)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);
    
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(pageManager, 32 * Byte));

    for (unsigned int i = 0; i < (1 * KByte / 32 * Byte) - 1; ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ((i + 1) * 32 * Byte, ptr->getMemoryUsage());
    }
}

TEST_F(SmallObjectAllocatorTest, getFreeMemory)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);
    
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(pageManager, 32 * Byte));

    const size_t maxMemory = 1 * KByte - 32 * Byte;

    EXPECT_EQ(maxMemory, ptr->getFreeMemory());

    for (unsigned int i = 1; i < (1 * KByte / 32 * Byte); ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ(maxMemory - (i * 32 * Byte), ptr->getFreeMemory());
    }
}

TEST_F(SmallObjectAllocatorTest, testAllocationPerformance)
{
    ProfilerStart("SmallObjectAllocator");

    std::cout << "Allocating " << allocations << std::endl;

    {
        boost::scoped_array<pointer> ptrs(new pointer[allocations]);
        
        Utilities::StopWatch sw("Time (default new)");

        for (size_t i = 0; i < allocations; ++i)
        {
            ptrs[i] = new char[blockSize];
        }

        for (size_t i = 0; i < allocations; ++i)
        {
            delete[] ptrs[i];
        }
    }

    {
        boost::scoped_array<pointer> ptrs(new pointer[allocations]);
        
        Utilities::StopWatch sw("Time (allocate)");

        for (size_t i = 0; i < allocations; ++i)
        {
            ptrs[i] = allocator->allocate(blockSize);
        }

        for (size_t i = 0; i < allocations; ++i)
        {
            allocator->deallocate(ptrs[i], blockSize, 1);
        }
    }

    ProfilerStop();
}
