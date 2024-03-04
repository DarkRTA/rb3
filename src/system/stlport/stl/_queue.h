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

#ifndef _STLP_INTERNAL_QUEUE_H
#define _STLP_INTERNAL_QUEUE_H

#ifndef _STLP_INTERNAL_DEQUE_H
#  include <stl/_deque.h>
#endif

#ifndef _STLP_INTERNAL_VECTOR_H
# include <stl/_vector.h>
#endif

#ifndef _STLP_INTERNAL_HEAP_H
#  include <stl/_heap.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_BASE_H
#  include <stl/_function_base.h>
#endif

namespace _STLP_STD {

template <class _Tp, class _Sequence = deque<_Tp> >
class queue
{
  typedef queue<_Tp, _Sequence> _Self;

public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;

protected:
  //c is a Standard name (23.2.3.1), do no make it STLport naming convention compliant.
  _Sequence c;
public:
  queue() : c() {}
  explicit queue(const _Sequence& __c) : c(__c) {}

  queue(__move_source<_Self> src)
    : c(_STLP_PRIV::_AsMoveSource(src.get().c)) {}

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  void push(const value_type& __x) { c.push_back(__x); }
  void pop() { c.pop_front(); }
  const _Sequence& _Get_s() const { return c; }
};

template <class _Tp, class _Sequence>
inline bool
operator==(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y) {
  return __x._Get_s() == __y._Get_s();
}

template <class _Tp, class _Sequence>
inline bool
operator<(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y) {
  return __x._Get_s() < __y._Get_s();
}

_STLP_RELOPS_OPERATORS( template <class _Tp, class _Sequence>, queue<_Tp, _Sequence> )

template <class _Tp, class _Sequence = vector<_Tp>,
          class _Compare = less<typename _Sequence::value_type> >
class priority_queue
{
  typedef priority_queue<_Tp, _Sequence, _Compare> _Self;

public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  //c is a Standard name (23.2.3.2), do no make it STLport naming convention compliant.
  _Sequence c;
  _Compare comp;
public:
  priority_queue() : c() {}
  explicit priority_queue(const _Compare& __x) :  c(), comp(__x) {}
  priority_queue(const _Compare& __x, const _Sequence& __s)
    : c(__s), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

  priority_queue(__move_source<_Self> src)
    : c(_STLP_PRIV::_AsMoveSource(src.get().c)),
      comp(_STLP_PRIV::_AsMoveSource(src.get().comp)) {}

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last)
    : c(__first, __last) { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first,
                 _InputIterator __last, const _Compare& __x)
    : c(__first, __last), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last,
                 const _Compare& __x, const _Sequence& __s)
  : c(__s), comp(__x)
  {
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), comp);
  }

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& __x) {
    _STLP_TRY {
      c.push_back(__x);
      push_heap(c.begin(), c.end(), comp);
    }
    _STLP_UNWIND(c.clear())
  }
  void pop() {
    _STLP_TRY {
      pop_heap(c.begin(), c.end(), comp);
      c.pop_back();
    }
    _STLP_UNWIND(c.clear())
  }
};

template <class _Tp, class _Sequence>
struct __move_traits<queue<_Tp, _Sequence> > :
  _STLP_PRIV::__move_traits_aux<_Sequence>
{};

template <class _Tp, class _Sequence, class _Compare>
struct __move_traits<priority_queue<_Tp, _Sequence, _Compare> > :
  _STLP_PRIV::__move_traits_aux2<_Sequence, _Compare>
{};

}

#undef comp

#endif /* _STLP_INTERNAL_QUEUE_H */

// Local Variables:
// mode:C++
// End:
