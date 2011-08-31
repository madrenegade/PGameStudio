#ifndef UTILITIES_MEMORY_ALLOCATIONINFO_H
#define UTILITIES_MEMORY_ALLOCATIONINFO_H

#include <typeinfo>
#include <string>

namespace Utilities
{
    namespace Memory
    {
        class AllocationInfo
        {
        public:
            AllocationInfo();
            
            AllocationInfo(const void* ptr, size_t bytes, const std::type_info& type);
            
            const void* getPointer() const;
            size_t getSize() const;
            
            const std::string& getType() const;
            
        private:
            const void* ptr;
            
            size_t bytes;

            std::string type;
        };
    }
}

#endif // UTILITIES_MEMORY_ALLOCATIONINFO_H
