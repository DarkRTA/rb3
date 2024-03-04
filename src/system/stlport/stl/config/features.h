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

#ifndef _STLP_FEATURES_H
#define _STLP_FEATURES_H

/*
 * Purpose of this file:
 *
 * Defines all STLport settings.
 * This file is actually a wrapper : it includes compiler-specific
 * settings from <config/stlcomp.h>
 * and user-defined settings from <config/user_config.h>.
 * See <config/stl_mycomp.h> and <config/user_config.h> for the description
 * of those macros
 *
 */

/* Definition of the STLport version informations */
#include <stl/_stlport_version.h>

/* Other macros defined by this file:

 * namespace-related macros (_STLP_STD, _STLP_PRIV, etc.)
 * exception-related macros (_STLP_TRY, _STLP_UNWIND, etc.)
 * _STLP_ASSERT, either as a test or as a null macro, depending on
   whether or not _STLP_ASSERTIONS is defined.
*/

/* Definition of the 2 STLport debug levels */
#define _STLP_STLPORT_DBG_LEVEL 1
#define _STLP_STANDARD_DBG_LEVEL 2

/* Placeholder for user to override settings.
 * It could be also used to mask settings from
 * different directories.
 */
#include <stl/config/user_config.h>

#if defined (_STLP_DEBUG) && !defined (_STLP_DEBUG_LEVEL)
#  define _STLP_DEBUG_LEVEL _STLP_STLPORT_DBG_LEVEL
#endif

#if defined (__BUILDING_STLPORT)
/* For the STLport implementation we can use everything:
 */
#  if defined (_STLP_NO_ANACHRONISMS)
#    undef _STLP_NO_ANACHRONISMS
#  endif
#  if defined (_STLP_NO_EXTENSIONS)
#    undef _STLP_NO_EXTENSIONS
#  endif
/* Moreover there are things that has no sens:
 */
#  if defined (_STLP_NO_IOSTREAMS)
#    error If you do not use iostreams you do not need to build the STLport library.
#  endif
#endif

/* ========================================================= */
/* Common configuration file for this particular installation. */
#include <stl/config/host.h>

/* Operational Environment specific */
#include <stl/config/_system.h>

/* ========================================================= */

#ifdef _STLP_USE_BOOST_SUPPORT
/* We are going to use the boost library support. To limit the problem
 * of self referencing headers we have to specify clearly to the boost
 * library that the Standard lib is STLport:
 */
#  ifndef BOOST_STDLIB_CONFIG
#    define BOOST_STDLIB_CONFIG <boost/config/stdlib/stlport.hpp>
#  endif
#endif


/*
 * Performs integrity check on user-specified parameters
 * and site-specific settings.
 */
/*
# include <stl/_check_config.h>
*/

/* SGI terms */

#if !defined (_STLP_DONT_USE_SHORT_STRING_OPTIM) && !defined (_STLP_USE_SHORT_STRING_OPTIM)
#  define _STLP_USE_SHORT_STRING_OPTIM 1
#endif

#if !defined (_STLP_NO_EXTENSIONS) && \
   !defined (_STLP_NO_CONTAINERS_EXTENSION) && !defined (_STLP_USE_CONTAINERS_EXTENSION)
#  define _STLP_USE_CONTAINERS_EXTENSION
#endif

#if defined (_STLP_USE_CONTAINERS_EXTENSION)
#  define _STLP_TEMPLATE_FOR_CONT_EXT template <class _KT>
#else
#  define _STLP_TEMPLATE_FOR_CONT_EXT
#endif

#if defined (_STLP_NO_IOSTREAMS) && \
   !defined (_STLP_USE_NEWALLOC) && !defined (_STLP_USE_MALLOC)
#  define _STLP_USE_NEWALLOC
#endif

#if !defined (_STLP_BIG_ENDIAN) && !defined (_STLP_LITTLE_ENDIAN)
#  if defined (_MIPSEB) || defined (__sparc) || defined (_AIX) || \
      defined (__hpux) || defined (macintosh) || defined (_MAC)
#    define _STLP_BIG_ENDIAN 1
#  elif defined (__i386) || defined (_M_IX86) || defined (_M_ARM) || \
        defined (__amd64__) || defined (_M_AMD64) || defined (__x86_64__) || \
        defined (__alpha__)
#    define _STLP_LITTLE_ENDIAN 1
#  elif defined (__ia64__)
    /* itanium allows both settings (for instance via gcc -mbig-endian) - hence a seperate check is required */
#    if defined (__BIG_ENDIAN__)
#      define _STLP_BIG_ENDIAN 1
#    else
#      define _STLP_LITTLE_ENDIAN 1
#    endif
#  else
#    error "can't determine endianess"
#  endif
#endif /* _STLP_BIG_ENDIAN */

/* ==========================================================
 * final workaround tuning based on given flags
 * ========================================================== */

#if defined (_STLP_NO_IOSTREAMS)
#  define _STLP_USE_NO_IOSTREAMS
#endif

/* Operating system recognition (basic) */
#if defined (__unix) || defined (__linux__) || defined (__QNX__) || defined (_AIX)  || defined (__NetBSD__) || defined(__OpenBSD__) || defined (__Lynx__)
#  define _STLP_UNIX 1
#elif defined(macintosh) || defined (_MAC)
#  define _STLP_MAC  1
#elif defined (_WIN32) || defined (__WIN32) || defined (WIN32) || defined (__WIN32__)
#  define _STLP_WIN32 1
#elif defined (__WIN16) || defined (WIN16) || defined (_WIN16)
#  define _STLP_WIN16
#endif /* __unix */

/* Native headers access macros */
#include <stl/config/_native_headers.h>

/*  shared library tune-up */

#if defined (__BUILDING_STLPORT)
/*  if we are rebuilding right now, place everything here */
#  undef  _STLP_DESIGNATED_DLL
#  define _STLP_DESIGNATED_DLL 1
#endif

#if !defined (_NOTHREADS) && !defined (_STLP_THREADS_DEFINED)

#  if defined (_PTHREADS)
#    define _STLP_PTHREADS
#    define _STLP_THREADS
#  endif
#  if defined (_UITHREADS)
#    define _STLP_UITHREADS
#    define _STLP_THREADS
#  endif

#  if defined (__sgi) && !defined (__KCC) && !defined (__GNUC__)
#    define _STLP_SGI_THREADS
#  elif defined (__DECC) || defined (__DECCXX)
#    define _STLP_DEC_THREADS
#  elif defined (_STLP_WIN32) && !defined (_STLP_PTHREADS)
#    define _STLP_WIN32THREADS 1
#  elif ((defined (__sun) && !defined (__linux__)) || defined (_UITHREADS) ) && \
        !defined(_STLP_PTHREADS)
#    define _STLP_UITHREADS
#  elif defined (__OS2__)
#    define _STLP_OS2THREADS
#  elif defined (__BEOS__)
#    define _STLP_BETHREADS
#  elif defined (__MWERKS__) && defined (N_PLAT_NLM) /* (__dest_os == __netware_os) */
#    define _STLP_NWTHREADS
#  else
#    define _STLP_PTHREADS
#  endif /* __sgi */
#  define _STLP_THREADS_DEFINED
#endif

#if (defined (_REENTRANT) || defined (_THREAD_SAFE) || \
    (defined (_POSIX_THREADS) && defined (__OpenBSD__))) && \
    !defined (_STLP_THREADS)
#  define _STLP_THREADS
#endif /* _REENTRANT */

#if defined (__linux__) && defined (_STLP_PTHREADS)
/* #  include <features.h> */

#  if defined (__USE_XOPEN2K) && !defined (_STLP_DONT_USE_PTHREAD_SPINLOCK)
#    define _STLP_USE_PTHREAD_SPINLOCK
#    define _STLP_STATIC_MUTEX _STLP_mutex
#  endif /* __USE_XOPEN2K */
#endif /* __linux__ && _STLP_PTHREADS */

#if defined (__OpenBSD__) && defined (_POSIX_THREADS) && !defined (_STLP_DONT_USE_PTHREAD_SPINLOCK)
#  define _STLP_USE_PTHREAD_SPINLOCK
#  define _STLP_STATIC_MUTEX _STLP_mutex
#endif

#ifndef _STLP_STATIC_MUTEX
#  define _STLP_STATIC_MUTEX _STLP_mutex_base
#endif

#if defined (_STLP_THREADS)
#  define _STLP_VOLATILE volatile
#else
#  define _STLP_VOLATILE
#endif

#ifdef _STLP_DEBUG
#  define _STLP_ASSERTIONS 1
#endif

#if !defined (_STLP_STATIC_ASSERT)
/* Some compiler support 0 size array so we use negative size array to generate
 * a compilation time error.
 */
#  define _STLP_STATIC_ASSERT(expr) typedef char __static_assert[expr ? 1 : -1];
#endif

/* if _STLP_DEBUG or _STLP_ASSERTIONS are set, stl/debug/_debug.h defines those */

#if !defined (_STLP_ASSERTIONS) && !defined (_STLP_DEBUG) && !defined (_STLP_DEBUG_ALLOC)
#  define _STLP_ASSERT(expr)
#endif

#if !defined (_STLP_DEBUG)
#  define _STLP_VERBOSE_ASSERT(expr,diagnostic)
#  define _STLP_DEBUG_CHECK(expr)
#  define _STLP_DEBUG_DO(expr)
#endif

/* default allocator configuration */
#define _STLP_DEFAULT_ALLOCATOR(_Tp) StlNodeAlloc< _Tp >
#define _STLP_DEFAULT_PAIR_ALLOCATOR(_Key, _Tp) StlNodeAlloc< pair < _Key, _Tp > >

/* debug mode tool */
#if defined (_STLP_DEBUG)
#  define _STLP_NON_DBG_NAME(X) _NonDbg_##X
#endif

/* pointer specialization tool */
#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  define _STLP_PTR_IMPL_NAME(X) _##X##_impl
#endif

/* Import some vendor's headers into corresponding STLport ones if they might be needed
 * (if we wrap native iostreams and use namepace other than std::) */
#  if defined (_STLP_WHOLE_NATIVE_STD)
#    define  _STLP_IMPORT_VENDOR_STD 1
#    undef   _STLP_MINIMUM_IMPORT_STD
#  endif

/* assume std:: namespace for C++ std library if not being told otherwise */
#    define _STLP_VENDOR_STD std

#    if !defined (_STLP_STD)
#      if !defined (_STLP_DEBUG)
#        if !defined (_STLP_USING_CROSS_NATIVE_RUNTIME_LIB)
#          ifndef _STLP_THREADS
#            define _STLP_STD  stlpmtx_std
#          else
#            define _STLP_STD  stlp_std
#          endif
#        else
#          ifndef _STLP_THREADS
#            define _STLP_STD  stlpxmtx_std
#          else
#            define _STLP_STD  stlpx_std
#          endif
#        endif
#      else
/*
 * The STLport debug mode is binary incompatible with the other modes,
 * lets make it clear on the STLport namespace to generate link errors rather
 * than runtime.
 */
#        if !defined (_STLP_USING_CROSS_NATIVE_RUNTIME_LIB)
#          ifndef _STLP_THREADS
#            define _STLP_STD  stlpdmtx_std
#          else
#            define _STLP_STD  stlpd_std
#          endif
#        else
#          ifndef _STLP_THREADS
#            define _STLP_STD  stlpdxmtx_std
#          else
#            define _STLP_STD  stlpdx_std
#          endif
#        endif
#      endif
#    endif

namespace _STLP_STD { }

#  define _STLP_PRIV_FORCE stlp_priv

#  if !defined (_STLP_DONT_USE_PRIV_NAMESPACE)
#    define _STLP_PRIV _STLP_PRIV_FORCE
namespace _STLP_PRIV {
  using namespace _STLP_STD;
}
#  else
#    define _STLP_PRIV _STLP_STD
#  endif

/* decide whether or not we use separate namespace for rel ops */
#  if !defined (_STLP_NO_RELOPS_NAMESPACE)
/* Use std::rel_ops namespace */
#    define _STLP_USE_SEPARATE_RELOPS_NAMESPACE
#  endif /* Use std::rel_ops namespace */

