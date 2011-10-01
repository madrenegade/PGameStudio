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

            AllocationInfo(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type);

            const char* getPool() const;
            const_byte_pointer getPointer() const;
            size_t getSize() const;

            std::string getType() const;

        private:
            const char* pool;
            const_byte_pointer ptr;

            size_t bytes;

            std::string type;
        };
    }
}

#endif // UTILITIES_MEMORY_ALLOCATIONINFO_H
