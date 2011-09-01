#include "Utilities/Memory/AllocationInfo.h"
#include "Utilities/functions.h"

namespace Utilities
{
    namespace Memory
    {
        AllocationInfo::AllocationInfo()
        {
            
        }
        
        AllocationInfo::AllocationInfo(const_pointer ptr, size_t bytes, const std::type_info& type)
        : ptr(ptr), bytes(bytes), type(type.name())
        {
            
        }
        
        const_pointer AllocationInfo::getPointer() const
        {
            return ptr;
        }
        
        size_t AllocationInfo::getSize() const
        {
            return bytes;
        }

        const std::string AllocationInfo::getType() const
        {
            return demangle(type.c_str());
        }
    }
}
