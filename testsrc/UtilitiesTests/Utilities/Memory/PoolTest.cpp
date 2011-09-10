#include "Utilities/Memory/Pool.h"
#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace Utilities::Memory;

TEST(PoolTest, getMemoryUsage)
{
    boost::shared_ptr<Pool> pool = Pool::create();
    EXPECT_EQ(0, pool->getMemoryUsage());
}

