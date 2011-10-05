#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/Exceptions/AllocationException.h"

#include <gtest/gtest.h>


using namespace Utilities::Memory;

class DebugMemoryTrackerTest : public testing::Test
{
protected:
    std::shared_ptr<MemoryTracker> tracker;

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
    tracker->trackAllocation<int>("Test", 0, 99);

    EXPECT_EQ(tracker->getMemoryUsage(), 99);
}

TEST_F(DebugMemoryTrackerTest, getMemoryUsageShouldProperlyUpdateOnNewAllocation)
{
    tracker->trackAllocation<int>("Test", 0, 99);
    tracker->trackAllocation("Test", tracker.get(), 1);

    EXPECT_EQ(tracker->getMemoryUsage(), 100);
}

TEST_F(DebugMemoryTrackerTest, getMemoryUsageShouldProperlyUpdateOnDeallocation)
{
    tracker->trackAllocation<int>("Test", 0, 100);
    tracker->trackDeallocation<int>("Test", 0, 100);

    EXPECT_EQ(tracker->getMemoryUsage(), 0);
}

TEST_F(DebugMemoryTrackerTest, trackAllocationShouldFailForDuplicatePointers)
{
    tracker->trackAllocation<int>("Test", 0, 1);

    ASSERT_THROW(tracker->trackAllocation<int>("Test", 0, 1), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackAllocationShouldFailForZeroSize)
{
    ASSERT_THROW(tracker->trackAllocation<int>("Test", 0, 0), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailWithoutMatchingAllocation)
{
    ASSERT_THROW(tracker->trackDeallocation<int>("Test", 0, 100), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidPointer)
{
    tracker->trackAllocation<MemoryTracker>("Test", 0, 100);

    ASSERT_THROW(tracker->trackDeallocation("Test", &tracker, 100), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidSize)
{
    tracker->trackAllocation<int>("Test", 0, 100);

    ASSERT_THROW(tracker->trackDeallocation<int>("Test", 0, 1), AllocationException);
}

TEST_F(DebugMemoryTrackerTest, trackDeallocationShouldFailForInvalidType)
{
    tracker->trackAllocation<int>("Test", 0, 100);

    ASSERT_THROW(tracker->trackDeallocation<short>("Test", 0, 100), AllocationException);
}
