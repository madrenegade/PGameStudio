#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Memory/constants.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"

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
const size_t pageSize = 128 * KByte;
const size_t blockSize = 256 * Byte;

class MediumObjectAllocatorTest : public testing::Test
{
protected:
    boost::scoped_ptr<MediumObjectAllocator> allocator;
    size_t allocations;

    virtual void SetUp()
    {
        const size_t usableBlocksPerPage = (pageSize / blockSize) - 1;
        const size_t availablePages = maxSize / pageSize;
        allocations = availablePages * usableBlocksPerPage;

        allocator.reset(new MediumObjectAllocator(PageManager::create(maxSize, pageSize), blockSize));
    }
};

TEST_F(MediumObjectAllocatorTest, assertBlockSizeIsBigEnough)
{
    PageManager::Ptr pageManager = PageManager::create(4 * KByte, 4 * KByte);

    EXPECT_THROW( {
        boost::scoped_ptr<MediumObjectAllocator> ptr(new MediumObjectAllocator(pageManager, 16 * Byte));
    }, std::logic_error);
}

TEST_F(MediumObjectAllocatorTest, getMemoryUsage)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);

    boost::scoped_ptr<MediumObjectAllocator> ptr(new MediumObjectAllocator(pageManager, 32 * Byte));

    for (unsigned int i = 0; i < (1 * KByte / 32 * Byte) - 1; ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ((i + 1) * 32 * Byte, ptr->getMemoryUsage());
    }
}

TEST_F(MediumObjectAllocatorTest, getFreeMemory)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);

    boost::scoped_ptr<MediumObjectAllocator> ptr(new MediumObjectAllocator(pageManager, 32 * Byte));

    const size_t maxMemory = 1 * KByte - 32 * Byte;

    EXPECT_EQ(maxMemory, ptr->getFreeMemory());

    for (unsigned int i = 1; i < (1 * KByte / 32 * Byte); ++i)
    {
        ptr->allocate(1);

        EXPECT_EQ(maxMemory - (i * 32 * Byte), ptr->getFreeMemory());
    }
}

#ifdef DEBUG
TEST_F(MediumObjectAllocatorTest, allocateShouldFailForTooManyBytes)
{
    EXPECT_THROW(allocator->allocate(pageSize), OutOfMemoryException);
}
#endif

TEST_F(MediumObjectAllocatorTest, testAllocateFailsWhenNotEnoughConsecutiveFreeBlocksAreAvailable)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);
    boost::scoped_ptr<MediumObjectAllocator> ptr(new MediumObjectAllocator(pageManager, 128 * Byte));

    ptr->allocate(3 * 128*Byte);
    ptr->allocate(1 * 128*Byte);
    ptr->allocate(3 * 128*Byte);

    EXPECT_THROW(ptr->allocate(1 * 128*Byte), OutOfMemoryException);
}

TEST_F(MediumObjectAllocatorTest, testAllocateUsesPageWithEnoughConsecutiveFreeBlocks)
{
    PageManager::Ptr pageManager = PageManager::create(1 * KByte, 1 * KByte);
    boost::scoped_ptr<MediumObjectAllocator> ptr(new MediumObjectAllocator(pageManager, 128 * Byte));

    ptr->allocate(3 * 128*Byte);
    byte_pointer p = ptr->allocate(1 * 128*Byte);
    ptr->allocate(3 * 128*Byte);

    ptr->deallocate(p, 128, 1);

    // allocate 2 additional blocks
    EXPECT_NE((byte_pointer)0, ptr->allocate(1 * 128*Byte));
}

TEST_F(MediumObjectAllocatorTest, testAllocationPerformance)
{
    ProfilerStart("MediumObjectAllocator");

    std::cout << "Allocating " << allocations << std::endl;

    {
        boost::scoped_array<byte_pointer> ptrs(new byte_pointer[allocations]);

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
        boost::scoped_array<byte_pointer> ptrs(new byte_pointer[allocations]);

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

