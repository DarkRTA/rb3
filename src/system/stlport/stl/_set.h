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

#ifndef _STLP_INTERNAL_SET_H
#define _STLP_INTERNAL_SET_H

#ifndef _STLP_INTERNAL_TREE_H
#  include <stl/_tree.h>
#endif

#if !defined (_STLP_USE_PTR_SPECIALIZATIONS)

namespace _STLP_STD {

//Specific iterator traits creation
_STLP_CREATE_ITERATOR_TRAITS(SetTraitsT, Const_traits)

template <class _Key, class _Compare = less<_Key>,
                     class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Key) >
class set
{
  typedef set<_Key, _Compare, _Alloc> _Self;
public:
// typedefs:
  typedef _Key     key_type;
  typedef _Key     value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;

private:
  //Specific iterator traits creation
  typedef _STLP_PRIV_FORCE::_SetTraitsT<value_type> _SetTraits;

public:
  //Following typedef have to be public for __move_traits specialization.
  typedef _STLP_PRIV::_Rb_tree<key_type, key_compare,
                              value_type, _STLP_PRIV::_Identity<value_type>,
                              _SetTraits, _Alloc> _Rep_type;

  typedef typename _Rep_type::pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::reference reference;
  typedef typename _Rep_type::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::allocator_type allocator_type;

private:
  _Rep_type _M_t;  // red-black tree representing set
  _STLP_KEY_TYPE_FOR_CONT_EXT(key_type)

public:

  // allocation/deallocation
  explicit set(const _Compare& __comp = _Compare(),
               const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) {}

  template <class _InputIterator>
  set(_InputIterator __first, _InputIterator __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_unique(__first, __last); }

  template <class _InputIterator>
  set(_InputIterator __first, _InputIterator __last, const _Compare& __comp,
      const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_unique(__first, __last); }

  set(const _Self& __x) : _M_t(__x._M_t) {}

  set(__move_source<_Self> src)
    : _M_t(__move_source<_Rep_type>(src.get()._M_t)) {}

  _Self& operator=(const _Self& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  // accessors:
  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return _M_t.key_comp(); }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  iterator begin() { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator begin() const { return _M_t.begin(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(_Self& __x) { _M_t.swap(__x._M_t); }

  // insert/erase
  pair<iterator,bool> insert(const value_type& __x)
  { return _M_t.insert_unique(__x); }
  iterator insert(iterator __pos, const value_type& __x)
  { return _M_t.insert_unique( __pos , __x); }
  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last)
  { _M_t.insert_unique(__first, __last); }

  void erase(iterator __pos) { _M_t.erase( __pos ); }
  size_type erase(const key_type& __x) { return _M_t.erase_unique(__x); }
  void erase(iterator __first, iterator __last) { _M_t.erase(__first, __last ); }
  void clear() { _M_t.clear(); }

  // set operations:
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator find(const _KT& __x) const { return _M_t.find(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator find(const _KT& __x) { return _M_t.find(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type count(const _KT& __x) const
  { return _M_t.find(__x) == _M_t.end() ? 0 : 1 ; }
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator lower_bound(const _KT& __x) { return _M_t.lower_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator lower_bound(const _KT& __x) const { return _M_t.lower_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator upper_bound(const _KT& __x) { return _M_t.upper_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator upper_bound(const _KT& __x) const { return _M_t.upper_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<iterator, iterator> equal_range(const _KT& __x)
  { return _M_t.equal_range_unique(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<const_iterator, const_iterator> equal_range(const _KT& __x) const
  { return _M_t.equal_range_unique(__x); }
};

//Specific iterator traits creation
_STLP_CREATE_ITERATOR_TRAITS(MultisetTraitsT, Const_traits)

template <class _Key, class _Compare = less<_Key>,
          class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Key) >
class multiset
{
  typedef multiset<_Key, _Compare, _Alloc> _Self;
public:
  // typedefs:

  typedef _Key     key_type;
  typedef _Key     value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;

private:
  //Specific iterator traits creation
  typedef _STLP_PRIV_FORCE::_MultisetTraitsT<value_type> _MultisetTraits;

public:
  //Following typedef have to be public for __move_traits specialization.
  typedef _STLP_PRIV::_Rb_tree<key_type, key_compare,
                              value_type, _STLP_PRIV::_Identity<value_type>,
                              _MultisetTraits, _Alloc> _Rep_type;

  typedef typename _Rep_type::pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::reference reference;
  typedef typename _Rep_type::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::allocator_type allocator_type;

private:
  _Rep_type _M_t;  // red-black tree representing multiset
  _STLP_KEY_TYPE_FOR_CONT_EXT(key_type)

public:
  explicit multiset(const _Compare& __comp = _Compare(),
                    const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) {}

  template <class _InputIterator>
  multiset(_InputIterator __first, _InputIterator __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_equal(__first, __last); }

  template <class _InputIterator>
  multiset(_InputIterator __first, _InputIterator __last,
           const _Compare& __comp,
           const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_equal(__first, __last); }

  multiset(const _Self& __x) : _M_t(__x._M_t) {}
  _Self& operator=(const _Self& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  multiset(__move_source<_Self> src)
    : _M_t(__move_source<_Rep_type>(src.get()._M_t)) {}

  // accessors:
  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return _M_t.key_comp(); }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  iterator begin() { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator begin() const { return _M_t.begin(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(_Self& __x) { _M_t.swap(__x._M_t); }

  // insert/erase
  iterator insert(const value_type& __x)
  { return _M_t.insert_equal(__x); }
  iterator insert(iterator __pos, const value_type& __x)
  { return _M_t.insert_equal(__pos, __x); }

  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last)
  { _M_t.insert_equal(__first, __last); }
  void erase(iterator __pos) { _M_t.erase( __pos ); }
  size_type erase(const key_type& __x) { return _M_t.erase(__x); }
  void erase(iterator __first, iterator __last) { _M_t.erase( __first, __last ); }
  void clear() { _M_t.clear(); }

  // multiset operations:
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator find(const _KT& __x) { return _M_t.find(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator find(const _KT& __x) const { return _M_t.find(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type count(const _KT& __x) const { return _M_t.count(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator lower_bound(const _KT& __x) { return _M_t.lower_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator lower_bound(const _KT& __x) const { return _M_t.lower_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator upper_bound(const _KT& __x) { return _M_t.upper_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator upper_bound(const _KT& __x) const { return _M_t.upper_bound(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<iterator, iterator> equal_range(const _KT& __x) { return _M_t.equal_range(__x); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<const_iterator, const_iterator> equal_range(const _KT& __x) const { return _M_t.equal_range(__x); }
};

#else
#  include <stl/pointers/_set.h>
namespace _STLP_STD {
#endif /* _STLP_USE_PTR_SPECIALIZATIONS */

#define _STLP_TEMPLATE_HEADER template <class _Key, class _Compare, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER set<_Key,_Compare,_Alloc>
#include <stl/_relops_cont.h>
#undef  _STLP_TEMPLATE_CONTAINER
#define _STLP_TEMPLATE_CONTAINER multiset<_Key,_Compare,_Alloc>
#include <stl/_relops_cont.h>
#undef  _STLP_TEMPLATE_CONTAINER
#undef  _STLP_TEMPLATE_HEADER

template <class _Key, class _Compare, class _Alloc>
struct __move_traits<set<_Key,_Compare,_Alloc> > :
  _STLP_PRIV::__move_traits_aux<typename set<_Key,_Compare,_Alloc>::_Rep_type>
{};

template <class _Key, class _Compare, class _Alloc>
struct __move_traits<multiset<_Key,_Compare,_Alloc> > :
  _STLP_PRIV::__move_traits_aux<typename multiset<_Key,_Compare,_Alloc>::_Rep_type>
{};

}

#endif /* _STLP_INTERNAL_SET_H */

// Local Variables:
// mode:C++
// End:
