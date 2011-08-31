#include "Utilities/Memory/MemoryTracker.h"
#include "Utilities/Memory/AllocationException.h"
#include <gtest/gtest.h>

using namespace Utilities::Memory;

TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldReturnZeroInitially)
{
    MemoryTracker tracker;
    EXPECT_EQ(tracker.getAllocatedMemorySize(), 0);
}

TEST(MemoryTrackerTest, getAllocatedMemorySize)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 99, typeid(int));
    
    EXPECT_EQ(tracker.getAllocatedMemorySize(), 99);
}

TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldProperlyUpdateOnNewAllocation)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 99, typeid(int));
    tracker.trackAllocation(&tracker, 1, typeid(int));
    
    EXPECT_EQ(tracker.getAllocatedMemorySize(), 100);
}

TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldProperlyUpdateOnDeallocation)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 100, typeid(int));
    tracker.trackDeallocation(0, 100, typeid(int));
    
    EXPECT_EQ(tracker.getAllocatedMemorySize(), 0);
}

TEST(MemoryTrackerTest, trackAllocationShouldFailForDuplicatePointers)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 1, typeid(int));
    
    ASSERT_THROW(tracker.trackAllocation(0, 1, typeid(int)), AllocationException);
}

TEST(MemoryTrackerTest, trackAllocationShouldFailForZeroSize)
{
    MemoryTracker tracker;
    
    ASSERT_THROW(tracker.trackAllocation(0, 0, typeid(int)), AllocationException);
}

TEST(MemoryTrackerTest, trackDeallocationShouldFailInitially)
{
    MemoryTracker tracker;
    ASSERT_THROW(tracker.trackDeallocation(0, 100, typeid(int)), AllocationException);
}

TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidPointer)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 100, typeid(int));
    
    ASSERT_THROW(tracker.trackDeallocation(&tracker, 100, typeid(int)), AllocationException);
}

TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidSize)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 100, typeid(int));
    
    ASSERT_THROW(tracker.trackDeallocation(0, 1, typeid(int)), AllocationException);
}

TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidType)
{
    MemoryTracker tracker;
    tracker.trackAllocation(0, 100, typeid(int));
    
    ASSERT_THROW(tracker.trackDeallocation(0, 100, typeid(short)), AllocationException);
}