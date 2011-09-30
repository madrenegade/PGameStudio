/*
 * File:   Allocator.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:06 PM
 */

#ifndef SCRIPTING_ALLOCATOR_H
#define	SCRIPTING_ALLOCATOR_H

#include "Utilities/Memory/MemoryManager.h"

namespace Scripting
{

    class Allocator
    {
    public:
        static Utilities::Memory::MemoryManager::Ptr memory;
        static Utilities::Memory::pool_id pool;

        static void* allocate(void* ud, void* ptr, size_t osize, size_t nsize);

    private:
        Allocator();
        ~Allocator();
    };
}


#endif	/* SCRIPTING_ALLOCATOR_H */

