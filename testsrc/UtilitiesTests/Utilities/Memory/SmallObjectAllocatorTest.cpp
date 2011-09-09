#include "Utilities/Memory/Allocators/SmallObjectAllocator.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/MemoryManager.h"
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

const size_t maxSize = 64 * MByte;
const size_t pageSize = 16 * KByte;
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
        allocator.reset(new SmallObjectAllocator(maxSize, pageSize, blockSize));
    }
};

TEST_F(SmallObjectAllocatorTest, assertBlockSizeIsBigEnough)
{
    EXPECT_THROW({
        boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(4 * KByte, 4 * KByte, 16 * Byte));
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
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(1 * KByte, 1 * KByte, 32 * Byte));

    for (unsigned int i = 0; i < (1 * KByte / 32 * Byte) - 1; ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ((i + 1) * 32 * Byte, ptr->getMemoryUsage());
    }
}

TEST_F(SmallObjectAllocatorTest, getFreeMemory)
{
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(1 * KByte, 1 * KByte, 32 * Byte));

    const size_t maxMemory = 1 * KByte - 32 * Byte;

    EXPECT_EQ(maxMemory, ptr->getFreeMemory());

    for (unsigned int i = 1; i < (1 * KByte / 32 * Byte); ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ(maxMemory - (i * 32 * Byte), ptr->getFreeMemory());
    }
}

//TEST_F(SmallObjectAllocatorTest, testAllocationPerformance)
//{
//    ProfilerStart("SmallObjectAllocator");
//
//    std::cout << "Allocating " << allocations << std::endl;
//
//    {
//        Utilities::StopWatch sw("Time (default new)");
//
//        pointer ptrs[allocations];
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            ptrs[i] = new char[blockSize];
//        }
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            delete[] ptrs[i];
//        }
//    }
//
//    {
//        Utilities::StopWatch sw("Time (allocate)");
//
//        pointer ptrs[allocations];
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            ptrs[i] = allocator->allocate(blockSize);
//        }
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            allocator->deallocate(ptrs[i], blockSize, 1);
//        }
//    }
//
//    ProfilerStop();
//}

TEST_F(SmallObjectAllocatorTest, testMemoryAllocationPerformance)
{
    boost::shared_ptr<MemoryTracker> tracker(new DebugMemoryTracker());
    boost::shared_ptr<MemoryManager> memory = MemoryManager::create(tracker);
    boost::shared_ptr<Pool> pool(new Pool(MemoryPoolSettings(8*MByte, 16*KByte, 128*Byte)));
    
    const size_t usableBlocksPerPage = (16*KByte / 128*Byte) - 1;
    const size_t availablePages = (8*MByte) / (16*KByte);
    const size_t numAllocations = availablePages * usableBlocksPerPage;
    
    std::cout << "Allocating " << numAllocations << std::endl;
    
    memory->registerMemoryPool(pool);

    {
//        Utilities::StopWatch sw("Time (default new)");

//        pointer ptrs[allocations];
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            ptrs[i] = new char[blockSize];
//        }
//
//        for (size_t i = 0; i < allocations; ++i)
//        {
//            delete[] ptrs[i];
//        }
    }

    {
        Utilities::StopWatch sw("Time (allocate)");

        boost::shared_array<char> ptrs[numAllocations];

        for (size_t i = 0; i < numAllocations; ++i)
        {
            ptrs[i] = memory->allocate<char, blockSize>();
        }

//        for (size_t i = 0; i < allocations; ++i)
//        {
//            allocator->deallocate(ptrs[i], blockSize, 1);
//        }
        //ProfilerStop();
    }
}