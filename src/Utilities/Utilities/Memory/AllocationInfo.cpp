#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/Memory/AllocationInfo.h"
#include "Utilities/functions.h"

namespace Utilities
{
    namespace Memory
    {
        AllocationInfo::AllocationInfo()
            : pool("unknown"), ptr(0), bytes(0), type("unknown")
        {

        }

        AllocationInfo::AllocationInfo(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type)
            : pool(pool), ptr(ptr), bytes(bytes), type(type.name())
        {

        }

        const char* AllocationInfo::getPool() const
        {
            return pool;
        }

        const_byte_pointer AllocationInfo::getPointer() const
        {
            return ptr;
        }

        size_t AllocationInfo::getSize() const
        {
            return bytes;
        }

        std::string AllocationInfo::getType() const
        {
            return demangle(type.c_str());
        }
    }
}
