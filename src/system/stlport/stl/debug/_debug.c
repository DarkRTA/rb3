/*
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

#ifndef _STLP_DEBUG_C
#define _STLP_DEBUG_C

#if defined (_STLP_DEBUG)
#if defined (_STLP_THREADS)
#  define _STLP_ACQUIRE_LOCK(_Lock) _Lock._M_acquire_lock();
#  define _STLP_RELEASE_LOCK(_Lock) _Lock._M_release_lock();
#else
#  define _STLP_ACQUIRE_LOCK(_Lock)
#  define _STLP_RELEASE_LOCK(_Lock)
#endif /* _STLP_THREADS */

namespace _STLP_PRIV {

//==========================================================
//  global non-inline functions
//==========================================================
// [ i1, i2)
template <class _Iterator>
inline bool
__in_range_aux(const _Iterator& __it, const _Iterator& __first,
               const _Iterator& __last, const random_access_iterator_tag &) {
    return ( __it >= __first &&
             __it < __last);
}

template <class _Iterator1, class _Iterator>
inline bool  __in_range_aux(const _Iterator1& __it, const _Iterator& __first,
                                       const _Iterator& __last, const forward_iterator_tag &) {
  _Iterator1 __i(__first);
  for (;  __i != __last && __i != __it; ++__i);
  return (__i != __last);
}

template <class _Iterator>
bool __check_range_aux(const _Iterator& __first, const _Iterator& __last,
                                  const __false_type& /*_IsIntegral*/) {
  _STLP_VERBOSE_RETURN(__valid_range(__first,__last), _StlMsg_INVALID_RANGE )
  return true;
}

template <class _Integral>
bool __check_range_aux(_Integral /*__first*/, _Integral /*__last*/,
                                  const __true_type& /*_IsIntegral*/)
{ return true; }

template <class _Iterator>
bool  __check_range(const _Iterator& __first, const _Iterator& __last) {
  typedef typename _IsIntegral<_Iterator>::_Ret _Integral;
  return __check_range_aux(__first, __last, _Integral());
}

template <class _Iterator>
bool  __check_range(const _Iterator& __it,
                               const _Iterator& __start, const _Iterator& __finish) {
  _STLP_VERBOSE_RETURN(__in_range(__it, __start, __finish),
                       _StlMsg_NOT_IN_RANGE_1)
  return true;
}

template <class _Iterator>
bool  __check_range(const _Iterator& __first, const _Iterator& __last,
                               const _Iterator& __start, const _Iterator& __finish) {
  _STLP_VERBOSE_RETURN(__in_range(__first, __last, __start, __finish),
                       _StlMsg_NOT_IN_RANGE_2)
  return true;
}

template <class _Tp>
bool __check_ptr_range(const _Tp* __first, const _Tp* __last) {
  _STLP_VERBOSE_RETURN((__first != 0 || __last == 0), _StlMsg_INVALID_ARGUMENT)
  _STLP_VERBOSE_RETURN(__valid_range(__first, __last, random_access_iterator_tag()),
                       _StlMsg_INVALID_RANGE)
  return true;
}

//===============================================================
template <class _Iterator>
void __invalidate_range(const __owned_list* __base,
                                   const _Iterator& __first,
                                   const _Iterator& __last) {
  typedef __owned_link _L_type;
  _STLP_ACQUIRE_LOCK(__base->_M_lock)
  _L_type* __prev = const_cast<_L_type*>(&__base->_M_node);
  _L_type* __pos = __prev->_M_next;

  while (__pos != 0) {
    if (!(&__first == static_cast<_Iterator*>(__pos) || &__last == static_cast<_Iterator*>(__pos)) &&
        __in_range_aux(static_cast<_Iterator*>(__pos)->_M_iterator,
                       __first._M_iterator, __last._M_iterator,
                       _STLP_ITERATOR_CATEGORY(__first, _Iterator))) {
      __pos->_M_owner = 0;
      __prev->_M_next = __pos->_M_next;
    }
    else {
      __prev = __pos;
    }
    __pos = __prev->_M_next;
  }
  _STLP_RELEASE_LOCK(__base->_M_lock)
}

template <class _Iterator>
void __invalidate_iterator(const __owned_list* __base,
                                      const _Iterator& __it) {
  typedef __owned_link   _L_type;
  _STLP_ACQUIRE_LOCK(__base->_M_lock)
  _L_type* __prev = const_cast<_L_type*>(&__base->_M_node);
  _L_type* __pos = __prev->_M_next;
  while (__pos != 0) {
    // this requires safe iterators to be derived from __owned_link
    if ((__pos != static_cast<const _L_type*>(&__it)) &&
        (static_cast<_Iterator*>(__pos)->_M_iterator == __it._M_iterator)) {
      __pos->_M_owner = 0;
      __prev->_M_next = __pos->_M_next;
    }
    else {
      __prev = __pos;
    }
    __pos = __prev->_M_next;
  }
  _STLP_RELEASE_LOCK(__base->_M_lock)
}

template <class _Iterator>
void  __change_range_owner(const _Iterator& __first,
                                      const _Iterator& __last,
                                      const __owned_list* __dst) {
  if (__first._Owner() == __dst)
    return;

  typedef __owned_link _L_type;
  // Check __stl_debug_engine<_Dummy>::_Swap_owners comments to see why there is no lock here
  //_STLP_ACQUIRE_LOCK(__base->_M_lock)
  __owned_list *__base = const_cast<__owned_list*>(__first._Owner());
  _L_type* __src_prev = &__base->_M_node;
  _L_type* __pos = __src_prev->_M_next;
  _L_type* __dst_prev = const_cast<_L_type*>(&__dst->_M_node);

  while (__pos != 0) {
    if (!(&__first == static_cast<_Iterator*>(__pos) || &__last == static_cast<_Iterator*>(__pos)) &&
        __in_range_aux(static_cast<_Iterator*>(__pos)->_M_iterator,
                       __first._M_iterator, __last._M_iterator,
                       _STLP_ITERATOR_CATEGORY(__first, _Iterator))) {
      __pos->_M_owner = const_cast<__owned_list*>(__dst);
      //remove __pos from __base:
      __src_prev->_M_next = __pos->_M_next;
      //add __pos to __dst:
      __pos->_M_next = __dst_prev->_M_next;
      __dst_prev->_M_next = __pos;
    }
    else {
      __src_prev = __pos;
    }
    __pos = __src_prev->_M_next;
  }
  //_STLP_RELEASE_LOCK(__base->_M_lock)
}

template <class _Iterator>
void __change_ite_owner(const _Iterator& __it,
                                   const __owned_list* __dst) {
  if (__it._Owner() == __dst)
    return;

  typedef __owned_link _L_type;
  // Check __stl_debug_engine<_Dummy>::_Swap_owners comments to see why there is no lock here
  //_STLP_ACQUIRE_LOCK(__base->_M_lock)
  __owned_list *__base = const_cast<__owned_list*>(__it._Owner());
  _L_type* __prev = &__base->_M_node;
  _L_type* __pos = __prev->_M_next;
  _L_type* __dst_prev = const_cast<_L_type*>(&__dst->_M_node);

  while (__pos != 0) {
    // this requires safe iterators to be derived from __owned_link
    if ((__pos != static_cast<const _L_type*>(&__it)) &&
        (static_cast<_Iterator*>(__pos)->_M_iterator == __it._M_iterator)) {
      __pos->_M_owner = const_cast<__owned_list*>(__dst);
      //remove __pos from __base:
      __prev->_M_next = __pos->_M_next;
      //add __pos to __dst:
      __pos->_M_next = __dst_prev->_M_next;
      __dst_prev->_M_next = __pos;
    }
    else {
      __prev = __pos;
    }
    __pos = __prev->_M_next;
  }
  //_STLP_RELEASE_LOCK(__base->_M_lock)
}

}

#endif /* _STLP_DEBUG */

#if defined (_STLP_EXPOSE_GLOBALS_IMPLEMENTATION)

#  ifndef _STLP_INTERNAL_CSTDLIB
#    include <stl/_cstdlib.h>
#  endif

//==========================================================
// .c section
//  owned_list non-inline methods and global functions
//==========================================================

#  if defined (_STLP_ASSERTIONS)

namespace _STLP_PRIV {

template <class _Dummy>
const char* __stl_debug_engine<_Dummy>::_Message_table[_StlMsg_MAX] = {
  "\n%s(%d): STL error: %s\n",
  "%s(%d): STL assertion failure : %s\n" _STLP_ASSERT_MSG_TRAILER,
  "\n%s(%d): STL error : %s\n%s(%d): STL assertion failure:     %s \n" _STLP_ASSERT_MSG_TRAILER,
  "Invalid argument to operation (see operation documentation)",
  "Taking an iterator out of destroyed (or otherwise corrupted) container",
  "Trying to extract an object out from empty container",
  "Past-the-end iterator could not be erased",
  "Index out of bounds",
  "Container doesn't own the iterator",
  "Container is owner of the iterator, but should not",
  "Uninitialized or invalidated (by mutating operation) iterator used",
  "Uninitialized or invalidated (by mutating operation) lefthand iterator in expression",
  "Uninitialized or invalidated (by mutating operation) righthand iterator in expression",
  "Iterators used in expression are from different owners",
  "Iterator could not be dereferenced (past-the-end ?)",
  "Range [first,last) is invalid",
  "Iterator is not in range [first,last)",
  "Range [first,last) is not in range [start,finish)",
  "The advance would produce invalid iterator",
  "Iterator is singular (advanced beyond the bounds ?)",
  "Invalid strict weak ordering predicate, if pred(a, b) then we should have !pred(b, a)",
  "Invalid equivalent predicate, if pred(a, b) then we should have pred(b, a)",
  "Memory block deallocated twice",
  "Deallocating a block that was never allocated",
  "Deallocating a memory block allocated for another type",
  "Size of block passed to deallocate() doesn't match block size",
  "Pointer underrun - safety margin at front of memory block overwritten",
  "Pointer overrrun - safety margin at back of memory block overwritten",
  "Attempt to dereference null pointer returned by auto_ptr::get()",
  "Memory allocation function returned a wrongly align memory block",
  "Unknown problem"
};

}

