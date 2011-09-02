//#include "Utilities/Memory/MemoryTracker.h"
//#include "Utilities/Memory/AllocationException.h"
//#include <gtest/gtest.h>
//
//using namespace Utilities::Memory;
//
//TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldReturnZeroInitially)
//{
//    MemoryTracker tracker;
//    EXPECT_EQ(tracker.getMemoryUsage(), 0);
//}
//
//TEST(MemoryTrackerTest, getAllocatedMemorySize)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 99);
//    
//    EXPECT_EQ(tracker.getMemoryUsage(), 99);
//}
//
//TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldProperlyUpdateOnNewAllocation)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 99);
//    tracker.trackAllocation(&tracker, 1);
//    
//    EXPECT_EQ(tracker.getAllocatedMemorySize(), 100);
//}
//
//TEST(MemoryTrackerTest, getAllocatedMemorySizeShouldProperlyUpdateOnDeallocation)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 100);
//    tracker.trackDeallocation<int>(0, 100);
//    
//    EXPECT_EQ(tracker.getMemoryUsage(), 0);
//}
//
//TEST(MemoryTrackerTest, trackAllocationShouldFailForDuplicatePointers)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 1);
//    
//    ASSERT_THROW(tracker.trackAllocation<int>(0, 1), AllocationException);
//}
//
//TEST(MemoryTrackerTest, trackAllocationShouldFailForZeroSize)
//{
//    MemoryTracker tracker;
//    
//    ASSERT_THROW(tracker.trackAllocation<int>(0, 0), AllocationException);
//}
//
//TEST(MemoryTrackerTest, trackDeallocationShouldFailInitially)
//{
//    MemoryTracker tracker;
//    ASSERT_THROW(tracker.trackDeallocation<int>(0, 100), AllocationException);
//}
//
//TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidPointer)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<MemoryTracker>(0, 100);
//    
//    ASSERT_THROW(tracker.trackDeallocation(&tracker, 100), AllocationException);
//}
//
//TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidSize)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 100);
//    
//    ASSERT_THROW(tracker.trackDeallocation<int>(0, 1), AllocationException);
//}
//
//TEST(MemoryTrackerTest, trackDeallocationShouldFailForInvalidType)
//{
//    MemoryTracker tracker;
//    tracker.trackAllocation<int>(0, 100);
//    
//    ASSERT_THROW(tracker.trackDeallocation<short>(0, 100), AllocationException);
//}