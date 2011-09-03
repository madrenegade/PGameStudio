#include "Utilities/Memory/SmallObjectAllocator.h"
#include "Utilities/Memory/constants.h"

#include <gtest/gtest.h>
#include <chrono>
#include <boost/scoped_ptr.hpp>
#include <google/profiler.h>

using namespace Utilities::Memory;

const size_t maxSize = 512 * KByte;
    const size_t pageSize = 1 * KByte;
    const size_t blockSize = 32 * Byte;
    
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
    // check that blocksize has enough bits
    FAIL();
}

typedef std::chrono::duration<long, std::ratio<1, 1000>> ms;

TEST_F(SmallObjectAllocatorTest, testAllocationPerformance)
{
    ProfilerStart("SmallObjectAllocator");
    
    std::cout << "Allocating " << allocations << std::endl;
    auto start = std::chrono::system_clock::now();
    
    pointer ptrs[allocations];
    
    for(size_t i = 0; i < allocations; ++i)
    {
        ptrs[i] = new char[blockSize];
    }
    
    auto end = std::chrono::system_clock::now();
    
    long diff = std::chrono::duration_cast<ms>(end - start).count();
    
    std::cout << "time: " << diff << " ms" << std::endl;
    
    
    
    
    start = std::chrono::system_clock::now();
    
    for(size_t i = 0; i < allocations; ++i)
    {
        allocator->allocate(1);
    }
    
    end = std::chrono::system_clock::now();
    
    diff = std::chrono::duration_cast<ms>(end - start).count();
    
    std::cout << "time: " << diff << " ms" << std::endl;
    
    ProfilerStop();
}