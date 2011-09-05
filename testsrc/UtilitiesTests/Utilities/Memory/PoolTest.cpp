#include "Utilities/Memory/Pool.h"
#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace Utilities::Memory;

TEST(PoolTest, getMemoryUsage)
{
    boost::scoped_ptr<Pool> pool(new Pool(MemoryPoolSettings()));
    EXPECT_EQ(0, pool->getMemoryUsage());
}

