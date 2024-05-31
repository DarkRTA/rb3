/*
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_VECTOR_H
#define _STLP_INTERNAL_VECTOR_H

#ifndef _STLP_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
#endif

#ifndef _STLP_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
#endif

#ifndef _STLP_INTERNAL_UNINITIALIZED_H
#  include <stl/_uninitialized.h>
#endif

#ifdef MILO_DEBUG
// From system/os/Debug.cpp
// Declared here since it's not relevant anywhere else
void std_vec_range_assert(size_t value, size_t max, const char *func);
#  define _STLP_VEC_RANGE_ASSERT(value, max) std_vec_range_assert(value, max, __FUNCTION__)
#else
#  define _STLP_VEC_RANGE_ASSERT(value, max) (void)0
#endif

// The vector base class serves one purpose, its constructor and
// destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.

namespace _STLP_PRIV {

template <class _Tp, class _Size, class _Alloc>
class _Vector_base {
public:
  typedef _Vector_base<_Tp, _Size, _Alloc> _Self;

  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;
  typedef _STLP_alloc_proxy<pointer, _Tp, allocator_type> _AllocProxy;

  _Vector_base(const _Alloc& __a)
    : _M_ptr(__a, 0), _M_finish_idx(0), _M_data_size(0) {}

  _Vector_base(size_t __n, const _Alloc& __a)
    : _M_ptr(__a, 0), _M_finish_idx(0), _M_data_size(__n) {
    _M_ptr._M_data = _M_ptr.allocate(__n);
  }

  _Vector_base(__move_source<_Self> src)
    : _M_ptr(__move_source<_AllocProxy>(src.get()._M_ptr)),
      _M_finish_idx(src.get()._M_finish_idx), _M_data_size(src.get()._M_data_size) {
    //Set the source as empty:
    src.get()._M_finish_idx = src.get()._M_data_size = src.get()._M_ptr._M_data = 0;
  }

  ~_Vector_base() {
    if (_M_ptr._M_data != pointer())
      _M_ptr.deallocate(_M_ptr._M_data, _M_data_size);

    _M_ptr._M_data = 0;
    _M_finish_idx = 0;
    _M_data_size = 0;
  }

protected:
  void _STLP_FUNCTION_THROWS _M_throw_length_error() const;
  void _STLP_FUNCTION_THROWS _M_throw_out_of_range() const;

  pointer _M_finish() { return _M_ptr._M_data + _M_finish_idx; }
  const_pointer _M_finish() const { return _M_ptr._M_data + _M_finish_idx; }

    // _M_inc_finish_idx in retail doesn't match with size_type as the parameter,
    // but symbols in bank 8 indicate it uses size_type
#ifdef VERSION_SZBE69
  void _M_inc_finish_idx(_Size increment) {
#else
  void _M_inc_finish_idx(size_type increment) {
#endif
    _STLP_VEC_RANGE_ASSERT(_M_finish_idx + increment, (_Size)~0);
    _M_finish_idx = _M_finish_idx + increment;
  }

  void _M_set_finish_idx(size_type idx) {
    _STLP_VEC_RANGE_ASSERT(idx, (_Size)~0);
    _M_finish_idx = idx;
  }

  void _M_set_data_size(size_type size) {
    _STLP_VEC_RANGE_ASSERT(size, (_Size)~0);
    _M_data_size = size;
  }

  _AllocProxy _M_ptr;
  _Size _M_finish_idx;
  _Size _M_data_size;
};

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  define vector _STLP_PTR_IMPL_NAME(Vector)
#elif defined (_STLP_DEBUG)
#  define vector _STLP_NON_DBG_NAME(Vector)
#else
}

namespace _STLP_STD {
#endif

template <class _Tp, class _Size = unsigned short, class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Tp) >
class vector : protected _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>
{
private:
  typedef _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc> _Base;
  typedef vector<_Tp, _Size, _Alloc> _Self;
public:
  typedef typename _Base::allocator_type allocator_type;

  typedef _Base::value_type value_type;
  typedef _Base::pointer pointer;
  typedef _Base::const_pointer const_pointer;
  typedef _Base::reference reference;
  typedef _Base::const_reference const_reference;
  typedef _Base::iterator iterator;
  typedef _Base::const_iterator const_iterator;

  typedef _Base::size_type size_type;
  typedef _Base::difference_type difference_type;

  typedef random_access_iterator_tag _Iterator_category;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

  allocator_type get_allocator() const
  { return (const allocator_type&)this->_M_ptr; }

private:
  typedef typename __type_traits<_Tp>::has_trivial_assignment_operator _TrivialCopy;
  typedef typename __type_traits<_Tp>::has_trivial_copy_constructor _TrivialUCopy;
#if !defined (_STLP_NO_MOVE_SEMANTIC)
  typedef typename __move_traits<_Tp>::implemented _Movable;
#else
  typedef __false_type _Movable;
#endif

  // handles insertions on overflow
  void _M_insert_overflow_aux(pointer __pos, const _Tp& __x, const __false_type& /*_Movable*/,
                              size_type __fill_len, bool __atend);
  void _M_insert_overflow_aux(pointer __pos, const _Tp& __x, const __true_type& /*_Movable*/,
                              size_type __fill_len, bool __atend) {
    //We need to take care of self referencing here:
    if (_M_is_inside(__x)) {
      value_type __x_copy = __x;
      _M_insert_overflow_aux(__pos, __x_copy, __false_type(), __fill_len, __atend);
      return;
    }
    _M_insert_overflow_aux(__pos, __x, __false_type(), __fill_len, __atend);
  }

  void _M_insert_overflow(pointer __pos, const _Tp& __x, const __false_type& /*_TrivialCopy*/,
                          size_type __fill_len, bool __atend = false)
  { _M_insert_overflow_aux(__pos, __x, _Movable(), __fill_len, __atend); }
  void _M_insert_overflow(pointer __pos, const _Tp& __x, const __true_type& /*_TrivialCopy*/,
                          size_type __fill_len, bool __atend = false);
  void _M_range_check(size_type __n) const {
    if (__n >= _M_finish_idx)
      this->_M_throw_out_of_range();
  }

