#include "Utilities/Memory/AllocationInfo.h"
#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/functions.h"
#include <gtest/gtest.h>

using namespace Utilities::Memory;

TEST(AllocationInfoTest, constructor)
{
    int i = 5;
    byte_pointer ptr = reinterpret_cast<byte_pointer>(&i);
    AllocationInfo allocationInfo(ptr, sizeof(int), typeid(i));
    
    EXPECT_EQ(ptr, allocationInfo.getPointer());
    EXPECT_EQ(sizeof(int), allocationInfo.getSize());
    EXPECT_EQ(Utilities::demangle(typeid(int).name()), allocationInfo.getType());
}