// abort()
#  ifndef _STLP_INTERNAL_CSTDLIB
#    include <stl/_cstdlib.h>
#  endif

#  if !defined (_STLP_DEBUG_MESSAGE)
#    ifndef _STLP_INTERNAL_CSTDARG
#      include <stl/_cstdarg.h>
#    endif
#    ifndef _STLP_INTERNAL_CSTDIO
#      include <stl/_cstdio.h>
#    endif
#    if defined (_STLP_DEBUG_MODE_THROWS) && !defined (_STLP_RANGE_ERRORS_H)
#      include <stl/_range_errors.h>
#    endif

namespace _STLP_PRIV {

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Message(const char * __format_str, ...) {
  _STLP_VENDOR_STD::va_list __args;
  va_start( __args, __format_str );

#      if defined (_STLP_DEBUG_MODE_THROWS)
  char __buffer[4096];

#        if defined (_STLP_USE_SAFE_STRING_FUNCTIONS)
  vsnprintf_s(__buffer, _STLP_ARRAY_SIZE(__buffer), _TRUNCATE, __format_str, __args);
#        else
  vsprintf(__buffer, __format_str, __args);
#        endif
#      endif

#      ifdef _STLP_DEBUG_MESSAGE_POST
  _STLP_DEBUG_MESSAGE_POST
#      endif

  va_end(__args);

#      if defined (_STLP_DEBUG_MODE_THROWS)
  __stl_throw_runtime_error(__buffer);
#      endif
}

}

#    else
namespace _STLP_PRIV {
template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Message(const char * __format_str, ...)
{}
}
#    endif /* _STLP_DEBUG_MESSAGE */

