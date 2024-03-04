/*
 * This file defines site configuration.
 */

// Required for symbols to match
#define _STLP_DONT_USE_PRIV_NAMESPACE

/*
 * _STLP_NO_THREADS: if defined, STLport don't use any
 * multithreading support. Synonym is _NOTHREADS
 */
#define _NOTHREADS
#define _STLP_NO_THREADS

/* _PTHREADS: if defined, use POSIX threads for multithreading support. */
/*
#define _PTHREADS
*/

/* compatibility section
 */

#if (defined (_STLP_NOTHREADS) || defined (_STLP_NO_THREADS) || defined (NOTHREADS))
#  if !defined (_NOTHREADS)
#    define _NOTHREADS
#  endif
#  if !defined (_STLP_NO_THREADS)
#    define _STLP_NO_THREADS
#  endif
#endif

#if !defined(_STLP_USE_DYNAMIC_LIB) && !defined(_STLP_USE_STATIC_LIB)
/*
 * Turn _STLP_USE_DYNAMIC_LIB to enforce use of .dll version of STLport library.
 * NOTE: please do that only if you know what you are doing!
 * Changing default will require you to change makefiles in "build" accordingly
 * and to rebuild STLPort library!
 * On UNIX, this has no effect, see build/lib/README for make tags.
 * See STLport configuration file (build/lib/configure.bat) for help in building
 * the require library versions.
 */
/*
#define _STLP_USE_DYNAMIC_LIB
*/

/*
 * Turn _STLP_USE_STATIC_LIB to enforce use of static version of STLport library.
 * NOTE: please do that only if you know what you are doing!
 * Changing default will require you to change makefile in "build" accordingly
 * and to rebuild STLPort library!
 * On UNIX, this has no effect, see build/lib/README for make tags.
 * See STLport configuration file (build/lib/configure.bat) for help in building
 * the require library versions.
 */
/*
#define _STLP_USE_STATIC_LIB
*/
#endif

/*
 * Signal STLport that we are using the cygwin distrib with the -mno-cygwin option.
 * This is similar to a mingw environment except that relative path to native headers
 * is different, this is why we need this macro.
 */
/*
#define _STLP_NO_CYGWIN
 */

/*
 * Edit relative path below (or put full path) to get native
 * compiler vendor's headers included. Default is "../include"
 * for _STLP_NATIVE_INCLUDE_PATH, default for other macros is
 * _STLP_NATIVE_INCLUDE_PATH.
 * Hint: never install STLport in the directory that ends with "include"
 */
/*
#undef _STLP_NATIVE_INCLUDE_PATH
#define _STLP_NATIVE_INCLUDE_PATH ../include
*/
/* same for C library headers like <cstring> */
/*
#undef _STLP_NATIVE_CPP_C_INCLUDE_PATH
#define _STLP_NATIVE_CPP_C_INCLUDE_PATH _STLP_NATIVE_INCLUDE_PATH
*/
/* same for C headers like <string.h> */
/*
#undef _STLP_NATIVE_C_INCLUDE_PATH
#define _STLP_NATIVE_C_INCLUDE_PATH _STLP_NATIVE_INCLUDE_PATH
*/
/* Some compilers locate basic C++ runtime support headers (<new>, <typeinfo>, <exception>) in separate directory */
/*
#undef _STLP_NATIVE_CPP_RUNTIME_INCLUDE_PATH
#define _STLP_NATIVE_CPP_RUNTIME_INCLUDE_PATH _STLP_NATIVE_INCLUDE_PATH
*/

/*
 * Uncomment _STLP_LEAKS_PEDANTIC to force deallocation of ALL allocated
 * memory chunks. Normally not required. But if you worry about quazi-leaks
 * (may be reported by some leaks detection tools), use
 * _STLP_LEAKS_PEDANTIC. It should be used with _STLP_USE_NEWALLOC or
 * _STLP_USE_MALLOC (see below), the default node_alloc allocator also clean
 * its internal memory pool but only if STLport is used as a dynamic library
 * under Win32 (using MSVC like compilers).
 */
