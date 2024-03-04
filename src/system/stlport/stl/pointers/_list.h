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

#ifndef _STLP_PTR_SPECIALIZED_LIST_H
#define _STLP_PTR_SPECIALIZED_LIST_H

#ifndef _STLP_POINTERS_SPEC_TOOLS_H
#  include <stl/pointers/_tools.h>
#endif

#define LIST_IMPL _STLP_PTR_IMPL_NAME(List)

#if defined (_STLP_DEBUG)
#  define list _STLP_NON_DBG_NAME(list)
namespace _STLP_PRIV {
#else
namespace _STLP_STD {
#endif

template <class _Tp, class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Tp) >
class list
{
  typedef typename _STLP_PRIV::_StorageType<_Tp>::_Type _StorageType;
  typedef typename _Alloc_traits<_StorageType, _Alloc>::allocator_type _StorageTypeAlloc;
  typedef _STLP_PRIV::LIST_IMPL<_StorageType, _StorageTypeAlloc> _Base;
  typedef typename _Base::iterator _BaseIte;
  typedef typename _Base::const_iterator _BaseConstIte;
  typedef _STLP_PRIV::_CastTraits<_StorageType, _Tp> cast_traits;
  typedef list<_Tp, _Alloc> _Self;

public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef typename _Alloc_traits<value_type, _Alloc>::allocator_type allocator_type;
  typedef bidirectional_iterator_tag _Iterator_category;

  typedef _STLP_PRIV::_List_iterator<value_type, _Nonconst_traits<value_type> > iterator;
  typedef _STLP_PRIV::_List_iterator<value_type, _Const_traits<value_type> >    const_iterator;

  _STLP_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

  allocator_type get_allocator() const
  { return _M_impl.get_allocator(); }

  explicit list(const allocator_type& __a = allocator_type())
    : _M_impl(__a) {}

  explicit list(size_type __n, const value_type& __val = value_type(),
       const allocator_type& __a = allocator_type())
    : _M_impl(__n, cast_traits::to_storage_type_cref(__val),
              __a) {}

  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a = allocator_type())
#  if !defined (_STLP_USE_ITERATOR_WRAPPER)
    : _M_impl(__first, __last, __a) {}
#  else
    : _M_impl(__a) {
    insert(begin(), __first, __last);
  }
#  endif

  list(const _Self& __x) : _M_impl(__x._M_impl) {}

  list(__move_source<_Self> src)
    : _M_impl(__move_source<_Base>(src.get()._M_impl)) {}

  iterator begin()             { return iterator(_M_impl.begin()._M_node); }
  const_iterator begin() const { return const_iterator(_M_impl.begin()._M_node); }

  iterator end()               { return iterator(_M_impl.end()._M_node); }
  const_iterator end() const   { return const_iterator(_M_impl.end()._M_node); }

  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

  bool empty() const         { return _M_impl.empty(); }
  size_type size() const     { return _M_impl.size(); }
  size_type max_size() const { return _M_impl.max_size(); }

  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back()              { return *(--end()); }
  const_reference back() const  { return *(--end()); }

  void swap(_Self &__x) { _M_impl.swap(__x._M_impl); }
  void clear() { _M_impl.clear(); }

#if !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const_reference __x = value_type())
#else
  iterator insert(iterator __pos, const_reference __x)
#endif
  { return iterator(_M_impl.insert(_BaseIte(__pos._M_node),
                                   cast_traits::to_storage_type_cref(__x))._M_node); }

#  if defined (_STLP_USE_ITERATOR_WRAPPER)
private:
  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                          const __true_type&)
  { _M_impl.insert(_BaseIte(__pos._M_node), __n, __val); }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          const __false_type&) {
    _M_impl.insert(_BaseIte(__pos._M_node),
                   typename _STLP_PRIV::_IteWrapper<_StorageType, _Tp, _InputIterator>::_Ite(__first),
                   typename _STLP_PRIV::_IteWrapper<_StorageType, _Tp, _InputIterator>::_Ite(__last));
  }

public:
#  endif

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
#  if defined (_STLP_USE_ITERATOR_WRAPPER)
    // Check whether it's an integral type.  If so, it's not an iterator.
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
#  else
    _M_impl.insert(_BaseIte(__pos._M_node), __first, __last);
#  endif
  }

  void insert(iterator __pos, size_type __n, const value_type& __x)
  { _M_impl.insert(_BaseIte(__pos._M_node), __n, cast_traits::to_storage_type_cref(__x)); }

  void push_front(const value_type& __x) { _M_impl.push_front(cast_traits::to_storage_type_cref(__x)); }
  void push_back(const value_type& __x)  { _M_impl.push_back(cast_traits::to_storage_type_cref(__x)); }

  iterator erase(iterator __pos)
  { return iterator(_M_impl.erase(_BaseIte(__pos._M_node))._M_node); }
  iterator erase(iterator __first, iterator __last)
  { return iterator(_M_impl.erase(_BaseIte(__first._M_node), _BaseIte(__last._M_node))._M_node); }

  void resize(size_type __new_size, const value_type& __x = value_type())
  {_M_impl.resize(__new_size, cast_traits::to_storage_type_cref(__x));}

  void pop_front() { _M_impl.pop_front(); }
  void pop_back()  { _M_impl.pop_back(); }

  _Self& operator=(const _Self& __x)
  { _M_impl = __x._M_impl; return *this; }
  void assign(size_type __n, const value_type& __val)
  { _M_impl.assign(__n, cast_traits::to_storage_type_cref(__val)); }

#  if defined (_STLP_USE_ITERATOR_WRAPPER)
private:
  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, const __true_type&)
  { _M_impl.assign(__n, __val); }

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
                          const __false_type&) {
    _M_impl.assign(typename _STLP_PRIV::_IteWrapper<_StorageType, _Tp, _InputIterator>::_Ite(__first),
                   typename _STLP_PRIV::_IteWrapper<_StorageType, _Tp, _InputIterator>::_Ite(__last));
  }

public:
#  endif

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
#  if defined (_STLP_USE_ITERATOR_WRAPPER)
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
#  else
    _M_impl.assign(__first, __last);
#  endif
  }

  void splice(iterator __pos, _Self& __x)
  { _M_impl.splice(_BaseIte(__pos._M_node), __x._M_impl); }
  void splice(iterator __pos, _Self& __x, iterator __i)
  { _M_impl.splice(_BaseIte(__pos._M_node), __x._M_impl, _BaseIte(__i._M_node)); }
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last)
  { _M_impl.splice(_BaseIte(__pos._M_node), __x._M_impl,
                   _BaseIte(__first._M_node), _BaseIte(__last._M_node)); }

  void remove(const_reference __val)
  { _M_impl.remove(cast_traits::to_storage_type_cref(__val)); }
  void unique() { _M_impl.unique(); }
  void merge(_Self& __x) { _M_impl.merge(__x._M_impl); }
  void reverse() { _M_impl.reverse(); }
  void sort() { _M_impl.sort(); }

  template <class _Predicate>
  void remove_if(_Predicate __pred)
  { _M_impl.remove_if(_STLP_PRIV::_UnaryPredWrapper<_StorageType, _Tp, _Predicate>(__pred)); }
  template <class _BinaryPredicate>
  void unique(_BinaryPredicate __bin_pred)
  { _M_impl.unique(_STLP_PRIV::_BinaryPredWrapper<_StorageType, _Tp, _BinaryPredicate>(__bin_pred)); }

  template <class _StrictWeakOrdering>
  void merge(_Self &__x, _StrictWeakOrdering __comp)
  { _M_impl.merge(__x._M_impl, _STLP_PRIV::_BinaryPredWrapper<_StorageType, _Tp, _StrictWeakOrdering>(__comp)); }

  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp)
  { _M_impl.sort(_STLP_PRIV::_BinaryPredWrapper<_StorageType, _Tp, _StrictWeakOrdering>(__comp)); }

private:
  _Base _M_impl;
};

}

#if defined (list)
#  undef list
#endif

#undef LIST_IMPL

#endif /* _STLP_PTR_SPECIALIZED_LIST_H */

// Local Variables:
// mode:C++
// End:
