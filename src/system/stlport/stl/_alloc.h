/*
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_ALLOC_H
#define _STLP_INTERNAL_ALLOC_H

#ifndef _STLP_INTERNAL_CSTDDEF
#  include <stl/_cstddef.h>
#endif

#if !defined (_STLP_DEBUG_H) && (defined(_STLP_DEBUG) || defined(_STLP_ASSERTIONS) || defined(_STLP_DEBUG_ALLOC))
#  include <stl/debug/_debug.h>
#endif

#ifndef _STLP_INTERNAL_CSTDLIB
#  include <stl/_cstdlib.h>
#endif

#ifndef _STLP_INTERNAL_CSTRING
#  include <stl/_cstring.h>
#endif

#ifndef _STLP_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
#endif

#ifndef __THROW_BAD_ALLOC
#  if !defined(_STLP_USE_EXCEPTIONS)
#    ifndef _STLP_INTERNAL_CSTDIO
#      include <stl/_cstdio.h>
#    endif
#    define __THROW_BAD_ALLOC puts("out of memory\n"); exit(1)
#  else
#    define __THROW_BAD_ALLOC throw _STLP_STD::bad_alloc()
#  endif
#endif

#ifndef _STLP_INTERNAL_NEW_HEADER
#  include <stl/_new.h>
#endif

#ifndef _STLP_INTERNAL_CONSTRUCT_H
#  include <stl/_construct.h>
#endif

#if !defined (__ALLOC)
#  define __ALLOC __sgi_alloc
#endif

#include "utl/MemMgr.h"

namespace _STLP_STD {

// Malloc-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.

#if !defined (_STLP_USE_NO_IOSTREAMS)
typedef void (* __oom_handler_type)();
#endif

class __malloc_alloc {
public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;

  static void* allocate(size_t& __n)
#if !defined (_STLP_USE_NO_IOSTREAMS)
  ;
#else
  {
    void *__result = malloc(__n);
#  if defined (_STLP_MALLOC_USABLE_SIZE)
    if (__result != 0) {
      __n = _STLP_MALLOC_USABLE_SIZE(__result);
    }
#  endif
    if (__result == 0) {
      __THROW_BAD_ALLOC;
    }
    return __result;
  }
#endif

  static void deallocate(void* __p, size_t /* __n */) { free((char*)__p); }
#if !defined (_STLP_USE_NO_IOSTREAMS)
  static __oom_handler_type set_malloc_handler(__oom_handler_type __f);
#endif
};

// New-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.
class __new_alloc {
public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;

  static void* allocate(size_t __n) { return __stl_new(__n); }
  static void deallocate(void* __p, size_t) { __stl_delete(__p); }
};


// Allocator adaptor to check size arguments for debugging.
// Reports errors using assert.  Checking can be disabled with
// NDEBUG, but it's far better to just use the underlying allocator
// instead when no checking is desired.
// There is some evidence that this can confuse Purify.
// This adaptor can only be applied to raw allocators

template <class _Alloc>
class __debug_alloc : public _Alloc {
public:
  typedef _Alloc __allocator_type;
  typedef typename _Alloc::value_type value_type;
private:
  struct __alloc_header {
    size_t __magic: 16;
    size_t __type_size:16;
    unsigned int _M_size:32;
  }; // that is 8 bytes for sure
  _STLP_STATIC_ASSERT(sizeof(__alloc_header) == 8);

  // Sunpro CC has bug on enums, so extra_before/after set explicitly
  enum { __pad = 8, __magic = 0xdeba, __deleted_magic = 0xdebd,
         __shred_byte = _STLP_SHRED_BYTE };

  enum { __extra_before = 16, __extra_after = 8 };
  // Size of space used to store size.  Note
  // that this must be large enough to preserve
  // alignment.
  static size_t __extra_before_chunk() {
    return (long)__extra_before / sizeof(value_type) +
      (size_t)((long)__extra_before % sizeof(value_type) > 0);
  }
  static size_t __extra_after_chunk() {
    return (long)__extra_after / sizeof(value_type) +
      (size_t)((long)__extra_after % sizeof(value_type) > 0);
  }
public:

  __debug_alloc() {}
  ~__debug_alloc() {}
  static void* allocate(size_t);
  static void deallocate(void *, size_t);
};

enum {_ALIGN = 8, _ALIGN_SHIFT = 3, _MAX_BYTES = 128};

#if !defined (_STLP_USE_NO_IOSTREAMS)
// Default node allocator.
// With a reasonable compiler, this should be roughly as fast as the
// original STL class-specific allocators, but with less fragmentation.
class __node_alloc {
  static void * _M_allocate(size_t& __n);
  /* __p may not be 0 */
  static void _M_deallocate(void *__p, size_t __n);

public:
  // this one is needed for proper simple_alloc wrapping
  typedef char value_type;

  /* __n must be > 0      */
  static void* allocate(size_t& __n)
  { return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
  /* __p may not be 0 */
  static void deallocate(void *__p, size_t __n)
  { if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
};

#endif /* _STLP_USE_NO_IOSTREAMS */

// Decomp hack: converts an allocator from one type to another
#ifdef VERSION_SZBE69
   // Note: does not preserve state! This is fine since StlNodeAlloc has no state,
   // and no other allocators are used as far as we've seen
#  define _STLP_CONVERT_ALLOCATOR(__a, _Alloc, _Tp) _Alloc_traits<_Tp, _Alloc>::allocator_type()
#else
#  define _STLP_CONVERT_ALLOCATOR(__a, _Alloc, _Tp) __a
#endif

// Another allocator adaptor: _Alloc_traits.  This serves two
// purposes.  First, make it possible to write containers that can use
// either SGI-style allocators or standard-conforming allocator.

// The fully general version.
template <class _Tp, class _Allocator>
struct _Alloc_traits {
  typedef _Allocator _Orig;
  typedef typename _Allocator::template rebind<_Tp> _Rebind_type;
  typedef typename _Rebind_type::other  allocator_type;
  static allocator_type create_allocator(const _Orig& __a)
  { return _STLP_CONVERT_ALLOCATOR(__a, _Orig, _Tp); }
};

#if defined (_STLP_USE_PERTHREAD_ALLOC)

}

// include additional header here
#  include <stl/_pthread_alloc.h>

namespace _STLP_STD {

#  if defined (_STLP_DEBUG_ALLOC)
typedef __debug_alloc<__pthread_alloc> __sgi_alloc;
#  else
typedef __pthread_alloc __sgi_alloc;
#  endif /* _STLP_DEBUG_ALLOC */

typedef __pthread_alloc __single_client_alloc;
typedef __pthread_alloc __multithreaded_alloc;

#else /* _STLP_USE_PERTHREAD_ALLOC */

#  if defined (_STLP_USE_NEWALLOC)

#    if defined (_STLP_DEBUG_ALLOC)
typedef __debug_alloc<__new_alloc> __sgi_alloc;
#    else
typedef __new_alloc __sgi_alloc;
#    endif /* _STLP_DEBUG_ALLOC */

typedef __new_alloc __single_client_alloc;
typedef __new_alloc __multithreaded_alloc;

#  elif defined (_STLP_USE_MALLOC)

#    if defined (_STLP_DEBUG_ALLOC)
typedef __debug_alloc<__malloc_alloc> __sgi_alloc;
#    else
typedef __malloc_alloc __sgi_alloc;
#    endif /* _STLP_DEBUG_ALLOC */

typedef __malloc_alloc __single_client_alloc;
typedef __malloc_alloc __multithreaded_alloc;

#  else

#    if defined (_STLP_DEBUG_ALLOC)
typedef __debug_alloc<__node_alloc> __sgi_alloc;
#    else
typedef __node_alloc __sgi_alloc;
#    endif

typedef __node_alloc __single_client_alloc;
typedef __node_alloc __multithreaded_alloc;

#  endif /* _STLP_USE_NEWALLOC */
#endif /* _STLP_USE_PERTHREAD_ALLOC */

// This implements allocators as specified in the C++ standard.
//
// Note that standard-conforming allocators use many language features
// that are not yet widely implemented.  In particular, they rely on
// member templates, partial specialization, partial ordering of function
// templates, the typename keyword, and the use of the template keyword
// to refer to a template member of a dependent type.

/*
template <class _Tp>
struct _AllocatorAux {
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;

  pointer address(reference __x) const {return &__x;}
  const_pointer address(const_reference __x) const { return &__x; }
};

template <class _Tp>
struct _AllocatorAux<const _Tp> {
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;

  const_pointer address(const_reference __x) const { return &__x; }
};
*/

template <class _Tp>
class allocator //: public _AllocatorAux<_Tp>
/* A small helper struct to recognize STLport allocator implementation
 * from any user specialization one.
 */
                : public __stlport_class<allocator<_Tp> > {
public:
  typedef _Tp        value_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };

  allocator() _STLP_NOTHROW {}
  template <class _Tp1> allocator(const allocator<_Tp1>&) _STLP_NOTHROW {}
  allocator(const allocator<_Tp>&) _STLP_NOTHROW {}
  allocator(__move_source<allocator<_Tp> > src) _STLP_NOTHROW {}
  ~allocator() _STLP_NOTHROW {}
  pointer address(reference __x) const {return &__x;}
  const_pointer address(const_reference __x) const { return &__x; }
  // __n is permitted to be 0.  The C++ standard says nothing about what the return value is when __n == 0.
  _Tp* allocate(size_type __n, const void* = 0) {
    if (__n > max_size()) {
      __THROW_BAD_ALLOC;
    }
    if (__n != 0) {
      size_type __buf_size = __n * sizeof(value_type);
      _Tp* __ret = reinterpret_cast<_Tp*>(__sgi_alloc::allocate(__buf_size));
#if defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_DEBUG_ALLOC)
      if (__ret != 0) {
        memset((char*)__ret, _STLP_SHRED_BYTE, __buf_size);
      }
#endif
      return __ret;
    }
    else
      return 0;
  }
  // __p is permitted to be a null pointer, only if n==0.
  void deallocate(pointer __p, size_type __n) {
    _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) {
#if defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_DEBUG_ALLOC)
      memset((char*)__p, _STLP_SHRED_BYTE, __n * sizeof(value_type));
#endif
      __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
    }
  }
  // backwards compatibility
  void deallocate(pointer __p) const {  if (__p != 0) __sgi_alloc::deallocate((void*)__p, sizeof(value_type)); }
  size_type max_size() const _STLP_NOTHROW  { return size_t(-1) / sizeof(value_type); }
  void construct(pointer __p, const_reference __val) { _STLP_STD::_Copy_Construct(__p, __val); }
  void destroy(pointer __p) { _STLP_STD::_Destroy(__p); }

#if defined (_STLP_NO_EXTENSIONS)
  /* STLport extension giving rounded size of an allocated memory buffer
   * This method do not have to be part of a user defined allocator implementation
   * and won't even be called if such a function was granted.
   */
protected:
#endif
  _Tp* allocate(size_type __n, size_type& __allocated_n) {
    if (__n > max_size()) {
      __THROW_BAD_ALLOC;
    }

    if (__n != 0) {
      size_type __buf_size = __n * sizeof(value_type);
      _Tp* __ret = reinterpret_cast<_Tp*>(__sgi_alloc::allocate(__buf_size));
#if defined (_STLP_DEBUG_UNINITIALIZED) && !defined (_STLP_DEBUG_ALLOC)
      if (__ret != 0) {
        memset((char*)__ret, _STLP_SHRED_BYTE, __buf_size);
      }
#endif
      __allocated_n = __buf_size / sizeof(value_type);
      return __ret;
    }
    else
      return 0;
  }
};

template<>
class allocator<void> {
public:
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
};

template <class _T1, class _T2> inline bool  operator==(const allocator<_T1>&, const allocator<_T2>&) _STLP_NOTHROW { return true; }
template <class _T1, class _T2> inline bool  operator!=(const allocator<_T1>&, const allocator<_T2>&) _STLP_NOTHROW { return false; }

// Custom allocator type present in RB3.
// Allocates from either the heap or a pool depending on the allocation size.
template <class _Tp> class StlNodeAlloc {
public:
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp        value_type;

  template <class _Tp1> struct rebind {
    typedef StlNodeAlloc<_Tp1> other;
  };

#ifdef VERSION_SZBE69_B8
  StlNodeAlloc() _STLP_NOTHROW {}
  StlNodeAlloc(StlNodeAlloc<_Tp> const &) _STLP_NOTHROW {}
  template <class _Tp1>
  StlNodeAlloc(const StlNodeAlloc<_Tp1>&) _STLP_NOTHROW {}
#endif

  ~StlNodeAlloc() _STLP_NOTHROW {}

  template <class _Tp1>
  bool operator==(const StlNodeAlloc<_Tp1>&) _STLP_NOTHROW { return true; }
  template <class _Tp1>
  bool operator!=(const StlNodeAlloc<_Tp1>&) _STLP_NOTHROW { return false; }

  size_type max_size() const _STLP_NOTHROW  {
    return size_type(-1) / sizeof(value_type);
  }

  value_type *allocate(const size_type count, const void* ptr = nullptr) const {
    return reinterpret_cast<value_type *>(
      _MemOrPoolAllocSTL(count * sizeof(value_type), FastPool)
    );
  }

  void deallocate(value_type *ptr, const size_type count) const {
    _MemOrPoolFreeSTL(count * sizeof(value_type), FastPool, ptr);
  }
};

}

namespace _STLP_PRIV {

template <class _Tp>
struct __alloc_type_traits {
  typedef typename _IsSTLportClass<allocator<_Tp> >::_Ret _STLportAlloc;

  //The default allocator implementation which is recognize thanks to the
  //__stlport_class inheritance is a stateless object so:
  typedef _STLportAlloc has_trivial_default_constructor;
  typedef _STLportAlloc has_trivial_copy_constructor;
  typedef _STLportAlloc has_trivial_assignment_operator;
  typedef _STLportAlloc has_trivial_destructor;
  typedef _STLportAlloc is_POD_type;
};

}

namespace _STLP_STD {

template <class _Tp>
struct __type_traits<allocator<_Tp> > : _STLP_PRIV::__alloc_type_traits<_Tp> {};

template <class _Tp, class _Alloc>
inline typename _Alloc_traits<_Tp, _Alloc>::allocator_type
__stl_alloc_create(const _Alloc& __a, const _Tp*) {
  typedef typename _Alloc::template rebind<_Tp>::other _Rebound_type;
  return _Rebound_type(__a);
}

}

namespace _STLP_PRIV {

// inheritance is being used for EBO optimization
template <class _Value, class _Tp, class _MaybeReboundAlloc>
class _STLP_alloc_proxy : public _MaybeReboundAlloc {
private:
  typedef _MaybeReboundAlloc _Base;
  typedef typename _Base::size_type size_type;
  typedef _STLP_alloc_proxy<_Value, _Tp, _MaybeReboundAlloc> _Self;
public:
  _Value _M_data;

  _STLP_alloc_proxy (const _MaybeReboundAlloc& __a, _Value __p) :
    _MaybeReboundAlloc(__a), _M_data(__p) {}

  _STLP_alloc_proxy (__move_source<_Self> src) :
    _MaybeReboundAlloc(_STLP_PRIV::_AsMoveSource<_Base>(src.get())),
    _M_data(_STLP_PRIV::_AsMoveSource<_Value>(src.get()._M_data)) {}

private:
  /* Following are helper methods to detect stateless allocators and avoid
   * swap in this case. For some compilers (VC6) it is a workaround for a
   * compiler bug in the Empty Base class Optimization feature, for others
   * it is a small optimization or nothing if no EBO. */
  void _M_swap_alloc(_Self&, const __true_type& /*_IsStateless*/)
  {}

  void _M_swap_alloc(_Self& __x, const __false_type& /*_IsStateless*/) {
    _MaybeReboundAlloc &__base_this = *this;
    _MaybeReboundAlloc &__base_x = __x;
    _STLP_STD::swap(__base_this, __base_x);
  }

public:
  void _M_swap_alloc(_Self& __x) {
    typedef typename _IsStateless<_MaybeReboundAlloc>::_Ret _StatelessAlloc;
    _M_swap_alloc(__x, _StatelessAlloc());
  }

  /* We need to define the following swap implementation for allocator with state
   * as those allocators might have implement a special swap function to correctly
   * move datas from an instance to the oher, _STLP_alloc_proxy should not break
   * this mecanism. */
  void swap(_Self& __x) {
    _M_swap_alloc(__x);
    _STLP_STD::swap(_M_data, __x._M_data);
  }

// These overloads cause problems with the signature that StlNodeAlloc::allocate has,
// and also mismatch in retail with the assumption that there is no inlining happening with these
// Leaving these as commented-out in case they're needed in the future
//   _Tp* allocate(size_type __n, size_type& __allocated_n) {
//     typedef typename _IsSTLportClass<_MaybeReboundAlloc>::_Ret _STLportAlloc;
//     return allocate(__n, __allocated_n, _STLportAlloc());
//   }
//   _Tp* allocate(size_type __n)
//   { return _Base::allocate(__n); }

// private:
//   _Tp* allocate(size_type __n, size_type& __allocated_n, const __true_type& /*STLport allocator*/)
//   { return _Base::allocate(__n, __allocated_n); }
//   _Tp* allocate(size_type __n, size_type& __allocated_n, const __false_type& /*STLport allocator*/)
//   { __allocated_n = __n; return allocate(__n); }
};

}

#if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION) && !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_alloc.c>
#endif

#endif /* _STLP_INTERNAL_ALLOC_H */

// Local Variables:
// mode:C++
// End:
