// Decomp hack to allow selecting between the two different vector styles

#ifndef _STLP_INTERNAL_VECTOR_H
#define _STLP_INTERNAL_VECTOR_H

#ifdef _STLP_USE_SIZED_VECTOR
#ifndef _STLP_INTERNAL_VECTOR_SIZED_H
#include <stl/_vector_sized.h> /* IWYU pragma: export */
#endif
#define _STLP_VECTOR_SIZE_PARAM class _Size,
#define _STLP_VECTOR_SIZE_ARG _Size,
#define _STLP_VECTOR_SIZE_DFLT_PARAM __DFL_TYPE_PARAM(_Size, unsigned short),
#define _STLP_VECTOR_SIZE_DFLT_ARG unsigned short,
#define _STLP_VECTOR_SIZE_PARAM_END , class _Size
#else
#ifndef _STLP_INTERNAL_VECTOR_PTRS_H
#include <stl/_vector_ptrs.h> /* IWYU pragma: export */
#endif
#define _STLP_VECTOR_SIZE_PARAM
#define _STLP_VECTOR_SIZE_ARG
#define _STLP_VECTOR_SIZE_DFLT_PARAM
#define _STLP_VECTOR_SIZE_DFLT_ARG
#define _STLP_VECTOR_SIZE_PARAM_END
#endif

_STLP_BEGIN_NAMESPACE

#ifndef _STLP_DONT_USE_PTR_SPECIALIZATIONS
#include <stl/pointers/_vector.h> /* IWYU pragma: export */
#endif /* _STLP_DONT_USE_PTR_SPECIALIZATIONS */

#define _STLP_TEMPLATE_HEADER                                                            \
    template <class _Tp, class _Alloc _STLP_VECTOR_SIZE_PARAM_END>
#define _STLP_TEMPLATE_CONTAINER vector<_Tp, _STLP_VECTOR_SIZE_ARG _Alloc>
#include <stl/_relops_cont.h>
#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
    template <class _Tp, _STLP_VECTOR_SIZE_PARAM class _Alloc>
    struct __move_traits<vector<_Tp, _STLP_VECTOR_SIZE_ARG _Alloc> > {
        typedef __true_type implemented;
        // Completness depends on the allocator:
        typedef typename __move_traits<_Alloc>::complete complete;
    };
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

_STLP_END_NAMESPACE

#ifndef _STLP_INTERNAL_BVECTOR_H
#include <stl/_bvector.h> /* IWYU pragma: export */
#endif

#if defined(_STLP_DEBUG)
#include <stl/debug/_vector.h> /* IWYU pragma: export */
#endif

#if defined(_STLP_USE_WRAPPER_FOR_ALLOC_PARAM)
#include <stl/wrappers/_vector.h> /* IWYU pragma: export */
#endif

#undef _STLP_VECTOR_TEMPL_PARAMS
#undef _STLP_VECTOR_TEMPL_DFLT
#undef _STLP_VECTOR_TEMPL_ARGS

#endif
