/* 
 * File:   STLAllocator.h
 * Author: madrenegade
 *
 * Created on September 8, 2011, 12:04 PM
 */

#ifndef UTILITIES_MEMORY_STLALLOCATOR_H
#define	UTILITIES_MEMORY_STLALLOCATOR_H

#include "Utilities/Memory/MemoryManager.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace Utilities
{
    namespace Memory
    {
        template <class T> class STLAllocator;

        // specialize for void:

        template <>
        class STLAllocator<void>
        {
        public:
            typedef void* pointer;
            typedef const void* const_pointer;
            // reference to void members are impossible.
            typedef void value_type;

            template <class U> struct rebind
            {
                typedef STLAllocator<U>
                    other;
            };
            
            static MemoryManager::Ptr memory;
        };

        template<class T>
        class STLAllocator
        {
        public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef T* pointer;
            typedef const T* const_pointer;
            typedef T& reference;
            typedef const T& const_reference;
            typedef T value_type;

            template <class U>
            struct rebind
            {
                typedef STLAllocator<U> other;
            };

            STLAllocator<T>() throw ()
            {
                setMemoryManager();
            }

            STLAllocator<T>(const STLAllocator& allocator) throw ()
            {
                setMemoryManager();
            }

            template <class U>
            STLAllocator(const STLAllocator<U>& allocator) throw ()
            {
                setMemoryManager();
            }

            ~STLAllocator() throw ()
            {
            }

            pointer address(reference x) const
            {
                throw std::runtime_error("address not implemented");
            }

            const_pointer address(const_reference x) const
            {
                throw std::runtime_error("address not implemented");
            }

            pointer allocate(size_type n, STLAllocator<void>::const_pointer hint = 0)
            {
                DCHECK(memory.get() != 0);
                
                return memory->stl_allocate<T > (n, StackTrace());
            }

            void deallocate(pointer p, size_type n)
            {
                DCHECK(memory.get() != 0);
                
                memory->deallocate<T > (p, n);
            }

            size_type max_size() const throw ()
            {
                return 0;
            }

            void construct(pointer p, const_reference val)
            {
                new(p) T(val);
            }

            void destroy(pointer p)
            {
            }

        private:
            static MemoryManager::Ptr memory;
            
            static void setMemoryManager()
            {
                memory = STLAllocator<void>::memory;
            }
        };

        MemoryManager::Ptr STLAllocator<void>::memory;
        template <class T> MemoryManager::Ptr STLAllocator<T>::memory;

        template <class T1, class T2>
        bool operator==(const STLAllocator<T1>&, const STLAllocator<T2>&) throw ()
        {
            return typeid (T1) == typeid (T2);
        }

        template <class T1, class T2>
        bool operator!=(const STLAllocator<T1>&, const STLAllocator<T2>&) throw ()
        {
            return typeid (T1) != typeid (T2);
        }
    }

}


#endif	/* UTILITIES_MEMORY_STLALLOCATOR_H */

