#include "Utilities/Memory/SmallObjectAllocator.h"
#include "Utilities/Memory/constants.h"

#include <gtest/gtest.h>
#include <chrono>
#include <boost/scoped_ptr.hpp>
#include <google/profiler.h>
#include <stdexcept>

using namespace Utilities::Memory;

const size_t maxSize = 32 * MByte;
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
        boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(4 * KByte, 4 * KByte, 16*Byte));
    }, std::logic_error);
}

TEST_F(SmallObjectAllocatorTest, allocateShouldCheckThatRequestedSizeFitsInOneBlock)
{
    EXPECT_THROW(allocator->allocate(blockSize + 1), std::logic_error);
}

TEST_F(SmallObjectAllocatorTest, getMemoryUsage)
{
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(1 * KByte, 1 * KByte, 32*Byte));
    
    for(unsigned int i = 0; i < (1*KByte / 32*Byte) - 1; ++i)
    {
        ptr->allocate(1);
        
        EXPECT_EQ((i+1) * 32 * Byte, ptr->getMemoryUsage());
    }
}

TEST_F(SmallObjectAllocatorTest, getFreeMemory)
{
    boost::scoped_ptr<SmallObjectAllocator> ptr(new SmallObjectAllocator(1 * KByte, 1 * KByte, 32*Byte));
    
    const size_t maxMemory = 1*KByte - 32*Byte;
    
    EXPECT_EQ(maxMemory, ptr->getFreeMemory());
    
    for(unsigned int i = 1; i < (1*KByte / 32*Byte); ++i)
    {
        ptr->allocate(1);
        
        EXPECT_EQ(maxMemory - (i * 32*Byte), ptr->getFreeMemory());
    }
}

typedef std::chrono::duration<long, std::ratio < 1, 1000 >> ms;

TEST_F(SmallObjectAllocatorTest, testAllocationPerformance)
{
    ProfilerStart("SmallObjectAllocator");

    std::cout << "Allocating " << allocations << std::endl;
    auto start = std::chrono::system_clock::now();

    pointer ptrs[allocations];

    for (size_t i = 0; i < allocations; ++i)
    {
        ptrs[i] = new char[blockSize];
    }

//    for (size_t i = 0; i < allocations; ++i)
//    {
//        delete[] ptrs[i];
//    }

    auto end = std::chrono::system_clock::now();

    long diff = std::chrono::duration_cast<ms > (end - start).count();

    std::cout << "time (default new): " << diff << " ms" << std::endl;




    start = std::chrono::system_clock::now();

    for (size_t i = 0; i < allocations; ++i)
    {
        ptrs[i] = allocator->allocate(blockSize);
    }

//    for (size_t i = 0; i < allocations; ++i)
//    {
//        allocator->deallocate(ptrs[i], blockSize, 1);
//    }

    end = std::chrono::system_clock::now();

    diff = std::chrono::duration_cast<ms > (end - start).count();

    std::cout << "time (SOA): " << diff << " ms" << std::endl;

    ProfilerStop();
}