public:
  iterator begin()             { return this->_M_ptr._M_data; }
  const_iterator begin() const { return this->_M_ptr._M_data; }
  iterator end()               { return this->_M_ptr._M_data + _M_finish_idx; }
  const_iterator end() const   { return this->_M_ptr._M_data + _M_finish_idx; }

                                         // for some reason rbegin() uses end()
                                         // but rend() doesn't use begin()? wack
  reverse_iterator rbegin()              { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
  reverse_iterator rend()                { return reverse_iterator(this->_M_ptr._M_data); }
  const_reverse_iterator rend() const    { return const_reverse_iterator(this->_M_ptr._M_data); }

  size_type size() const        { return _M_finish_idx; }
  size_type max_size() const {
    size_type __vector_max_size = size_type(-1) / sizeof(_Tp);
    typename allocator_type::size_type __alloc_max_size = this->_M_ptr.max_size();
    return (__alloc_max_size < __vector_max_size)?__alloc_max_size:__vector_max_size;
  }

  size_type capacity() const    { return _M_data_size; }
  bool empty() const            { return _M_finish_idx == 0; }

  reference operator[](size_type __n) { return this->_M_ptr._M_data[__n]; }
  const_reference operator[](size_type __n) const { return this->_M_ptr._M_data[__n]; }

  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back()              { return *(end() - 1); }
  const_reference back() const  { return *(end() - 1); }

  reference at(size_type __n) { _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const { _M_range_check(__n); return (*this)[__n]; }

  explicit vector(const allocator_type& __a = allocator_type())
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__a) {}

private:
  //We always call _M_initialize with only 1 parameter. Default parameter
  //is used to allow explicit instanciation of vector with types with no
  //default constructor.
  void _M_initialize(size_type __n, const _Tp& __val = _Tp()) {
    iterator __end = _STLP_PRIV::__uninitialized_init(this->_M_ptr._M_data, __n, __val);
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
  }

public:
  explicit vector(size_type __n)
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__n, allocator_type())
  { _M_initialize(__n); }
  vector(size_type __n, const _Tp& __val, const allocator_type& __a = allocator_type())
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__n, __a) {
    // TODO: Figure out which type trait should be used here
    iterator __end = _STLP_PRIV::__uninitialized_fill_n(this->_M_ptr._M_data, __n, __val, __false_type());
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
  }

  vector(const _Self& __x)
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__x.size(), __x.get_allocator()) {
    iterator __end = _STLP_PRIV::__ucopy_ptrs(__x.begin(), __x.end(), this->_M_ptr._M_data, _TrivialUCopy());
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
  }

  vector(__move_source<_Self> src)
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__move_source<_Base>(src.get()))
  {}

private:
  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __val,
                         const __true_type& /*_IsIntegral*/) {
    this->_M_ptr._M_data = this->_M_ptr.allocate(__n);
    _M_set_data_size(__n);
    _M_set_finish_idx(__n);
    // TODO: Figure out which type trait should be used here
    iterator __end = __uninitialized_fill_n(this->_M_ptr._M_data, __n, __val, __false_type());
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
  }

  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first, _InputIterator __last,
                         const __false_type& /*_IsIntegral*/)
  { _M_range_initialize(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator)); }

public:
  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
               const allocator_type& __a = allocator_type() )
    : _STLP_PRIV::_Vector_base<_Tp, _Size, _Alloc>(__a) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_initialize_aux(__first, __last, _Integral());
  }

  //As the vector container is a back insert oriented container it
  //seems rather logical to destroy elements in reverse order.
  ~vector() { _STLP_STD::_Destroy_Range(rbegin(), rend()); }

  _Self& operator=(const _Self& __x);

  void reserve(size_type __n);

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const _Tp& __val) { _M_fill_assign(__n, __val); }
  void _M_fill_assign(size_type __n, const _Tp& __val);

  template <class _ForwardIter>
  void _M_assign_aux(_ForwardIter __first, _ForwardIter __last, const forward_iterator_tag &) {
    const size_type __len = distance(__first, __last);
    if (__len > capacity()) {
      size_type __n = __len;
      iterator __tmp = _M_allocate_and_copy(__n, __first, __last);
      _M_clear();
      _M_set(__tmp, __tmp + __len, __tmp + __n);
    }
    else if (size() >= __len) {
      iterator __new_finish = copy(__first, __last, this->_M_ptr._M_data);
      _STLP_STD::_Destroy_Range(__new_finish, end());
      _M_set_finish_idx(__new_finish - this->_M_ptr._M_data);
    }
    else {
      _ForwardIter __mid = __first;
      advance(__mid, size());
      copy(__first, __mid, this->_M_ptr._M_data);
      _M_set_finish_idx(uninitialized_copy(__mid, __last, end()) - this->_M_ptr._M_data);
    }
  }

  template <class _InputIter>
  void _M_assign_aux(_InputIter __first, _InputIter __last,
                     const input_iterator_tag &) {
    iterator __cur = begin();
    for ( ; __first != __last && __cur != end(); ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      erase(__cur, end());
    else
      insert(end(), __first, __last);
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val,
                          const __true_type& /*_IsIntegral*/)
  { _M_fill_assign(__n, __val); }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last,
                          const __false_type& /*_IsIntegral*/)
  { _M_assign_aux(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIter)); }

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

#if !defined (_STLP_NO_ANACHRONISMS)
  void push_back(const _Tp& __x = _Tp()) {
#else
  void push_back(const _Tp& __x) {
#endif
    if (this->_M_finish_idx != this->_M_data_size) {
      _Copy_Construct(_M_finish(), __x);
      _M_inc_finish_idx(1);
    }
    else
      _M_insert_overflow(_M_finish(), __x, _TrivialCopy(), 1UL, true);
  }

#if !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const _Tp& __x = _Tp());
#else
  iterator insert(iterator __pos, const _Tp& __x);
#endif

  void swap(_Self& __x) {
    this->_M_ptr.swap(__x._M_ptr);
    _STLP_STD::swap(this->_M_finish_idx, __x._M_finish_idx);
    _STLP_STD::swap(this->_M_data_size, __x._M_data_size);
  }

private:
  void _M_fill_insert_aux (iterator __pos, size_type __n, const _Tp& __x, const __true_type& /*_Movable*/);
  void _M_fill_insert_aux (iterator __pos, size_type __n, const _Tp& __x, const __false_type& /*_Movable*/);
  void _M_fill_insert (iterator __pos, size_type __n, const _Tp& __x);

  bool _M_is_inside(const value_type& __x) const {
    return (&__x >= begin() && &__x < end());
  }

  template <class _ForwardIterator>
  void _M_range_insert_realloc(iterator __pos,
                               _ForwardIterator __first, _ForwardIterator __last,
                               size_type __n) {
    const size_type __old_size = size();
    size_type __len = __old_size + (max)(__old_size, __n);
    pointer __new_start = this->_M_ptr.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = _STLP_PRIV::__uninitialized_move(begin(), __pos, __new_start, _TrivialUCopy(), _Movable());
      __new_finish = uninitialized_copy(__first, __last, __new_finish);
      __new_finish = _STLP_PRIV::__uninitialized_move(__pos, end(), __new_finish, _TrivialUCopy(), _Movable());
    }
    _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
                  this->_M_ptr.deallocate(__new_start,__len)))
    _M_clear_after_move();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }

  template <class _ForwardIterator>
  void _M_range_insert_aux(iterator __pos,
                           _ForwardIterator __first, _ForwardIterator __last,
                           size_type __n, const __true_type& /*_Movable*/) {
    iterator __src = end() - 1;
    iterator __dst = __src + __n;
    for (; __src >= __pos; --__dst, --__src) {
      _STLP_STD::_Move_Construct(__dst, *__src);
      _STLP_STD::_Destroy_Moved(__src);
    }
    uninitialized_copy(__first, __last, __pos);
    _M_inc_finish_idx(__n);
  }

  template <class _ForwardIterator>
  void _M_range_insert_aux(iterator __pos,
                           _ForwardIterator __first, _ForwardIterator __last,
                           size_type __n, const __false_type& /*_Movable*/) {
    const size_type __elems_after = end() - __pos;
    pointer __old_finish = end();
    if (__elems_after > __n) {
      _STLP_PRIV::__ucopy_ptrs(end() - __n, end(), end(), _TrivialUCopy());
      _M_inc_finish_idx(__n);
      _STLP_PRIV::__copy_backward_ptrs(__pos, __old_finish - __n, __old_finish, _TrivialCopy());
      copy(__first, __last, __pos);
    }
    else {
      _ForwardIterator __mid = __first;
      advance(__mid, __elems_after);
      uninitialized_copy(__mid, __last,end());
      _M_inc_finish_idx(__n - __elems_after);
      _STLP_PRIV::__ucopy_ptrs(__pos, __old_finish,end(), _TrivialUCopy());
      _M_inc_finish_idx(__elems_after);
      copy(__first, __mid, __pos);
    } /* elems_after */
  }


  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                          const __true_type&)
  { _M_fill_insert(__pos, (size_type) __n, (_Tp) __val); }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          const __false_type&)
  { _M_range_insert(__pos, __first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator)); }

