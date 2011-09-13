#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/Memory/AllocationInfo.h"
#include "Utilities/functions.h"

namespace Utilities
{
    namespace Memory
    {
        AllocationInfo::AllocationInfo()
        : ptr(0), bytes(0), type("unknown")
        {
            
        }
        
        AllocationInfo::AllocationInfo(const_byte_pointer ptr, size_t bytes, const std::type_info& type)
        : ptr(ptr), bytes(bytes), type(type.name())
        {
            
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
