#include "Utilities/Memory/AllocatorMock.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"
#include "Utilities/Memory/constants.h"
#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <stdexcept>

using namespace Utilities::Memory;

class AllocatorTest : public testing::Test
{
protected:
    boost::scoped_ptr<AllocatorMock> allocator;

    virtual void SetUp()
    {
        allocator.reset(new AllocatorMock(1 * KByte, 1 * KByte, 32 * Byte));
    }
};

#ifdef DEBUG
TEST_F(AllocatorTest, assertPoolSizeIsMultipleOfPageSize)
{
    EXPECT_THROW({
        boost::scoped_ptr<Allocator> ptr(new AllocatorMock(1 * KByte, 333 * Byte, 111 * Byte));
    }, std::invalid_argument);
}

TEST_F(AllocatorTest, assertPageSizeIsMultipleOfBlockSize)
{
    EXPECT_THROW({
        boost::scoped_ptr<Allocator> ptr(new AllocatorMock(1000 * Byte, 10 * Byte, 8 * Byte));
    }, std::invalid_argument);
}

TEST_F(AllocatorTest, assertPageSizeIsMultipleOfBitsPerByte)
{
    EXPECT_THROW({
        boost::scoped_ptr<Allocator> ptr(new AllocatorMock(1000 * KByte, 10 * Byte, 5 * Byte));
    }, std::invalid_argument);
}
#endif

TEST_F(AllocatorTest, containsShouldReturnFalseInitially)
{
    EXPECT_FALSE(allocator->contains(0));
}

TEST_F(AllocatorTest, containsShouldReturnTrueAfterAllocate)
{
    byte_pointer ptr = allocator->allocate(10);

    EXPECT_TRUE(allocator->contains(ptr));
}

TEST_F(AllocatorTest, allocateShouldFailWhenMaxMemoryIsExceeded)
{
    boost::scoped_ptr<Allocator> ptr(new AllocatorMock(16 * Byte, 16 * Byte, 8 * Byte));
    ptr->allocate(8);

    EXPECT_THROW(ptr->allocate(1), OutOfMemoryException);
}