public:
  // Check whether it's an integral type.  If so, it's not an iterator.
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

private:
  template <class _InputIterator>
  void _M_range_insert(iterator __pos,
                       _InputIterator __first, _InputIterator __last,
                       const input_iterator_tag &) {
    for ( ; __first != __last; ++__first) {
      __pos = insert(__pos, *__first);
      ++__pos;
    }
  }

  template <class _ForwardIterator>
  void _M_range_insert(iterator __pos,
                       _ForwardIterator __first, _ForwardIterator __last,
                       const forward_iterator_tag &) {
    /* This method do not check self referencing.
     * Standard forbids it, checked by the debug mode.
     */
    if (__first != __last) {
      size_type __n = distance(__first, __last);

      if (size_type(this->_M_data_size - this->_M_finish_idx) >= __n) {
        _M_range_insert_aux(__pos, __first, __last, __n, _Movable());
      }
      else {
        _M_range_insert_realloc(__pos, __first, __last, __n);
      }
    }
  }

public:
  void insert (iterator __pos, size_type __n, const _Tp& __x)
  { _M_fill_insert(__pos, __n, __x); }

  void pop_back() {
    _M_inc_finish_idx(-1);
    _STLP_STD::_Destroy(end());
  }

private:
  iterator _M_erase(iterator __pos, const __true_type& /*_Movable*/) {
    _STLP_STD::_Destroy(__pos);
    iterator __dst = __pos, __src = __dst + 1;
    iterator __end = end();
    for (; __src != __end; ++__dst, ++__src) {
      _STLP_STD::_Move_Construct(__dst, *__src);
      _STLP_STD::_Destroy_Moved(__src);
    }
    _M_set_finish_idx(__dst - begin());
    return __pos;
  }
  iterator _M_erase(iterator __pos, const __false_type& /*_Movable*/) {
    if (__pos + 1 != end())
      _STLP_PRIV::__copy_ptrs(__pos + 1, end(), __pos, _TrivialCopy());
    _M_inc_finish_idx(-1);
    _STLP_STD::_Destroy(end());
    return __pos;
  }
  iterator _M_erase(iterator __first, iterator __last, const __true_type& /*_Movable*/) {
    iterator __dst = __first, __src = __last;
    iterator __end = end();
    for (; __dst != __last && __src != __end; ++__dst, ++__src) {
      _STLP_STD::_Destroy(__dst);
      _STLP_STD::_Move_Construct(__dst, *__src);
    }
    if (__dst != __last) {
      //There is more elements to erase than element to move:
      _STLP_STD::_Destroy_Range(__dst, __last);
      _STLP_STD::_Destroy_Moved_Range(__last, __end);
    }
    else {
      //There is more element to move than element to erase:
      for (; __src != __end; ++__dst, ++__src) {
        _STLP_STD::_Destroy_Moved(__dst);
        _STLP_STD::_Move_Construct(__dst, *__src);
      }
      _STLP_STD::_Destroy_Moved_Range(__dst, __end);
    }
    _M_set_finish_idx(__dst - begin());
    return __first;
  }
  iterator _M_erase(iterator __first, iterator __last, const __false_type& /*_Movable*/) {
    pointer __i = _STLP_PRIV::__copy_ptrs(__last, end(), __first, _TrivialCopy());
    _STLP_STD::_Destroy_Range(__i, end());
    _M_set_finish_idx(__i - begin());
    return __first;
  }

public:
  iterator erase(iterator __pos) {
    return _M_erase(__pos, _Movable());
  }
  iterator erase(iterator __first, iterator __last) {
    if (__first == __last)
      return __first;
    return _M_erase(__first, __last, _Movable());
  }

  void resize(size_type __new_size, const _Tp& __x = _Tp()) {
    if (__new_size < size())
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }

  void clear() {
    erase(this->_M_ptr._M_data, end());
  }

private:
  void _M_clear() {
    _STLP_STD::_Destroy_Range(rbegin(), rend());
    this->_M_ptr.deallocate(this->_M_ptr._M_data, this->_M_data_size);
  }

  void _M_clear_after_move() {
    _STLP_STD::_Destroy_Moved_Range(rbegin(), rend());
    this->_M_ptr.deallocate(this->_M_ptr._M_data, this->_M_data_size);
  }

  void _M_set(pointer __s, pointer __f, pointer __e) {
    this->_M_ptr._M_data = __s;
    _M_set_finish_idx(__f - __s);
    _M_set_data_size(__e - __s);
  }

  template <class _ForwardIterator>
  pointer _M_allocate_and_copy(size_type& __n,
                               _ForwardIterator __first, _ForwardIterator __last)
  {
    pointer __result = this->_M_ptr.allocate(__n);
    _STLP_TRY {
      uninitialized_copy(__first, __last, __result);
      return __result;
    }
    _STLP_UNWIND(this->_M_ptr.deallocate(__result, __n))
    _STLP_RET_AFTER_THROW(__result)
  }


  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first, _InputIterator __last,
                           const input_iterator_tag &) {
    for ( ; __first != __last; ++__first)
      push_back(*__first);
  }
  // This function is only called by the constructor.
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
                           const forward_iterator_tag &) {
    size_type __n = distance(__first, __last);
    this->_M_ptr._M_data = this->_M_ptr.allocate(__n);
    _M_set_data_size(__n);
    iterator __end = uninitialized_copy(__first, __last, this->_M_ptr._M_data);
    _M_set_finish_idx(__end - this->_M_ptr._M_data);
  }
};

}

#if defined (vector)
#  undef vector
#endif

#if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_vector.c>
#endif

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  include <stl/pointers/_vector.h>
#endif

//We define the bool specialization before the debug interfave
//to benefit of the debug version of vector even for the bool
//specialization.
#if !defined (_STLP_NO_EXTENSIONS)
#  if !defined (_STLP_INTERNAL_BVECTOR_H)
#    include <stl/_bvector.h>
#  endif
#endif

#if defined (_STLP_DEBUG)
#  include <stl/debug/_vector.h>
#endif

namespace _STLP_STD {

#if !defined (_STLP_NO_EXTENSIONS)
// This typedef is non-standard.  It is provided for backward compatibility.
typedef vector<bool, allocator<bool> > bit_vector;
#endif

#define _STLP_TEMPLATE_HEADER template <class _Tp, class _Size, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER vector<_Tp, _Size, _Alloc>
#include <stl/_relops_cont.h>
#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER

template <class _Tp, class _Size, class _Alloc>
struct __move_traits<vector<_Tp, _Size, _Alloc> > {
  typedef __stlp_movable implemented;
  typedef typename __move_traits<_Alloc>::complete complete;
};

#  if !defined (_STLP_DEBUG)
template <class _Tp, class _Size, class _Alloc>
struct _DefaultZeroValue<vector<_Tp, _Size, _Alloc> >
{ typedef typename __type_traits<_Alloc>::has_trivial_default_constructor _Ret; };
#  endif

}

#endif /* _STLP_VECTOR_H */

// Local Variables:
// mode:C++
// End:
