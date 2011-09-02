#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/Memory/MemoryTrackerMock.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace Utilities::Memory;

class MemoryManagerTest : public testing::Test
{
protected:
    boost::scoped_ptr<MemoryManager> memory;
    
    virtual void SetUp()
    {
        boost::shared_ptr<MemoryTracker> tracker(new MemoryTrackerMock());
        
        memory.reset(new MemoryManager(tracker));
    }
};

TEST_F(MemoryManagerTest, allocateShouldFailIfPoolDoesNotExists)
{
    EXPECT_THROW(memory->allocate<int>(1), std::logic_error);
}