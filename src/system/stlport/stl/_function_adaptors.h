/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996-1998
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * Copyright (c) 2000
 * Pavel Kuznetsov
 *
 * Copyright (c) 2001
 * Meridian'93
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

// This file has noo macro protection as it is meant to be included several times
// from other header.
// Adaptor function objects: pointers to member functions.

// There are a total of 16 = 2^4 function objects in this family.
//  (1) Member functions taking no arguments vs member functions taking
//       one argument.
//  (2) Call through pointer vs call through reference.
//  (3) Member function with void return type vs member function with
//      non-void return type.
//  (4) Const vs non-const member function.

// Note that choice (3) is nothing more than a workaround: according
//  to the draft, compilers should handle void and non-void the same way.
//  This feature is not yet widely implemented, though.  You can only use
//  member functions returning void if your compiler supports partial
//  specialization.

// All of this complexity is in the function objects themselves.  You can
//  ignore it by using the helper function mem_fun and mem_fun_ref,
//  which create whichever type of adaptor is appropriate.

namespace _STLP_STD {

template <class _Ret, class _Tp>
class mem_fun_t : public unary_function<_Tp*,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(void);
public:
  explicit mem_fun_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(_Tp* __p) const { return (__p->*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp>
class const_mem_fun_t : public unary_function<const _Tp*,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(void) const;
public:
  explicit const_mem_fun_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(const _Tp* __p) const { return (__p->*_M_f)(); }
private:
  __fun_type _M_f;
};


template <class _Ret, class _Tp>
class mem_fun_ref_t : public unary_function<_Tp,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(void);
public:
  explicit mem_fun_ref_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(_Tp& __r) const { return (__r.*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp>
class const_mem_fun_ref_t : public unary_function<_Tp,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(void) const;
public:
  explicit const_mem_fun_ref_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(const _Tp& __r) const { return (__r.*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp, class _Arg>
class mem_fun1_t : public binary_function<_Tp*,_Arg,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(_Arg);
public:
  explicit mem_fun1_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(_Tp* __p, _Arg __x) const { return (__p->*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp, class _Arg>
class const_mem_fun1_t : public binary_function<const _Tp*,_Arg,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(_Arg) const;
public:
  explicit const_mem_fun1_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(const _Tp* __p, _Arg __x) const
    { return (__p->*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp, class _Arg>
class mem_fun1_ref_t : public binary_function<_Tp,_Arg,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(_Arg);
public:
  explicit mem_fun1_ref_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(_Tp& __r, _Arg __x) const { return (__r.*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Ret, class _Tp, class _Arg>
class const_mem_fun1_ref_t : public binary_function<_Tp,_Arg,_Ret> {
  typedef _Ret (_Tp::*__fun_type)(_Arg) const;
public:
  explicit const_mem_fun1_ref_t(__fun_type __pf) : _M_f(__pf) {}
  _Ret operator()(const _Tp& __r, _Arg __x) const { return (__r.*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Arg, class _Result>
class pointer_to_unary_function : public unary_function<_Arg, _Result> {
protected:
  _Result (*_M_ptr)(_Arg);
public:
  pointer_to_unary_function() {}
  explicit pointer_to_unary_function(_Result (*__x)(_Arg)) : _M_ptr(__x) {}
  _Result operator()(_Arg __x) const { return _M_ptr(__x); }
};

template <class _Arg1, class _Arg2, class _Result>
class pointer_to_binary_function :
  public binary_function<_Arg1,_Arg2,_Result> {
protected:
    _Result (*_M_ptr)(_Arg1, _Arg2);
public:
    pointer_to_binary_function() {}
    explicit pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) {}
    _Result operator()(_Arg1 __x, _Arg2 __y) const {
      return _M_ptr(__x, __y);
    }
};


#if defined(_STLP_DONT_RETURN_VOID)
//Partial specialization for the void type
template <class _Tp>
class mem_fun_t<void, _Tp> : public unary_function<_Tp*,void> {
  typedef void (_Tp::*__fun_type)(void);
public:
  explicit mem_fun_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(_Tp* __p) const { (__p->*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Tp>
class const_mem_fun_t<void, _Tp> : public unary_function<const _Tp*,void> {
  typedef void (_Tp::*__fun_type)(void) const;
public:
  explicit const_mem_fun_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(const _Tp* __p) const { (__p->*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Tp>
class mem_fun_ref_t<void, _Tp> : public unary_function<_Tp,void> {
  typedef void (_Tp::*__fun_type)(void);
public:
  explicit mem_fun_ref_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(_Tp& __r) const { (__r.*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Tp>
class const_mem_fun_ref_t<void, _Tp> : public unary_function<_Tp,void> {
  typedef void (_Tp::*__fun_type)(void) const;
public:
  explicit const_mem_fun_ref_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(const _Tp& __r) const { (__r.*_M_f)(); }
private:
  __fun_type _M_f;
};

template <class _Tp, class _Arg>
class mem_fun1_t<void, _Tp, _Arg> : public binary_function<_Tp*,_Arg,void> {
  typedef void (_Tp::*__fun_type)(_Arg);
public:
  explicit mem_fun1_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(_Tp* __p, _Arg __x) const { (__p->*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Tp, class _Arg>
class const_mem_fun1_t<void, _Tp, _Arg>
  : public binary_function<const _Tp*,_Arg,void> {
  typedef void (_Tp::*__fun_type)(_Arg) const;
public:
  explicit const_mem_fun1_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(const _Tp* __p, _Arg __x) const { (__p->*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Tp, class _Arg>
class mem_fun1_ref_t<void, _Tp, _Arg>
  : public binary_function<_Tp,_Arg,void> {
  typedef void (_Tp::*__fun_type)(_Arg);
public:
  explicit mem_fun1_ref_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(_Tp& __r, _Arg __x) const { (__r.*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Tp, class _Arg>
class const_mem_fun1_ref_t<void, _Tp, _Arg>
  : public binary_function<_Tp,_Arg,void> {
  typedef void (_Tp::*__fun_type)(_Arg) const;
public:
  explicit const_mem_fun1_ref_t (__fun_type __pf) : _M_f(__pf) {}
  void operator()(const _Tp& __r, _Arg __x) const { (__r.*_M_f)(__x); }
private:
  __fun_type _M_f;
};

template <class _Arg>
class pointer_to_unary_function<_Arg, void> : public unary_function<_Arg, void> {
  typedef void (*__fun_type)(_Arg);
  __fun_type _M_ptr;
public:
  pointer_to_unary_function() {}
  explicit pointer_to_unary_function(__fun_type __x) : _M_ptr(__x) {}
  void operator()(_Arg __x) const { _M_ptr(__x); }
};

template <class _Arg1, class _Arg2>
class pointer_to_binary_function<_Arg1, _Arg2, void> : public binary_function<_Arg1,_Arg2,void> {
  typedef void (*__fun_type)(_Arg1, _Arg2);
  __fun_type _M_ptr;
public:
  pointer_to_binary_function() {}
  explicit pointer_to_binary_function(__fun_type __x) : _M_ptr(__x) {}
  void operator()(_Arg1 __x, _Arg2 __y) const { _M_ptr(__x, __y); }
};

#endif /*_STLP_DONT_RETURN_VOID*/

// Mem_fun adaptor helper functions.  There are only two:
//  mem_fun and mem_fun_ref.  (mem_fun1 and mem_fun1_ref
//  are provided for backward compatibility, but they are no longer
//  part of the C++ standard.)

template <class _Result, class _Tp>
inline mem_fun_t<_Result,_Tp>
mem_fun(_Result (_Tp::*__f)()) { return mem_fun_t<_Result,_Tp>(__f); }

template <class _Result, class _Tp>
inline const_mem_fun_t<_Result,_Tp>
mem_fun(_Result (_Tp::*__f)() const)  { return const_mem_fun_t<_Result,_Tp>(__f); }

template <class _Result, class _Tp>
inline mem_fun_ref_t<_Result,_Tp>
mem_fun_ref(_Result (_Tp::*__f)())  { return mem_fun_ref_t<_Result,_Tp>(__f); }

template <class _Result, class _Tp>
inline const_mem_fun_ref_t<_Result,_Tp>
mem_fun_ref(_Result (_Tp::*__f)() const)  { return const_mem_fun_ref_t<_Result,_Tp>(__f); }

template <class _Result, class _Tp, class _Arg>
inline mem_fun1_t<_Result,_Tp,_Arg>
mem_fun(_Result (_Tp::*__f)(_Arg)) { return mem_fun1_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline const_mem_fun1_t<_Result,_Tp,_Arg>
mem_fun(_Result (_Tp::*__f)(_Arg) const) { return const_mem_fun1_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline mem_fun1_ref_t<_Result,_Tp,_Arg>
mem_fun_ref(_Result (_Tp::*__f)(_Arg)) { return mem_fun1_ref_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline const_mem_fun1_ref_t<_Result,_Tp,_Arg>
mem_fun_ref(_Result (_Tp::*__f)(_Arg) const) { return const_mem_fun1_ref_t<_Result,_Tp,_Arg>(__f); }

# if !(defined (_STLP_NO_EXTENSIONS) || defined (_STLP_NO_ANACHRONISMS))
//  mem_fun1 and mem_fun1_ref are no longer part of the C++ standard,
//  but they are provided for backward compatibility.
template <class _Result, class _Tp, class _Arg>
inline mem_fun1_t<_Result,_Tp,_Arg>
mem_fun1(_Result (_Tp::*__f)(_Arg)) { return mem_fun1_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline const_mem_fun1_t<_Result,_Tp,_Arg>
mem_fun1(_Result (_Tp::*__f)(_Arg) const) { return const_mem_fun1_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline mem_fun1_ref_t<_Result,_Tp,_Arg>
mem_fun1_ref(_Result (_Tp::*__f)(_Arg)) { return mem_fun1_ref_t<_Result,_Tp,_Arg>(__f); }

template <class _Result, class _Tp, class _Arg>
inline const_mem_fun1_ref_t<_Result,_Tp,_Arg>
mem_fun1_ref(_Result (_Tp::*__f)(_Arg) const) { return const_mem_fun1_ref_t<_Result,_Tp,_Arg>(__f); }

# endif /* _STLP_NO_EXTENSIONS */

template <class _Arg, class _Result>
inline pointer_to_unary_function<_Arg, _Result>
ptr_fun(_Result (*__f)(_Arg))
{ return pointer_to_unary_function<_Arg, _Result>(__f); }

template <class _Arg1, class _Arg2, class _Result>
inline pointer_to_binary_function<_Arg1,_Arg2,_Result>
ptr_fun(_Result (*__f)(_Arg1, _Arg2))
{ return pointer_to_binary_function<_Arg1,_Arg2,_Result>(__f); }

}
