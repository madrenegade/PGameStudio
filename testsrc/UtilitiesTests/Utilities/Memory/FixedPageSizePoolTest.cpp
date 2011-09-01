#include "Utilities/Memory/FixedPageSizePool.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <boost/scoped_ptr.hpp>

using namespace Utilities::Memory;

class FixedPageSizePoolTest : public testing::Test
{
protected:
    
    virtual void SetUp()
    {
    }
};

TEST_F(FixedPageSizePoolTest, ctorShouldFailForZeroPageSize)
{
    ASSERT_THROW(FixedPageSizePool(4, 0), std::logic_error);
}

TEST_F(FixedPageSizePoolTest, ctorShouldFailForIfPageSizeIsTooLarge)
{
    ASSERT_THROW(FixedPageSizePool(4, 8), std::invalid_argument);
}

TEST_F(FixedPageSizePoolTest, ctorShouldFailForIfPageSizeIsNotMultipleOfPoolSize)
{
    ASSERT_THROW(FixedPageSizePool(4, 3), std::invalid_argument);
}

