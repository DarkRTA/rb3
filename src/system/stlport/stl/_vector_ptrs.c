/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
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
#ifndef _STLP_VECTOR_PTRS_C
#define _STLP_VECTOR_PTRS_C

#if !defined (_STLP_INTERNAL_VECTOR_PTRS_H)
#  include <stl/_vector_ptrs.h>
#endif

#include <stl/_range_errors.h>

_STLP_BEGIN_NAMESPACE

#if defined ( _STLP_NESTED_TYPE_PARAM_BUG )
#  define __iterator__        _Tp*
#else
#  define __iterator__        _STLP_TYPENAME_ON_RETURN_TYPE _VECTOR_IMPL<_Tp, _Alloc>::iterator
#endif

template <class _Tp, class _Alloc> 
void _Vector_base<_Tp,_Alloc>::_M_throw_length_error() const {
  __stl_throw_length_error("vector");
}

template <class _Tp, class _Alloc> 
void _Vector_base<_Tp, _Alloc>::_M_throw_out_of_range() const {
  __stl_throw_out_of_range("vector");
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::reserve(size_type __n) {
  if (capacity() < __n) {
    if (max_size() < __n) {
      this->_M_throw_length_error();
    }

    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, this->_M_start, this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_insert_overflow_aux(pointer __pos, const _Tp& __x, const __false_type& /*NOT TO USE!!*/,
                                                       size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  const size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_end_of_storage.allocate(__len);
  pointer __new_finish = __new_start;
  _STLP_TRY {
    __new_finish = __uninitialized_move(this->_M_start, __pos, __new_start, _TrivialUCpy(), _Movable());
    // handle insertion
    if (__fill_len == 1) {
      _Copy_Construct(__new_finish, __x);
      ++__new_finish;
    } else
      __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
      __new_finish = __uninitialized_move(__pos, this->_M_finish, __new_finish, _TrivialUCpy(), _Movable()); // copy remainder
  }
  _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
               this->_M_end_of_storage.deallocate(__new_start,__len)))
  _M_clear_after_move();
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_insert_overflow(pointer __pos, const _Tp& __x, const __true_type& /*_TrivialCpy*/,
                                                   size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  const size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_end_of_storage.allocate(__len);
  pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __pos, __new_start);
  // handle insertion
  __new_finish = __fill_n(__new_finish, __fill_len, __x);
  if (!__atend)
    __new_finish = (pointer)__copy_trivial(__pos, this->_M_finish, __new_finish); // copy remainder
  _M_clear();
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_insert_aux (iterator __pos, size_type __n, 
                                                    const _Tp& __x, const __true_type& /*_Movable*/) {
  if (_M_is_inside(__x)) {
    _Tp __x_copy = __x;
    _M_fill_insert_aux(__pos, __n, __x_copy, __true_type());
    return;
  }
  iterator __src = this->_M_finish - 1;
  iterator __dst = __src + __n;
  for (; __src >= __pos; --__dst, --__src) {
    _STLP_STD::_Move_Construct(__dst, *__src);
    _STLP_STD::_Destroy_Moved(__src);
  }
  __uninitialized_fill_n(__pos, __n, __x, _PODType());
  this->_M_finish += __n;
}
template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_insert_aux (iterator __pos, size_type __n, 
                                                    const _Tp& __x, const __false_type& /*_Movable*/) {
  //Here self referencing needs to be checked even for non movable types.
  if (_M_is_inside(__x)) {
    _Tp __x_copy = __x;
    _M_fill_insert_aux(__pos, __n, __x_copy, __false_type());
    return;
  }
  const size_type __elems_after = this->_M_finish - __pos;
  pointer __old_finish = this->_M_finish;
  if (__elems_after > __n) {
    __uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _TrivialUCpy());
    this->_M_finish += __n;
    __copy_backward_ptrs(__pos, __old_finish - __n, __old_finish, _TrivialAss());
    _STLP_STD::fill(__pos, __pos + __n, __x);
  } else {
    this->_M_finish = __uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x, _PODType());
    __uninitialized_copy(__pos, __old_finish, this->_M_finish, _TrivialUCpy());
    this->_M_finish += __elems_after;
    _STLP_STD::fill(__pos, __old_finish, __x);
  }
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_insert(iterator __pos,
                                               size_type __n, const _Tp& __x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      _M_fill_insert_aux(__pos, __n, __x, _Movable());
    } else 
      _M_insert_overflow(__pos, __x, _TrivialCpy(), __n);
  }
}

template <class _Tp, class _Alloc>
_VECTOR_IMPL<_Tp,_Alloc>& _VECTOR_IMPL<_Tp,_Alloc>::operator=(const _VECTOR_IMPL<_Tp, _Alloc>& __x) {
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {
      pointer __tmp = _M_allocate_and_copy(__xlen, __CONST_CAST(const_pointer, __x._M_start)+0, __CONST_CAST(const_pointer, __x._M_finish)+0);
      _M_clear();
      this->_M_start = __tmp;
      this->_M_end_of_storage._M_data = this->_M_start + __xlen;
    } else if (size() >= __xlen) {
      pointer __i = __copy_ptrs(__CONST_CAST(const_pointer, __x._M_start)+0, __CONST_CAST(const_pointer, __x._M_finish)+0, this->_M_start, _TrivialAss());
      _STLP_STD::_Destroy_Range(__i, this->_M_finish);
    } else {
      __copy_ptrs(__CONST_CAST(const_pointer, __x._M_start), __CONST_CAST(const_pointer, __x._M_start) + size(), this->_M_start, _TrivialAss());
      __uninitialized_copy(__CONST_CAST(const_pointer, __x._M_start) + size(), 
                           __CONST_CAST(const_pointer, __x._M_finish)+0, this->_M_finish, _TrivialUCpy());
    }
    this->_M_finish = this->_M_start + __xlen;
  }
  return *this;
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_assign(size_t __n, const _Tp& __val) {
  if (__n > capacity()) {
    _VECTOR_IMPL<_Tp, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  } else if (__n > size()) {
    fill(begin(), end(), __val);
    this->_M_finish = __uninitialized_fill_n(this->_M_finish, __n - size(), __val, _PODType());
  } else
    erase(__fill_n(begin(), __n, __val), end());
}

template <class _Tp, class _Alloc>
__iterator__
_VECTOR_IMPL<_Tp, _Alloc>::insert(iterator __pos, const _Tp& __x) {
  size_type __n = __pos - begin();
  _M_fill_insert(__pos, 1, __x);
  return begin() + __n;
}

#undef __iterator__

_STLP_END_NAMESPACE

#endif /*  _STLP_VECTOR_C */

// Local Variables:
// mode:C++
// End:
