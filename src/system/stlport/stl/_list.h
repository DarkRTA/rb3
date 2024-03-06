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

#ifndef _STLP_INTERNAL_LIST_IMPL_H
#define _STLP_INTERNAL_LIST_IMPL_H

#ifndef _STLP_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
#endif

#ifndef _STLP_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
#endif

#ifndef _STLP_INTERNAL_CONSTRUCT_H
#  include <stl/_construct.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_BASE_H
#  include <stl/_function_base.h>
#endif

namespace _STLP_PRIV {

struct _List_node_base {
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};

template <class _Dummy>
class _List_global {
public:
  typedef _List_node_base _Node_base;
  static void  _Transfer(_Node_base* __pos,
                                    _Node_base* __first, _Node_base* __last);
};

typedef _List_global<bool> _List_global_inst;

template <class _Tp>
class _List_node : public _List_node_base {
public:
  _Tp _M_data;
};

struct _List_iterator_base {
  typedef size_t                     size_type;
  typedef ptrdiff_t                  difference_type;
  typedef bidirectional_iterator_tag iterator_category;

  _List_node_base* _M_node;

  _List_iterator_base(_List_node_base* __x) : _M_node(__x) {}

  void _M_incr() { _M_node = _M_node->_M_next; }
  void _M_decr() { _M_node = _M_node->_M_prev; }
};


template<class _Tp, class _Traits>
struct _List_iterator : public _List_iterator_base {
  typedef _Tp value_type;
  typedef typename _Traits::pointer    pointer;
  typedef typename _Traits::reference  reference;

  typedef _List_iterator<_Tp, _Traits>         _Self;
  typedef typename _Traits::_NonConstTraits    _NonConstTraits;
  typedef _List_iterator<_Tp, _NonConstTraits> iterator;
  typedef typename _Traits::_ConstTraits       _ConstTraits;
  typedef _List_iterator<_Tp, _ConstTraits>    const_iterator;

  typedef bidirectional_iterator_tag iterator_category;
  typedef _List_node<_Tp> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  explicit _List_iterator(_List_node_base* __x) : _List_iterator_base(__x) {}
  _List_iterator() : _List_iterator_base(0) {}
  //copy constructor for iterator and constructor from iterator for const_iterator
  _List_iterator(const iterator& __x) :  _List_iterator_base(__x._M_node) {}

  reference operator*() const { return static_cast<_Node*>(this->_M_node)->_M_data; }
  pointer operator->() const { return &(operator*()); }

  _Self& operator++() {
    this->_M_incr();
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    this->_M_incr();
    return __tmp;
  }
  _Self& operator--() {
    this->_M_decr();
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    this->_M_decr();
    return __tmp;
  }
  bool operator==(const_iterator __y ) const {
    return this->_M_node == __y._M_node;
  }
  bool operator!=(const_iterator __y ) const {
    return this->_M_node != __y._M_node;
  }
};

}

namespace _STLP_STD {
template <class _Tp, class _Traits>
struct __type_traits<_STLP_PRIV::_List_iterator<_Tp, _Traits> > {
  typedef __false_type   has_trivial_default_constructor;
  typedef __true_type    has_trivial_copy_constructor;
  typedef __true_type    has_trivial_assignment_operator;
  typedef __true_type    has_trivial_destructor;
  typedef __false_type   is_POD_type;
};
}

namespace _STLP_PRIV {

// Base class that encapsulates details of allocators and helps
// to simplify EH

template <class _Tp, class _Alloc>
class _List_base {
protected:
  typedef _List_node_base _Node_base;
  typedef _List_node<_Tp> _Node;
  typedef _List_base<_Tp, _Alloc> _Self;
  typedef typename _Alloc_traits<_Node, _Alloc>::allocator_type _Node_allocator_type;
public:
  typedef _STLP_alloc_proxy<_Node_base, _Node, _Node_allocator_type> _AllocProxy;
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const
  { return (const _Node_allocator_type&)_M_node; }

  _List_base(const allocator_type& __a) : _M_node(_STLP_CONVERT_ALLOCATOR(__a, allocator_type, _Node), _Node_base())
  { _M_empty_initialize(); }
  _List_base(__move_source<_Self> src) :
    _M_node(__move_source<_AllocProxy>(src.get()._M_node)) {
    if (src.get().empty())
      //We force this to empty.
      _M_empty_initialize();
    else {
      src.get()._M_empty_initialize();
      _M_node._M_data._M_prev->_M_next = _M_node._M_data._M_next->_M_prev = &_M_node._M_data;
    }
  }

  ~_List_base()
  { clear(); }

  void clear();
  bool empty() const { return _M_node._M_data._M_next == &_M_node._M_data; }

  void _M_empty_initialize() {
    _M_node._M_data._M_next = &_M_node._M_data;
    _M_node._M_data._M_prev = _M_node._M_data._M_next;
  }

public:
  _AllocProxy _M_node;
};

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  define list _STLP_PTR_IMPL_NAME(List)
#elif defined (_STLP_DEBUG)
#  define list _STLP_NON_DBG_NAME(list)
#else
}

namespace _STLP_STD {
#endif

template <class _Tp, class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Tp) >
class list;

#if !defined (list)
}

namespace _STLP_PRIV {
#endif

// helper functions to reduce code duplication
template <class _Tp, class _Alloc, class _Predicate>
void _S_remove_if(list<_Tp, _Alloc>& __that, _Predicate __pred);

template <class _Tp, class _Alloc, class _BinaryPredicate>
void _S_unique(list<_Tp, _Alloc>& __that, _BinaryPredicate __binary_pred);

template <class _Tp, class _Alloc, class _StrictWeakOrdering>
void _S_merge(list<_Tp, _Alloc>& __that, list<_Tp, _Alloc>& __x,
              _StrictWeakOrdering __comp);

template <class _Tp, class _Alloc, class _StrictWeakOrdering>
void _S_sort(list<_Tp, _Alloc>& __that, _StrictWeakOrdering __comp);

#if !defined (list)
}

namespace _STLP_STD {
#endif

template <class _Tp, class _Alloc>
class list : public _STLP_PRIV::_List_base<_Tp, _Alloc>
{
  typedef _STLP_PRIV::_List_base<_Tp, _Alloc> _Base;
  typedef list<_Tp, _Alloc> _Self;
  typedef _STLP_PRIV::_List_node<_Tp> _Node;
  typedef _STLP_PRIV::_List_node_base _Node_base;
public:
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef typename _Base::allocator_type allocator_type;
  typedef bidirectional_iterator_tag _Iterator_category;

public:
  typedef _STLP_PRIV::_List_iterator<_Tp, _Nonconst_traits<_Tp> > iterator;
  typedef _STLP_PRIV::_List_iterator<_Tp, _Const_traits<_Tp> >    const_iterator;
  _STLP_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS;

protected:
  _Node_base* _M_create_node(const_reference __x = value_type()) {
    _Node* __p = this->_M_node.allocate(1);
    _STLP_TRY {
      _Copy_Construct(&__p->_M_data, __x);
    }
    _STLP_UNWIND(this->_M_node.deallocate(__p, 1))
    return __p;
  }

public:
  explicit list(size_type __n, const_reference __val = value_type(),
                const allocator_type& __a = allocator_type())
    : _STLP_PRIV::_List_base<_Tp, _Alloc>(__a)
    { this->insert(begin(), __n, __val); }

  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a = allocator_type())
    : _STLP_PRIV::_List_base<_Tp, _Alloc>(__a)
  { _M_insert(begin(), __first, __last); }

  explicit list(const allocator_type& __a = allocator_type())
    : _STLP_PRIV::_List_base<_Tp, _Alloc>(__a) {}

  list(const _Self& __x) : _STLP_PRIV::_List_base<_Tp, _Alloc>(__x.get_allocator())
  { _M_insert(begin(), __x.begin(), __x.end()); }

  list(__move_source<_Self> src)
    : _STLP_PRIV::_List_base<_Tp, _Alloc>(__move_source<_Base>(src.get())) {}

  ~list() {}

  _Self& operator = (const _Self& __x);

  iterator begin()                      { return iterator(this->_M_node._M_data._M_next); }
  const_iterator begin() const          { return const_iterator(this->_M_node._M_data._M_next); }

  iterator end()                        { return iterator(&this->_M_node._M_data); }
  const_iterator end() const            { return const_iterator(const_cast<_Node_base*>(&this->_M_node._M_data)); }

  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

  size_type size() const {
    size_type __result = distance(begin(), end());
    return __result;
  }
  size_type max_size() const { return size_type(-1); }

  reference front()             { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back()              { return *(--end()); }
  const_reference back() const  { return *(--end()); }

private:
  void _M_swap_aux(_Self& __x) {
    __x._M_node._M_swap_alloc(this->_M_node);
    __x._M_node._M_data._M_next = this->_M_node._M_data._M_next;
    __x._M_node._M_data._M_next->_M_prev = &__x._M_node._M_data;
    __x._M_node._M_data._M_prev = this->_M_node._M_data._M_prev;
    __x._M_node._M_data._M_prev->_M_next = &__x._M_node._M_data;
    this->_M_empty_initialize();
  }

public:
  void swap(_Self& __x) {
    if (__x.empty()) {
      if (this->empty()) {
        return;
      }
      this->_M_swap_aux(__x);
    } else if (this->empty()) {
      __x._M_swap_aux(*this);
    } else {
      this->_M_node.swap(__x._M_node);
      _STLP_STD::swap(this->_M_node._M_data._M_prev->_M_next, __x._M_node._M_data._M_prev->_M_next);
      _STLP_STD::swap(this->_M_node._M_data._M_next->_M_prev, __x._M_node._M_data._M_next->_M_prev);
    }
  }

#if !defined(_STLP_NO_ANACHRONISMS)
  iterator insert(iterator __pos, const_reference __x = value_type()) {
#else
  iterator insert(iterator __pos, const_reference __x) {
#endif
    _Node_base* __tmp = _M_create_node(__x);
    _Node_base* __n = __pos._M_node;
    _Node_base* __p = __n->_M_prev;
    __tmp->_M_next = __n;
    __tmp->_M_prev = __p;
    __p->_M_next = __tmp;
    __n->_M_prev = __tmp;
    return iterator(__tmp);
  }

private:
  template <class _InputIterator>
  void _M_insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  // Check whether it's an integral type.  If so, it's not an iterator.
  template<class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_insert(__pos, __n, __x);
  }
  template <class _InputIter>
  void _M_insert_dispatch(iterator __pos, _InputIter __first, _InputIter __last,
                          const __false_type& /*_IsIntegral*/) {
    //We use a temporary list to avoid the auto reference troubles (infinite loop)
    for (; __first != __last; ++__first)
      insert(__pos, *__first);
  }

public:
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_splice_insert_dispatch(__pos, __first, __last, _Integral());
  }

private:
  // Check whether it's an integral type.  If so, it's not an iterator.
  template<class _Integer>
  void _M_splice_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_insert(__pos, __n, __x);
  }
  template <class _InputIter>
  void _M_splice_insert_dispatch(iterator __pos, _InputIter __first, _InputIter __last,
                          const __false_type& /*_IsIntegral*/) {
    //We use a temporary list to avoid the auto reference troubles (infinite loop)
    _Self __tmp(__first, __last, this->get_allocator());
    splice(__pos, __tmp);
  }

public:
  void insert(iterator __pos, size_type __n, const_reference __x)
  { _M_fill_insert(__pos, __n, __x); }

private:
  void _M_fill_insert(iterator __pos, size_type __n, const_reference __x) {
    for ( ; __n > 0; --__n)
      insert(__pos, __x);
  }

public:
  void push_front(const_reference __x) { insert(begin(), __x); }
  void push_back (const_reference __x) { insert(end(), __x); }

  iterator erase(iterator __pos) {
    _Node_base* __next_node = __pos._M_node->_M_next;
    _Node_base* __prev_node = __pos._M_node->_M_prev;
    _Node* __n = static_cast<_Node*>(__pos._M_node);
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    _STLP_STD::_Destroy(&__n->_M_data);
    this->_M_node.deallocate(__n, 1);
    return iterator(__next_node);
  }

  iterator erase(iterator __first, iterator __last) {
    while (__first != __last)
      erase(__first++);
    return __last;
  }

  void resize(size_type __new_size, const_reference __x = value_type());

  void pop_front() { erase(begin()); }
  void pop_back() {
    iterator __tmp = end();
    erase(--__tmp);
  }

public:
  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const_reference __val) { _M_fill_assign(__n, __val); }

  void _M_fill_assign(size_type __n, const_reference __val);

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _IsIntegral<_InputIterator>::_Ret _Integral;
    _M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val,
                          const __true_type& /*_IsIntegral*/) {
    _M_fill_assign(__n, __val);
  }

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first2, _InputIterator __last2,
                          const __false_type& /*_IsIntegral*/) {
    iterator __first1 = begin();
    iterator __last1 = end();
    for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
      *__first1 = *__first2;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }

public:
  void splice(iterator __pos, _Self& __x) {
    if (!__x.empty()) {
      if (this->get_allocator() == __x.get_allocator()) {
        _STLP_PRIV::_List_global_inst::_Transfer(__pos._M_node, __x.begin()._M_node, __x.end()._M_node);
      }
      else {
        insert(__pos, __x.begin(), __x.end());
        __x.clear();
      }
    }
  }
  void splice(iterator __pos, _Self& __x, iterator __i) {
    iterator __j = __i;
    ++__j;
    if (__pos == __i || __pos == __j) return;
    if (this->get_allocator() == __x.get_allocator()) {
      _STLP_PRIV::_List_global_inst::_Transfer(__pos._M_node, __i._M_node, __j._M_node);
    }
    else {
      insert(__pos, *__i);
      __x.erase(__i);
    }
  }
  void splice(iterator __pos, _Self& __x, iterator __first, iterator __last) {
    if (__first != __last) {
      if (this->get_allocator() == __x.get_allocator()) {
        _STLP_PRIV::_List_global_inst::_Transfer(__pos._M_node, __first._M_node, __last._M_node);
      }
      else {
        insert(__pos, __first, __last);
        __x.erase(__first, __last);
      }
    }
  }

  void remove(const_reference __val) {
    iterator __first = begin();
    iterator __last = end();
    while (__first != __last) {
      iterator __next = __first;
      ++__next;
      if (__val == *__first) erase(__first);
      __first = __next;
    }
  }

  void unique()
  { _STLP_PRIV::_S_unique(*this, equal_to<value_type>()); }

  void merge(_Self& __x)
  { _STLP_PRIV::_S_merge(*this, __x, less<value_type>()); }

  void reverse() {
    _Node_base* __p = &this->_M_node._M_data;
    _Node_base* __tmp = __p;
    do {
      _STLP_STD::swap(__tmp->_M_next, __tmp->_M_prev);
      __tmp = __tmp->_M_prev;     // Old next node is now prev.
    } while (__tmp != __p);
  }

  void sort()
  { _STLP_PRIV::_S_sort(*this, less<value_type>()); }

  template <class _Predicate>
  void remove_if(_Predicate __pred)
  { _STLP_PRIV::_S_remove_if(*this, __pred); }
  template <class _BinaryPredicate>
  void unique(_BinaryPredicate __binary_pred)
  { _STLP_PRIV::_S_unique(*this, __binary_pred); }

  template <class _StrictWeakOrdering>
  void merge(_Self& __x,
             _StrictWeakOrdering __comp) {
    _STLP_PRIV::_S_merge(*this, __x, __comp);
  }

  template <class _StrictWeakOrdering>
  void sort(_StrictWeakOrdering __comp)
  { _STLP_PRIV::_S_sort(*this, __comp); }
};

}

#if defined (list)
#  undef list
#endif

#if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_list.c>
#endif

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  include <stl/pointers/_list.h>
#endif

#if defined (_STLP_DEBUG)
#  include <stl/debug/_list.h>
#endif

namespace _STLP_STD {

template <class _Tp, class _Alloc>
inline bool
operator==(const list<_Tp,_Alloc>& __x, const list<_Tp,_Alloc>& __y) {
  typedef typename list<_Tp,_Alloc>::const_iterator const_iterator;
  const_iterator __end1 = __x.end();
  const_iterator __end2 = __y.end();

  const_iterator __i1 = __x.begin();
  const_iterator __i2 = __y.begin();
  while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2) {
    ++__i1;
    ++__i2;
  }
  return __i1 == __end1 && __i2 == __end2;
}

#define _STLP_EQUAL_OPERATOR_SPECIALIZED
#define _STLP_TEMPLATE_HEADER    template <class _Tp, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER list<_Tp, _Alloc>
#include <stl/_relops_cont.h>
#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER
#undef _STLP_EQUAL_OPERATOR_SPECIALIZED

template <class _Tp, class _Alloc>
struct __move_traits<list<_Tp, _Alloc> > {
  typedef __stlp_movable implemented;
  typedef typename __move_traits<_Alloc>::complete complete;
};

}

#endif /* _STLP_INTERNAL_LIST_IMPL_H */

// Local Variables:
// mode:C++
// End:
