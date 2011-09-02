/* 
 * File:   PoolMock.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 12:55 PM
 */

#ifndef UTILITIES_MEMORY_POOLMOCK_H
#define	UTILITIES_MEMORY_POOLMOCK_H

#include "Utilities/Memory/Pool.h"

namespace Utilities
{
    namespace Memory
    {

        class PoolMock : public Pool
        {
        public:
            /**
             * Mock pool creates a 100 byte buffer
             */
            PoolMock();
            
            /**
             * always returns the beginning of the 100-byte buffer
             * @param bytes - has no effect
             * @return the beginning of the 100-byte buffer
             */
            virtual pointer allocate(size_t bytes);
            
            /**
             * does nothing
             * @param ptr
             * @param sizeOfOneObject
             * @param numObjects
             */
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);
            
            /**
             * always returns true
             * @param ptr
             * @return true
             */
            virtual bool contains(const_pointer ptr) const;
            
            /**
             *
             * @return the number of times allocate was called
             */
            unsigned int getAllocations() const;
            
            /**
             * 
             * @return the number of times deallocate was called
             */
            unsigned int getDeallocations() const;
            
        protected:
            virtual size_t getMemoryUsage() const;
            
        private:
            boost::scoped_array<char> data;
            
            unsigned int allocations;
            unsigned int deallocations;
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOLMOCK_H */

