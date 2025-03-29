#pragma once
#include "Platform/MemoryManager.h"
#include <vector>
#include <list>
#include "Platform/RootObject.h"
#include "utl/VectorSizeDefs.h"

namespace Quazal {

    // the allocators are apparently Quazal::MemAllocator
    // pretty much copy pasted the StlNodeAlloc implementation nate did...
    // thank you nate lol
    template <class T>
    class MemAllocator {
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef const T &const_reference;

        template <class T2>
        struct rebind {
            typedef MemAllocator<T2> other;
        };

#ifdef VERSION_SZBE69_B8
        // Retail doesn't have constructor calls
        MemAllocator() {}
        MemAllocator(MemAllocator<T> const &) {}
        template <class T2>
        MemAllocator(const MemAllocator<T2> &) {}
#endif

        // ...but still has the destructor
        ~MemAllocator() {}

#ifdef VERSION_SZBE69
        // This is the only way to make allocator conversions
        // work in retail without using constructors
        template <class T2>
        operator MemAllocator<T2>() const {
            return MemAllocator<T2>();
        }
#endif

        template <class T2>
        MemAllocator<T> &operator=(const MemAllocator<T2> &right) {}

        template <class T2>
        bool operator==(const MemAllocator<T2> &) const {
            return true;
        }
        template <class T2>
        bool operator!=(const MemAllocator<T2> &) const {
            return false;
        }

        pointer address(reference value) const { return &value; }
        const_pointer address(const_reference value) const { return &value; }
        size_type max_size() const { return size_type(-1) / sizeof(T); }

        pointer allocate(const size_type count, const void *hint = nullptr) const {
#ifdef STL_NODE_ALLOC_DEBUG
            // A leftover from the earlier prototype versions of RB3;
            // bank 5/6 use type info for allocation tracing purposes
            typeid(pointer);
#endif
            return reinterpret_cast<pointer>(
                _MemOrPoolAllocSTL(count * sizeof(T), FastPool)
            );
        }

        void deallocate(pointer ptr, size_type count) const {
            MemoryManager::Free(
                MemoryManager::GetDefaultMemoryManager(),
                ptr,
                (MemoryManager::_InstructionType)7
            );
        }

        void construct(pointer ptr, const_reference value) const { new (ptr) T(value); }
        void destroy(pointer ptr) const { ptr->~T(); }
    };

    template <class T VECTOR_SIZE_DFLT_PARAM>
    class qVector : public std::vector<T VECTOR_SIZE_ARG, MemAllocator<T> > {
    public:
    };

    template <class T>
    class qList : public std::list<T, MemAllocator<T> >, public RootObject {
    public:
    };

}