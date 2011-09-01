#ifndef UTILITIES_MEMORY_ALLOCATIONINFO_H
#define UTILITIES_MEMORY_ALLOCATIONINFO_H

#include <typeinfo>
#include <string>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {
        class AllocationInfo
        {
        public:
            AllocationInfo();
            
            AllocationInfo(const_pointer ptr, size_t bytes, const std::type_info& type);
            
            const_pointer getPointer() const;
            size_t getSize() const;
            
            const std::string getType() const;
            
        private:
            const_pointer ptr;
            
            size_t bytes;

            std::string type;
        };
    }
}

#endif // UTILITIES_MEMORY_ALLOCATIONINFO_H
