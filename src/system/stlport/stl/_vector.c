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
#ifndef _STLP_VECTOR_C
#define _STLP_VECTOR_C

#if !defined (_STLP_INTERNAL_VECTOR_H)
#  include <stl/_vector.h>
#endif

#include <stl/_range_errors.h>

namespace _STLP_PRIV {

template <class _Tp, class _Size, class _Alloc>
void _Vector_base<_Tp, _Size, _Alloc>::_M_throw_length_error() const {
  __stl_throw_length_error("vector");
}

template <class _Tp, class _Size, class _Alloc>
void _Vector_base<_Tp, _Size, _Alloc>::_M_throw_out_of_range() const {
  __stl_throw_out_of_range("vector");
}

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  define vector _STLP_PTR_IMPL_NAME(Vector)
#elif defined (_STLP_DEBUG)
#  define vector _STLP_NON_DBG_NAME(vector)
#else
}

namespace _STLP_STD {
#endif

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::reserve(size_type __n) {
  if (capacity() < __n) {
    if (max_size() < __n) {
      this->_M_throw_length_error();
    }

    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_ptr._M_data) {
      __tmp = _M_allocate_and_copy(__n, begin(), end());
      _M_clear();
    } else {
      __tmp = this->_M_ptr.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_insert_overflow_aux(pointer __pos, const _Tp& __x, const __false_type& /*DO NOT USE!!*/,
                                                 size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_ptr.allocate(__len);
  pointer __new_finish = __new_start;
  _STLP_TRY {
    __new_finish = _STLP_PRIV::__uninitialized_move(this->_M_ptr._M_data, __pos, __new_start, _TrivialUCopy(), _Movable());
    // handle insertion
    if (__fill_len == 1) {
      _Copy_Construct(__new_finish, __x);
      ++__new_finish;
    } else
      // TODO: Figure out which type trait should be used here
      __new_finish = _STLP_PRIV::__uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
      __new_finish = _STLP_PRIV::__uninitialized_move(__pos, end(), __new_finish, _TrivialUCopy(), _Movable()); // copy remainder
  }
  _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
               this->_M_ptr.deallocate(__new_start,__len)))
  _M_clear_after_move();
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_insert_overflow(pointer __pos, const _Tp& __x, const __true_type& /*_TrivialCopy*/,
                                             size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_ptr.allocate(__len);
  pointer __new_finish = static_cast<pointer>(_STLP_PRIV::__copy_trivial(this->_M_ptr._M_data, __pos, __new_start));
  // handle insertion
  __new_finish = _STLP_PRIV::__fill_n(__new_finish, __fill_len, __x);
  if (!__atend)
    __new_finish = static_cast<pointer>(_STLP_PRIV::__copy_trivial(__pos, _M_finish(), __new_finish)); // copy remainder
  _M_clear();
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_fill_insert_aux(iterator __pos, size_type __n,
                                             const _Tp& __x, const __true_type& /*_Movable*/) {
  if (_M_is_inside(__x)) {
    _Tp __x_copy = __x;
    _M_fill_insert_aux(__pos, __n, __x_copy, __true_type());
    return;
  }
  iterator __src = end() - 1;
  iterator __dst = __src + __n;
  for (; __src >= __pos; --__dst, --__src) {
    _STLP_STD::_Move_Construct(__dst, *__src);
    _STLP_STD::_Destroy_Moved(__src);
  }
    // TODO: Figure out which type trait should be used here
  _STLP_PRIV::__uninitialized_fill_n(__pos, __n, __x, __false_type());
  _M_inc_finish_idx(__n);
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_fill_insert_aux (iterator __pos, size_type __n,
                                              const _Tp& __x, const __false_type& /*_Movable*/) {
  //Here self referencing needs to be checked even for non movable types.
  if (_M_is_inside(__x)) {
    _Tp __x_copy = __x;
    _M_fill_insert_aux(__pos, __n, __x_copy, __false_type());
    return;
  }
  const size_type __elems_after = end() - __pos;
  pointer __old_finish = end();
  if (__elems_after > __n) {
    _STLP_PRIV::__ucopy_ptrs(end() - __n, end(), end(), _TrivialUCopy());
    _M_inc_finish_idx(__n);
    _STLP_PRIV::__copy_backward_ptrs(__pos, __old_finish - __n, __old_finish, _TrivialCopy());
    _STLP_STD::fill(__pos, __pos + __n, __x);
  } else {
    // TODO: Figure out which type trait should be used here
    iterator __end = _STLP_PRIV::__uninitialized_fill_n(end(), __n - __elems_after, __x, __false_type());
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
    _STLP_PRIV::__ucopy_ptrs(__pos, __old_finish, end(), _TrivialUCopy());
    _M_inc_finish_idx(__elems_after);
    _STLP_STD::fill(__pos, __old_finish, __x);
  }
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_fill_insert(iterator __pos,
                                         size_type __n, const _Tp& __x) {
  if (__n != 0) {
    if (size_type(this->_M_data_size - this->_M_finish_idx) >= __n) {
      _M_fill_insert_aux(__pos, __n, __x, _Movable());
    } else
      _M_insert_overflow(__pos, __x, _TrivialCopy(), __n);
  }
}

template <class _Tp, class _Size, class _Alloc>
vector<_Tp, _Size, _Alloc>& vector<_Tp, _Size, _Alloc>::operator = (const vector<_Tp, _Size, _Alloc>& __x) {
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {
      size_type __len = __xlen;
      pointer __tmp = _M_allocate_and_copy(__len, const_cast<const_pointer>(__x.begin()) + 0,
                                                  const_cast<const_pointer>(__x.end()) + 0);
      _M_clear();
      this->_M_ptr._M_data = __tmp;
      _M_set_data_size(__len);
    } else if (size() >= __xlen) {
      pointer __i = _STLP_PRIV::__copy_ptrs(const_cast<const_pointer>(__x.begin()) + 0,
                                           const_cast<const_pointer>(__x.end()) + 0, begin(), _TrivialCopy());
      _STLP_STD::_Destroy_Range(__i, end());
    } else {
      _STLP_PRIV::__copy_ptrs(const_cast<const_pointer>(__x.begin()),
                             const_cast<const_pointer>(__x.begin()) + size(), begin(), _TrivialCopy());
      _STLP_PRIV::__ucopy_ptrs(const_cast<const_pointer>(__x.begin()) + size(),
                              const_cast<const_pointer>(__x.end()) + 0, end(), _TrivialUCopy());
    }
    _M_set_finish_idx(__xlen);
  }
  return *this;
}

template <class _Tp, class _Size, class _Alloc>
void vector<_Tp, _Size, _Alloc>::_M_fill_assign(size_type __n, const _Tp& __val) {
  if (__n > capacity()) {
    vector<_Tp, _Size, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  } else if (__n > size()) {
    fill(begin(), end(), __val);
    // TODO: Figure out which type trait should be used here
    iterator __end = _STLP_PRIV::__uninitialized_fill_n(end(), __n - size(), __val, __false_type());
    _M_set_finish_idx(__end - begin());
  } else
    erase(_STLP_PRIV::__fill_n(begin(), __n, __val), end());
}

template <class _Tp, class _Size, class _Alloc>
typename vector<_Tp, _Size, _Alloc>::iterator
vector<_Tp, _Size, _Alloc>::insert(iterator __pos, const _Tp& __x) {
  size_type __n = __pos - begin();
  _M_fill_insert(__pos, 1, __x);
  return begin() + __n;
}

}

#if defined (vector)
#  undef vector
#endif

#endif /*  _STLP_VECTOR_C */

// Local Variables:
// mode:C++
// End:
