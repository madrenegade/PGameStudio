/*
 * File:   STLAllocator.h
 * Author: madrenegade
 *
 * Created on September 8, 2011, 12:04 PM
 */

#ifndef UTILITIES_MEMORY_STLALLOCATOR_H
#define	UTILITIES_MEMORY_STLALLOCATOR_H

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <stdexcept>

#include "Utilities/Memory/MemoryManager.h"

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;

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

            static MemoryManager* memory;
        };

        /**
         * An allocator template class for use in STL containers. Internally it uses
         * \ref Utilities::Memory::MemoryManager to do allocations and deallocations.
         */
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

            STLAllocator() throw ()
            {
                setMemoryManager();
            }

            STLAllocator(const STLAllocator& /*allocator*/) throw ()
            {
                setMemoryManager();
            }

            template <class U>
            STLAllocator(const STLAllocator<U>& /*allocator*/) throw ()
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

            pointer allocate(size_type n,
#ifdef GCC
                             STLAllocator<void>::const_pointer hint __attribute__((unused)) = 0
#endif
                            )
            {
                //DCHECK_NE(memory, nullptr);

#ifdef DEBUG
                return memory->rawAllocate<T > (n, StackTrace());
#else
                return memory->rawAllocate<T > (n);
#endif
            }

            void deallocate(pointer p, size_type n)
            {
                //DCHECK_NE(memory, nullptr);

                memory->rawDeallocate<T > (p, n);
            }

            size_type max_size() const throw ()
            {
                // TODO: return largest block
                return 128 * Byte;
            }

            void construct(pointer p, const_reference val = T())
            {
                new(p) T(val);
            }

            void destroy(pointer p)
            {
                p->~T();
            }

        private:
            static MemoryManager* memory;

            static void setMemoryManager()
            {
                memory = STLAllocator<void>::memory;
            }
        };

        template <class T>
        MemoryManager* STLAllocator<T>::memory;

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

