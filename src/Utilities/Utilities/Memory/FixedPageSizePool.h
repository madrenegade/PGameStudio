/* 
 * File:   FixedPageSizePool.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 4:29 PM
 */

#ifndef UTILITIES_MEMORY_FIXEDPAGESIZEPOOL_H
#define	UTILITIES_MEMORY_FIXEDPAGESIZEPOOL_H

#include "Utilities/Memory/Pool.h"

namespace Utilities
{
    namespace Memory
    {

        class FixedPageSizePool : public Pool
        {
        public:
            FixedPageSizePool(size_t totalSize, size_t pageSize);
            
            virtual pointer allocate(size_t bytes);
            
            virtual void deallocate(const_pointer ptr, size_t bytes);
            virtual void deallocateArray(const_pointer ptr, size_t bytes);
            
        private:
            const size_t pageSize;
            
            void assertPageSize() const;
            
            void assertPageSizeIsNotZero() const;
            void assertPageSizeIsMultipleOfPoolSize() const;
        };
    }
}
#endif	/* UTILITIES_MEMORY_FIXEDPAGESIZEPOOL_H */

