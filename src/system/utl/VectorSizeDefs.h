#ifndef UTL_VECTORSIZEDEFS_H
#define UTL_VECTORSIZEDEFS_H

#include <vector>

/*
 * These defines exist as future-proofing for using STLs other than STLport.
 * Use them wherever the vector size argument must be used, rather than specifying the
 * size argument directly, as otherwise that argument will attempt to be used as the
 * allocator on standard STL implementations and fail miserably.
 *
 * Usage examples:
    template <class T VECTOR_SIZE_DFLT_PARAM>
    class Vector2 : public std::vector<T VECTOR_SIZE_ARG> {};

    template <class T VECTOR_SIZE_PARAM>
    void foo(Vector2<T VECTOR_SIZE_ARG>& vec) { ... }
 */
// clang-format off
#if defined(STLPORT) && defined(_STLP_USE_SIZED_VECTOR)
    // Set vector to use a short size type
    #define VECTOR_SIZE_SMALL , unsigned short
    // Set vector to use a large size type
    #define VECTOR_SIZE_LARGE , unsigned int
    // Template parameter declaration
    #define VECTOR_SIZE_PARAM , class VecSize
    // Argument to a template instantiation
    #define VECTOR_SIZE_ARG , VecSize
    // Template parameter declaration with default value
    #define VECTOR_SIZE_DFLT_PARAM , class VecSize = unsigned short
    // Default argument to a template instantiation
    #define VECTOR_SIZE_DFLT_ARG , unsigned short
#else
    #define VECTOR_SIZE_SMALL
    #define VECTOR_SIZE_LARGE
    #define VECTOR_SIZE_PARAM
    #define VECTOR_SIZE_ARG
    #define VECTOR_SIZE_DFLT_PARAM
    #define VECTOR_SIZE_DFLT_ARG
#endif
// clang-format on

#endif