/*
#define _STLP_LEAKS_PEDANTIC 1
*/

/*
 * Uncomment _STLP_USE_NEWALLOC to force allocator<T> to use plain "new"
 * instead of STLport optimized node allocator engine.
 */
/*
#define _STLP_USE_NEWALLOC 1
*/

/*
 * Uncomment _STLP_USE_MALLOC to force allocator<T> to use plain "malloc"
 * instead of STLport optimized node allocator engine.
 */
/*
#define _STLP_USE_MALLOC 1
*/

/*
 * Uncomment _STLP_USE_PERTHREAD_ALLOC to force allocator<T> to use
 * a specific implementation targetting the massively multi-threaded
 * environment. The implementation is based on the POSIX pthread
 * interface.
 */
/*
#define _STLP_USE_PERTHREAD_ALLOC 1
*/

/*
 * Set _STLP_DEBUG_ALLOC to use allocators that perform memory debugging,
 * such as padding/checking for memory consistency
 */
/*
#define _STLP_DEBUG_ALLOC 1
*/

/*
 * For compiler not supporting partial template specialization or ordering of
 * template functions STLport implement a workaround based on inheritance
 * detection. This inheritance can introduce trouble in client code when
 * a user class derived a STL container (which is not advised as STL containers
 * do not have virtual destructors). To disable this workaround turn this macro on:
 */
/*
#define _STLP_DONT_USE_PARTIAL_SPEC_WRKD 1
*/

/*
 * Uncomment this to force all debug diagnostic to be directed through a
 * user-defined global function:
 *  void __stl_debug_message(const char * format_str, ...)
 * instead of predefined STLport routine.
 * This allows you to take control of debug message output.
 * Default routine calls fprintf(stderr,...)
 * Note : If you set this macro, you must supply __stl_debug_message
 * function definition somewhere.
 */
/*
#define _STLP_DEBUG_MESSAGE 1
*/

/*
 * Uncomment this to force all failed assertions to be executed through
 * user-defined global function:
 *  void __stl_debug_terminate(void). This allows
 * you to take control of assertion behaviour for debugging purposes.
 * Default routine calls abort().
 * Note : If you set this macro, you must supply __stl_debug_terminate
 * function definition somewhere.
 */
/*
#define _STLP_DEBUG_TERMINATE 1
*/

/*
 * Uncomment that to disable exception handling code
 */
#define _STLP_DONT_USE_EXCEPTIONS 1

/*==========================================================
 * Compatibility section
 *==========================================================*/

/*
 * Use abbreviated class names for linker benefit (don't affect interface).
 * This option is obsolete, but should work in this release.
 *
 */
/*
#define _STLP_USE_ABBREVS
*/

/*
 * This definition precludes STLport reverse_iterator to be compatible with
 * other parts of MSVC library. (With partial specialization, it just
 * has no effect).
 * Use it _ONLY_ if you use SGI-style reverse_iterator<> template explicitly
 */
/*
#define _STLP_NO_MSVC50_COMPATIBILITY 1
*/

/*
 * On systems with support of large files (_LARGEFILE_SOURCE,
 * _LARGEFILE64_SOURCE defined) we will use 64-bit file offset, even if
 * __USE_FILE_OFFSET64 or _FILE_OFFSET_BITS not defined or _FILE_OFFSET_BITS
 * less than 64. In the last case sizeof(std::streamoff) may not be equal to
 * sizeof(off_t), if you want to force equal size of off_t and streamoff,
 * uncomment macro below. But pay attention, this has influence on libstlport
 * and in future usage it may cause conflict with defined _FILE_OFFSET_BITS macro.
 */

/*
#define _STLP_USE_DEFAULT_FILE_OFFSET
*/

/*==========================================================================*/

/*
  Local Variables:
  mode:C++
  End:
*/
