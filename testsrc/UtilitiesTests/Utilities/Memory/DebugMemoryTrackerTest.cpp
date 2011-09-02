#include "Utilities/Memory/DebugMemoryTracker.h"
#include "Utilities/Memory/AllocationException.h"

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

using namespace Utilities::Memory;

class DebugMemoryTrackerTest : public testing::Test
{
protected:
    boost::shared_ptr<MemoryTracker> tracker;
    
    virtual void SetUp()
    {
        tracker.reset(new DebugMemoryTracker());
    }
};

TEST_F(DebugMemoryTrackerTest, getMemoryUsageShouldReturnZeroInitially)
{
    EXPECT_EQ(tracker->getMemoryUsage(), 0);
}

TEST_F(DebugMemoryTrackerTest, getMemoryUsage)
{
    tracker->trackAllocation<int>(0, 99);
    
    EXPECT_EQ(tracker->getMemoryUsage(), 99);
}

TEST_F(DebugMemoryTrackerTest, getMemoryUsageShouldProperlyUpdateOnNewAllocation)
{
    tracker->trackAllocation<int>(0, 99);
    tracker->trackAllocation(tracker.get(), 1);
    
    EXPECT_EQ(tracker->getMemoryUsage(), 100);
}

TEST_F(DebugMemoryTrackerTest, getMemoryUsageShouldProperlyUpdateOnDeallocation)
{
    tracker->trackAllocation<int>(0, 100);
    tracker->trackDeallocation<int>(0, 100);
    
    EXPECT_EQ(tracker->getMemoryUsage(), 0);
}

TEST_F(DebugMemoryTrackerTest, trackAllocationShouldFailForDuplicatePointers)
{
    tracker->trackAllocation<int>(0, 1);
    
    ASSERT_THROW(tracker->trackAllocation<int>(0, 1), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackAllocationShouldFailForZeroSize)
{
    ASSERT_THROW(tracker->trackAllocation<int>(0, 0), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailWithoutMatchingAllocation)
{
    ASSERT_THROW(tracker->trackDeallocation<int>(0, 100), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidPointer)
{
    tracker->trackAllocation<MemoryTracker>(0, 100);
    
    ASSERT_THROW(tracker->trackDeallocation(&tracker, 100), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidSize)
{
    tracker->trackAllocation<int>(0, 100);
    
    ASSERT_THROW(tracker->trackDeallocation<int>(0, 1), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidType)
{
    tracker->trackAllocation<int>(0, 100);
    
    ASSERT_THROW(tracker->trackDeallocation<short>(0, 100), AllocationException);
}