namespace _STLP_PRIV {

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_IndexedError(int __error_ind, const char* __f, int __l) {
  __stl_debug_message(_Message_table[_StlFormat_ERROR_RETURN],
                      __f, __l, _Message_table[__error_ind]);
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_VerboseAssert(const char* __expr, int __error_ind, const char* __f, int __l) {
  __stl_debug_message(_Message_table[_StlFormat_VERBOSE_ASSERTION_FAILURE],
                      __f, __l, _Message_table[__error_ind], __f, __l, __expr);
  __stl_debug_terminate();
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Assert(const char* __expr, const char* __f, int __l) {
  __stl_debug_message(_Message_table[_StlFormat_ASSERTION_FAILURE],__f, __l, __expr);
  __stl_debug_terminate();
}

// if exceptions are present, sends unique exception
// if not, calls abort() to terminate
template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Terminate()
{ abort(); }

}

#  endif /* _STLP_ASSERTIONS */

#  if defined (_STLP_DEBUG)

namespace _STLP_PRIV {

//==========================================================
//  owned_list non-inline methods
//==========================================================

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Invalidate_all(__owned_list* __l) {
  _STLP_ACQUIRE_LOCK(__l->_M_lock);
  _Stamp_all(__l, 0);
  __l->_M_node._M_next =0;
  _STLP_RELEASE_LOCK(__l->_M_lock);
}

// boris : this is unasafe routine; should be used from within critical section only !
template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Stamp_all(__owned_list* __l, __owned_list* __o) {
  // crucial
  if (__l->_M_node._M_owner) {
    for (__owned_link*  __pos = (__owned_link*)__l->_M_node._M_next;
      __pos != 0; __pos = (__owned_link*)__pos->_M_next) {
      _STLP_ASSERT(__pos->_Owner()== __l)
      __pos->_M_owner=__o;
    }
  }
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Verify(const __owned_list* __l) {
  _STLP_ACQUIRE_LOCK(__l->_M_lock);
  if (__l) {
    _STLP_ASSERT(__l->_M_node._Owner() != 0)
    for (__owned_link* __pos = (__owned_link*)__l->_M_node._M_next;
         __pos != 0; __pos = (__owned_link*)__pos->_M_next) {
      _STLP_ASSERT(__pos->_Owner()== __l)
    }
  }
  _STLP_RELEASE_LOCK(__l->_M_lock);
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Swap_owners(__owned_list& __x, __owned_list& __y) {
  /*
   *  according to the standard : --no swap() function invalidates any references,
   *  pointers,  or  iterators referring to the elements of the containers being swapped.
   */

  __owned_link* __tmp;

  /*
   * boris : there is a deadlock potential situation here if we lock two containers sequentially.
   * As user is supposed to provide its own synchronization around swap() ( it is unsafe to do any container/iterator access
   * in parallel with swap()), we just do not use any locking at all -- that behaviour is closer to non-debug version
   */

  __tmp = __x._M_node._M_next;

  _Stamp_all(&__x, &__y);
  _Stamp_all(&__y, &__x);

  __x._M_node._M_next = __y._M_node._M_next;
  __y._M_node._M_next = __tmp;
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_Set_owner(__owned_list& __src, __owned_list& __dst) {
  if (&__src == &__dst)
    return;

  // Check __stl_debug_engine<_Dummy>::_Swap_owners comments to see why there is no lock here
  typedef __owned_link _L_type;
  _L_type* __prev = &__src._M_node;
  _L_type* __pos = __prev->_M_next;

  while (__pos != 0) {
    __pos->_M_owner = &__dst;
    __prev = __pos;
    __pos = __prev->_M_next;
  }
  __prev->_M_next = __dst._M_node._M_next;
  __dst._M_node._M_next = __src._M_node._M_next;
  __src._M_node._M_next = 0;
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_M_detach(__owned_list* __l, __owned_link* __c_node) {
  if (__l  != 0) {

    _STLP_VERBOSE_ASSERT(__l->_Owner()!=0, _StlMsg_INVALID_CONTAINER)

    _STLP_ACQUIRE_LOCK(__l->_M_lock)
      // boris : re-test the condition in case someone else already deleted us
      if(__c_node->_M_owner != 0) {
        __owned_link* __prev, *__next;

        for (__prev = &__l->_M_node; (__next = __prev->_M_next) != __c_node;
             __prev = __next) {
          _STLP_ASSERT(__next && __next->_Owner() == __l)
            }

        __prev->_M_next = __c_node->_M_next;
        __c_node->_M_owner=0;
      }
    _STLP_RELEASE_LOCK(__l->_M_lock)
  }
}

template <class _Dummy>
void
__stl_debug_engine<_Dummy>::_M_attach(__owned_list* __l, __owned_link* __c_node) {
  if (__l ==0) {
    (__c_node)->_M_owner = 0;
  } else {
    _STLP_VERBOSE_ASSERT(__l->_Owner()!=0, _StlMsg_INVALID_CONTAINER)
    _STLP_ACQUIRE_LOCK(__l->_M_lock)
    __c_node->_M_owner = __l;
    __c_node->_M_next = __l->_M_node._M_next;
    __l->_M_node._M_next = __c_node;
    _STLP_RELEASE_LOCK(__l->_M_lock)
  }
}

template <class _Dummy>
void*
__stl_debug_engine<_Dummy>::_Get_container_ptr(const __owned_link* __l) {
  const __owned_list* __owner    = __l->_Owner();
  _STLP_VERBOSE_RETURN_0(__owner != 0, _StlMsg_INVALID_ITERATOR)
  void* __ret = const_cast<void*>(__owner->_Owner());
  _STLP_VERBOSE_RETURN_0(__ret !=0, _StlMsg_INVALID_CONTAINER)
  return __ret;
}

template <class _Dummy>
bool
__stl_debug_engine<_Dummy>::_Check_same_owner(const __owned_link& __i1,
                                              const __owned_link& __i2) {
  _STLP_VERBOSE_RETURN(__i1._Valid(), _StlMsg_INVALID_LEFTHAND_ITERATOR)
  _STLP_VERBOSE_RETURN(__i2._Valid(), _StlMsg_INVALID_RIGHTHAND_ITERATOR)
  _STLP_VERBOSE_RETURN((__i1._Owner() == __i2._Owner()), _StlMsg_DIFFERENT_OWNERS)
  return true;
}

template <class _Dummy>
bool
__stl_debug_engine<_Dummy>::_Check_same_or_null_owner(const __owned_link& __i1,
                                                      const __owned_link& __i2) {
  _STLP_VERBOSE_RETURN(__i1._Owner() == __i2._Owner(), _StlMsg_DIFFERENT_OWNERS)
  return true;
}

template <class _Dummy>
bool
__stl_debug_engine<_Dummy>::_Check_if_owner( const __owned_list * __l, const __owned_link& __it) {
  const __owned_list* __owner_ptr = __it._Owner();
  _STLP_VERBOSE_RETURN(__owner_ptr != 0, _StlMsg_INVALID_ITERATOR)
  _STLP_VERBOSE_RETURN(__l == __owner_ptr, _StlMsg_NOT_OWNER)
  return true;
}

template <class _Dummy>
bool
__stl_debug_engine<_Dummy>::_Check_if_not_owner( const __owned_list * __l, const __owned_link& __it) {
  const __owned_list* __owner_ptr = __it._Owner();
  _STLP_VERBOSE_RETURN(__owner_ptr != 0, _StlMsg_INVALID_ITERATOR)
  _STLP_VERBOSE_RETURN(__l != __owner_ptr, _StlMsg_SHOULD_NOT_OWNER)
  return true;
}

}

#  endif /* _STLP_DEBUG */

#endif /* if defined (EXPOSE_GLOBALS_IMPLEMENTATION) */

#endif /* header guard */

// Local Variables:
// mode:C++
// End:
