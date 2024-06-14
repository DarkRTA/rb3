/*
 * Copyright (c) 2003
 * Francois Dumont
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

#ifndef _STLP_SPECIALIZED_VECTOR_H
#define _STLP_SPECIALIZED_VECTOR_H

#ifndef _STLP_POINTERS_SPEC_TOOLS_H
#  include <stl/pointers/_tools.h>
#endif

#define VECTOR_IMPL _STLP_PTR_IMPL_NAME(Vector)

#if defined (_STLP_DEBUG)
#  define vector _STLP_NON_DBG_NAME(vector)
namespace _STLP_PRIV {
#else
namespace _STLP_STD {
#endif

template <class _Tp, class _Size = unsigned short, class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Tp) >
class vector
{
  /* In the vector implementation iterators are pointer which give a number
   * of opportunities for optimization. To not break those optimizations
   * iterators passed to template should not be wrapped for casting purpose.
   * So vector implementation will always use a qualified void pointer type and
   * won't use iterator wrapping.
   */
  typedef typename _STLP_PRIV::_StorageType<_Tp>::_QualifiedType _StorageType;
  typedef typename _Alloc_traits<_StorageType, _Alloc>::allocator_type _StorageTypeAlloc;
  typedef _STLP_PRIV::VECTOR_IMPL<_StorageType, _Size, _StorageTypeAlloc> _Base;
  typedef vector<_Tp, _Size, _Alloc> _Self;

public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;
  typedef typename _Alloc_traits<value_type, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const
  { return _M_impl.get_allocator(); }

  iterator begin()             { return _M_impl.begin(); }
  const_iterator begin() const { return _M_impl.begin(); }
  iterator end()               { return _M_impl.end(); }
  const_iterator end() const   { return _M_impl.end(); }

  reverse_iterator rbegin()              { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
  reverse_iterator rend()                { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const    { return const_reverse_iterator(begin()); }

  size_type size() const        { return _M_impl.size(); }
  size_type max_size() const    { return _M_impl.max_size(); }

  size_type capacity() const    { return _M_impl.capacity(); }
  bool empty() const            { return _M_impl.empty(); }

  reference operator[](size_type __n) { return _M_impl[__n]; }
  const_reference operator[](size_type __n) const { return _M_impl[__n]; }

  reference front()             { return _M_impl.front(); }
  const_reference front() const { return _M_impl.front(); }
  reference back()              { return _M_impl.back(); }
  const_reference back() const  { return _M_impl.back(); }

  reference at(size_type __n) { return _M_impl.at(__n); }
  const_reference at(size_type __n) const { return _M_impl.at(__n); }

#ifdef VERSION_SZBE69
  explicit vector(const allocator_type& __a = allocator_type())
    : _M_impl(_STLP_CONVERT_ALLOCATOR(__a, allocator_type, _StorageType)) {}
#else
  explicit vector()
    : _M_impl(_STLP_CONVERT_ALLOCATOR(allocator_type(), allocator_type, _StorageType)) {}

  explicit vector(const allocator_type& __a)
    : _M_impl(_STLP_CONVERT_ALLOCATOR(__a, allocator_type, _StorageType)) {}
#endif

  explicit vector(size_type __n, const value_type& __val = value_type(),
         const allocator_type& __a = allocator_type())
    : _M_impl(__n, __val, __a) {}

  vector(const _Self& __x)
    : _M_impl(__x._M_impl) {}

  explicit vector(__move_source<_Self> src)
    : _M_impl(__move_source<_Base>(src.get()._M_impl)) {}

  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const allocator_type& __a = allocator_type() )
  : _M_impl(__first, __last,
            __a) {}

  _Self& operator=(const _Self& __x) { _M_impl = __x._M_impl; return *this; }

  void reserve(size_type __n) {_M_impl.reserve(__n);}
  void assign(size_type __n, const value_type& __val)
  { _M_impl.assign(__n, __val); }

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last)
  { _M_impl.assign(__first, __last); }

#if !defined(_STLP_NO_ANACHRONISMS)
  void push_back(const value_type& __x = value_type())
#else
  void push_back(const value_type& __x)
#endif
  { _M_impl.push_back(__x); }

#if !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const value_type& __x = value_type())
#else
  iterator insert(iterator __pos, const value_type& __x)
#endif
  { return _M_impl.insert(__pos, __x); }

  void swap(_Self& __x) { _M_impl.swap(__x._M_impl); }

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last)
  { _M_impl.insert(__pos, __first, __last); }

  void insert (iterator __pos, size_type __n, const value_type& __x) {
    _M_impl.insert(__pos, __n, __x);
  }

  void pop_back() {_M_impl.pop_back();}
  iterator erase(iterator __pos)
  {return _M_impl.erase(__pos); }
  iterator erase(iterator __first, iterator __last) {
    return _M_impl.erase(__first, __last);
  }

  void resize(size_type __new_size, const value_type& __x = value_type())
  { _M_impl.resize(__new_size, __x); }

  void clear() { _M_impl.clear(); }

private:
  _Base _M_impl;
};

// Pointer wrapper
// Necessary due to differences specific to vectors containing pointers.
// The original implementation above is left unmodified to prevent making new issues.
template <class _Tp, class _Size, class _Alloc>
class vector<_Tp*, _Size, _Alloc>
{
  typedef void* _StorageType;
  typedef typename _Alloc_traits<_StorageType, _Alloc>::allocator_type _StorageTypeAlloc;
  typedef _STLP_PRIV::VECTOR_IMPL<_StorageType, _Size, _StorageTypeAlloc> _Base;
  typedef vector<_Tp, _Size, _Alloc> _Self;

public:
  typedef _Tp* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;

  _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;
  typedef typename _Alloc_traits<value_type, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const
  { return _M_impl.get_allocator(); }

  iterator begin()             { return reinterpret_cast<iterator>(_M_impl.begin()); }
  const_iterator begin() const { return reinterpret_cast<const_iterator>(_M_impl.begin()); }
  iterator end()               { return reinterpret_cast<iterator>(_M_impl.end()); }
  const_iterator end() const   { return reinterpret_cast<const_iterator>(_M_impl.end()); }

  reverse_iterator rbegin()              { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
  reverse_iterator rend()                { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const    { return const_reverse_iterator(begin()); }

  size_type size() const        { return _M_impl.size(); }
  size_type max_size() const    { return _M_impl.max_size(); }

  size_type capacity() const    { return _M_impl.capacity(); }
  bool empty() const            { return _M_impl.empty(); }

  reference operator[](size_type __n) { return reinterpret_cast<reference>(_M_impl[__n]); }
  const_reference operator[](size_type __n) const { return reinterpret_cast<const_reference>(_M_impl[__n]); }

  reference front()             { return reinterpret_cast<reference>(_M_impl.front()); }
  const_reference front() const { return reinterpret_cast<const_reference>(_M_impl.front()); }
  reference back()              { return reinterpret_cast<reference>(_M_impl.back()); }
  const_reference back() const  { return reinterpret_cast<const_reference>(_M_impl.back()); }

  reference at(size_type __n) { return reinterpret_cast<reference>(_M_impl.at(__n)); }
  const_reference at(size_type __n) const { return reinterpret_cast<const_reference>(_M_impl.at(__n)); }

  explicit vector(const allocator_type& __a = allocator_type())
    : _M_impl(_STLP_CONVERT_ALLOCATOR(__a, allocator_type, _StorageType)) {}

  explicit vector(size_type __n, const value_type& __val = value_type(),
         const allocator_type& __a = allocator_type())
    : _M_impl(__n, reinterpret_cast<_StorageType const&>(__val),
      __a) {}

  vector(const _Self& __x)
    : _M_impl(__x._M_impl) {}

  explicit vector(__move_source<_Self> src)
    : _M_impl(__move_source<_Base>(src.get()._M_impl)) {}

  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
         const allocator_type& __a = allocator_type() )
  : _M_impl(__first, __last,
            __a) {}

  _Self& operator=(const _Self& __x) { _M_impl = __x._M_impl; return *this; }

  void reserve(size_type __n) {_M_impl.reserve(__n);}
  void assign(size_type __n, const value_type& __val)
  { _M_impl.assign(__n, reinterpret_cast<_StorageType const&>(__val)); }

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last)
  { _M_impl.assign(__first, __last); }

  void push_back(value_type __x) {
    _Tp& __y = *__x; // Necessary to match correctly
    _M_impl.push_back(reinterpret_cast<_StorageType*>(&__y));
  }

#if !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const value_type& __x = value_type())
#else
  iterator insert(iterator __pos, const value_type& __x)
#endif
  { return reinterpret_cast<iterator>(_M_impl.insert(reinterpret_cast<_StorageType*>(__pos),
                                                         reinterpret_cast<_StorageType const&>(__x))); }

  void swap(_Self& __x) { _M_impl.swap(__x._M_impl); }

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last)
  { _M_impl.insert(reinterpret_cast<_StorageType*>(__pos), __first, __last); }

  void insert (iterator __pos, size_type __n, const value_type& __x) {
    _M_impl.insert(reinterpret_cast<_StorageType*>(__pos), __n, reinterpret_cast<_StorageType const&>(__x));
  }

  void pop_back() {_M_impl.pop_back();}
  iterator erase(iterator __pos)
  {return reinterpret_cast<iterator>(_M_impl.erase(reinterpret_cast<_StorageType*>(__pos)));}
  iterator erase(iterator __first, iterator __last) {
    return reinterpret_cast<iterator>(_M_impl.erase(reinterpret_cast<_StorageType*>(__first),
                                                        reinterpret_cast<_StorageType*>(__last)));
  }

  void resize(size_type __new_size, const value_type& __x = value_type())
  { _M_impl.resize(__new_size, reinterpret_cast<_StorageType const&>(__x)); }

  void clear() { _M_impl.clear(); }

private:
  _Base _M_impl;
};

}

#if defined (vector)
#  undef vector
#endif

#undef VECTOR_IMPL

#endif /* _STLP_SPECIALIZED_VECTOR_H */