/* Official STLport namespace when std is not redefined.
 * Here we don't use a macro as stlport is used as file name by boost
 * and folder name under beos:
 */
namespace stlport = _STLP_STD;

/* advanced keywords usage */
#if defined (_STLP_USE_CONTAINERS_EXTENSION)
#  define _STLP_KEY_TYPE_FOR_CONT_EXT(type)
#  define _STLP_TEMPLATE_FOR_CONT_EXT template <class _KT>
#else
#  define _STLP_KEY_TYPE_FOR_CONT_EXT(type) typedef type _KT;
#  define _STLP_TEMPLATE_FOR_CONT_EXT
#endif

#define _STLP_DECLARE_REVERSE_ITERATORS(__reverse_iterator) \
   typedef _STLP_STD::reverse_iterator<const_iterator> const_reverse_iterator; \
   typedef _STLP_STD::reverse_iterator<iterator> reverse_iterator

#define _STLP_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS \
        _STLP_DECLARE_REVERSE_ITERATORS(reverse_bidirectional_iterator)
#define _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS \
        _STLP_DECLARE_REVERSE_ITERATORS(reverse_iterator)

#define __IMPORT_CONTAINER_TYPEDEFS(_Super)                              \
    typedef typename _Super::value_type value_type;                      \
    typedef typename _Super::size_type size_type;                        \
    typedef typename _Super::difference_type difference_type;            \
    typedef typename _Super::reference reference;                        \
    typedef typename _Super::const_reference const_reference;            \
    typedef typename _Super::pointer pointer;                            \
    typedef typename _Super::const_pointer const_pointer;                \
    typedef typename _Super::allocator_type allocator_type;


#define __IMPORT_ITERATORS(_Super)                                       \
    typedef typename _Super::iterator iterator;                          \
    typedef typename _Super::const_iterator const_iterator;

#define __IMPORT_REVERSE_ITERATORS(_Super)                                   \
    typedef typename _Super::const_reverse_iterator  const_reverse_iterator; \
    typedef typename _Super::reverse_iterator reverse_iterator;

#define  __IMPORT_SUPER_COPY_ASSIGNMENT(__derived_name, _Self, _SUPER)       \
    __derived_name(const _Super& __x) : _SUPER(__x) {}                       \
    _Self& operator=(const _Super& __x) {                                    \
        *(_Super*)this = __x;                                                \
        return *this;                                                        \
    }                                                                        \
    __derived_name(const _Self& __x) : _SUPER(__x) {}                        \
    _Self& operator=(const _Self& __x) {                                     \
        *(_Super*)this = __x;                                                \
        return *this;                                                        \
    }

#define __IMPORT_WITH_ITERATORS(_Super) \
  __IMPORT_CONTAINER_TYPEDEFS(_Super) __IMPORT_ITERATORS(_Super)

#define __IMPORT_WITH_REVERSE_ITERATORS(_Super) \
  __IMPORT_WITH_ITERATORS(_Super) __IMPORT_REVERSE_ITERATORS(_Super)

#if !defined (_STLP_DONT_USE_EXCEPTIONS) && !defined (_STLP_USE_EXCEPTIONS)
#  define _STLP_USE_EXCEPTIONS
#endif

#if defined (_STLP_USE_EXCEPTIONS)
#  define _STLP_TRY try
#  define _STLP_CATCH_ALL catch(...)
#  ifndef _STLP_THROW
#    define _STLP_THROW(x) throw x
#  endif
#  define _STLP_RETHROW throw

#  define _STLP_UNWIND(action) catch(...) { action; throw; }

#  ifdef _STLP_THROW_RETURN_BUG
#    define _STLP_RET_AFTER_THROW(data) return data;
#  else
#    define _STLP_RET_AFTER_THROW(data)
#  endif

/* We do not use exception throw specifications unless we are forced to */
#  if !defined (_STLP_THROWS)
#    define _STLP_THROWS(x)
#  endif
#  if !defined (_STLP_NOTHROW)
#    define _STLP_NOTHROW
#  endif
#else
#  define _STLP_TRY
#  define _STLP_CATCH_ALL if (false)
#  ifndef _STLP_THROW
#    define _STLP_THROW(x)
#  endif
#  define _STLP_RETHROW {}
#  define _STLP_UNWIND(action)
#  define _STLP_THROWS(x)
#  define _STLP_NOTHROW
#  define _STLP_RET_AFTER_THROW(data)
#endif

/*
 * Here we check _STLP_NO_EXCEPTIONS which means that the compiler has no
 * exception support but not the _STLP_USE_EXCEPTIONS which simply means
 * that the user do not want to use them.
 */
#define _STLP_THROWS_INHERENTLY(x) throw x
#define _STLP_NOTHROW_INHERENTLY throw()

/* STLport function not returning are functions that throw so we translate
 * the noreturn functions in throwing functions taking also into account
 * exception support activation.
 */
#if defined (_STLP_NORETURN_FUNCTION) && !defined (_STLP_FUNCTION_THROWS)
#  define _STLP_FUNCTION_THROWS _STLP_NORETURN_FUNCTION
#else
#  define _STLP_FUNCTION_THROWS
#endif

#if defined (_STLP_DEBUG_ALLOC) && !defined (_STLP_ASSERTIONS)
#  define _STLP_ASSERTIONS 1
#endif

/* uninitialized value filler */
#ifndef _STLP_SHRED_BYTE
/* This value is designed to cause problems if an error occurs */
#  define _STLP_SHRED_BYTE 0xA3
#endif /* _STLP_SHRED_BYTE */

/* shared library tune-up */
#ifdef _STLP_USE_NO_IOSTREAMS
/*
 * If we do not use iostreams we undef USE_DYNAMIC_LIB macro as this macro add some code
 * to use the dynamic (shared) STLport library for some platform/compiler
 * configuration leading to problem when do not link to the STLport lib.
 */
#  undef _STLP_USE_DYNAMIC_LIB
#endif

#ifndef _STLP_USE_NO_IOSTREAMS

#  if defined (__DECCXX) && ! defined (__USE_STD_IOSTREAM)
#    define __USE_STD_IOSTREAM
#  endif

/* We only need to expose details of streams implementation
   if we use non-standard i/o or are building STLport*/
#  if defined (__BUILDING_STLPORT) || defined (_STLP_NO_FORCE_INSTANTIATE) || !defined(_STLP_NO_CUSTOM_IO)
#    define _STLP_EXPOSE_STREAM_IMPLEMENTATION 1
#  endif

/* We only need to expose details of global implementation if we are building STLport
   or have not instantiated everything in the lib */
#  if defined (__BUILDING_STLPORT) || defined (_STLP_NO_FORCE_INSTANTIATE)
#    undef  _STLP_EXPOSE_GLOBALS_IMPLEMENTATION
#    define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1
#  endif

#else /* _STLP_USE_NO_IOSTREAMS */
/* when we are not using SGI iostreams, we must expose globals, but not streams implementation */
#  define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION
#endif /* _STLP_USE_NO_IOSTREAMS */

#ifdef _STLP_USE_SEPARATE_RELOPS_NAMESPACE
#  define _STLP_RELOPS_OPERATORS(_TMPL, _TP) \
_TMPL inline bool operator!=(const _TP& __x, const _TP& __y) {return !(__x == __y);}\
_TMPL inline bool operator>(const _TP& __x, const _TP& __y)  {return __y < __x;}\
_TMPL inline bool operator<=(const _TP& __x, const _TP& __y) { return !(__y < __x);}\
_TMPL inline bool operator>=(const _TP& __x, const _TP& __y) { return !(__x < __y);}
#else
#  define _STLP_RELOPS_OPERATORS(_TMPL, _TP)
#endif

/* A really useful macro */
#define _STLP_ARRAY_SIZE(A) sizeof(A) / sizeof(A[0])
#define _STLP_ARRAY_AND_SIZE(A) A, sizeof(A) / sizeof(A[0])

#endif /* _STLP_FEATURES_H */
