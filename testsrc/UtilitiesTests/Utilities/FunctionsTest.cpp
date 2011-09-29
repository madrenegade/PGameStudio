#include "Utilities/functions.h"
#include "Utilities/Memory/constants.h"
#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/Memory/constants.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <bitset>
#include <bits/stringfwd.h>

#include "Utilities/StopWatch.h"

using namespace Utilities;

TEST(FunctionsTest, demangleShouldSucceedForValidTypes)
{
    EXPECT_EQ("int", demangle(typeid (int) .name()));
}

TEST(FunctionsTest, demangleShouldReturnInitialInputOnErrors)
{
    EXPECT_EQ("non-existing-type", demangle("non-existing-type"));
}

#ifdef DEBUG
TEST(FunctionsTest, fillMemoryShouldFailForNullPointer)
{
    EXPECT_THROW(fillMemory(0, 1, 0), std::invalid_argument);
}

TEST(FunctionsTest, fillMemoryShouldFailForZeroSize)
{
    Memory::byte buffer[1];

    EXPECT_THROW(fillMemory(buffer, 0, 0), std::invalid_argument);
}
#endif

TEST(FunctionsTest, fillMemory)
{
    Memory::byte buffer[10];

    fillMemory(buffer, 10, 5);

    for (unsigned int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(5, buffer[i]);
    }
}

std::string generateBitSet(long bitToUnset)
{
    std::string s;
    s.resize(Memory::ULONG_BITS);

    for (unsigned long i = 0; i < Memory::ULONG_BITS; ++i)
    {
        if (bitToUnset != -1)
        {
            if (i > (Memory::ULONG_BITS - 1) - bitToUnset)
            {
                s[i] = '0';
            }
            else
            {
                s[i] = '1';
            }
        }
        else
        {
            s[i] = '0';
        }
    }

    return s;
}

TEST(FunctionsTest, countsBitsFromRight)
{
    std::bitset<Memory::ULONG_BITS> bits(generateBitSet(-1));
    EXPECT_EQ(Memory::ULONG_BITS, countZeroBitsFromRight(bits.to_ulong()));
        
    for (size_t i = 0; i < Memory::ULONG_BITS; ++i)
    {
        std::bitset<Memory::ULONG_BITS> bits(generateBitSet(i));

        EXPECT_EQ(i, countZeroBitsFromRight(bits.to_ulong()));
    }
}