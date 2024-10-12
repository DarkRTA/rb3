#ifndef STL_STLALLOC_H
#define STL_STLALLOC_H

// File name known from bank 5/6

#include <cstddef>
#include <system/utl/MemMgr.h>

#ifdef STL_NODE_ALLOC_DEBUG
#include <typeinfo>
#endif

#ifdef STLPORT
// StlNodeAlloc exists in the STLport namespace
namespace STLPORT {
#endif

    template <class T>
    class StlNodeAlloc {
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
            typedef StlNodeAlloc<T2> other;
        };

#ifdef VERSION_SZBE69_B8
        // Retail doesn't have constructor calls
        StlNodeAlloc() {}
        StlNodeAlloc(StlNodeAlloc<T> const &) {}
        template <class T2>
        StlNodeAlloc(const StlNodeAlloc<T2> &) {}
#endif

        // ...but still has the destructor
        ~StlNodeAlloc() {}

#ifdef VERSION_SZBE69
        // This is the only way to make allocator conversions
        // work in retail without using constructors
        template <class T2>
        operator StlNodeAlloc<T2>() const {
            return StlNodeAlloc<T2>();
        }
#endif

        template <class T2>
        StlNodeAlloc<T> &operator=(const StlNodeAlloc<T2> &right) {}

        template <class T2>
        bool operator==(const StlNodeAlloc<T2> &) const {
            return true;
        }
        template <class T2>
        bool operator!=(const StlNodeAlloc<T2> &) const {
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
            _MemOrPoolFreeSTL(count * sizeof(T), FastPool, ptr);
        }

        void construct(pointer ptr, const_reference value) const { new (ptr) T(value); }
        void destroy(pointer ptr) const { ptr->~T(); }
    };

#ifdef STLPORT
}
#endif

#endif
