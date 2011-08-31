#include "Utilities/Memory/AllocationInfo.h"

namespace Utilities
{
    namespace Memory
    {
        AllocationInfo::AllocationInfo()
        {
            
        }
        
        AllocationInfo::AllocationInfo(const void* ptr, size_t bytes, const std::type_info& type)
        : ptr(ptr), bytes(bytes), type(type.name())
        {
            
        }
        
        const void* AllocationInfo::getPointer() const
        {
            return ptr;
        }
        
        size_t AllocationInfo::getSize() const
        {
            return bytes;
        }

        const std::string& AllocationInfo::getType() const
        {
            return type;
        }
    }
}
