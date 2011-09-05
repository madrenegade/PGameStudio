#include "Utilities/functions.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace Utilities;

TEST(FunctionsTest, demangleShouldSucceedForValidTypes)
{
    EXPECT_EQ("int", demangle(typeid(int).name()));
}

TEST(FunctionsTest, demangleShouldReturnInitialInputOnErrors)
{
    EXPECT_EQ("non-existing-type", demangle("non-existing-type"));
}

TEST(FunctionsTest, fillMemoryShouldFailForNullPointer)
{
    EXPECT_THROW(fillMemory(0, 1, 0), std::invalid_argument);
}

TEST(FunctionsTest, fillMemoryShouldFailForZeroSize)
{
    Memory::byte buffer[1];
    
    EXPECT_THROW(fillMemory(buffer, 0, 0), std::invalid_argument);
}

TEST(FunctionsTest, fillMemory)
{
    Memory::byte buffer[10];
    
    fillMemory(buffer, 10, 5);
    
    for(unsigned int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(5, buffer[i]);
    }
}
