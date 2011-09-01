/* 
 * File:   LargeObjectMemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:50 PM
 */

#include "Utilities/Memory/LargeObjectMemoryManager.h"
#include "LargeObjectMemoryManager.h"

namespace Utilities
{
    namespace Memory
    {
        LargeObjectMemoryManager::LargeObjectMemoryManager(size_t maxMemory)
        : AbstractMemoryManager(maxMemory)
        {
            
        }
        
        pointer LargeObjectMemoryManager::allocate(size_t n, char prealloc)
        {
            char* ptr = new char[n];
            
            setMemory(ptr, n, prealloc);
            
            return ptr;
        }
        
		void LargeObjectMemoryManager::deallocate(const_pointer ptr, size_t sizeOfOne, size_t n)
        {
            if(n == 0)
            {
                delete ptr;
            }
            else
            {
                delete[] ptr;
            }
        }
    }
}


