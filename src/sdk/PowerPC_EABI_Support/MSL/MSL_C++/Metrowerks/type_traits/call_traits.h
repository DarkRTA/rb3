#ifndef _METROWERKS_TYPE_TRAITS_CALL_TRAITS
#define _METROWERKS_TYPE_TRAITS_CALL_TRAITS

namespace Metrowerks {

    namespace details {

        // probably doesn't cover all useful cases (e.g. long long),
        // but this will do for our purposes

        template <typename T, bool Small = sizeof(T) <= sizeof(void *)>
        struct call_traits_imp {
            typedef const T param_type;
        };

        template <typename T>
        struct call_traits_imp<T, false> {
            typedef const T &param_type;
        };

        template <typename T, bool Small>
        struct call_traits_imp<T *, Small> {
            typedef T *param_type;
        };

        template <typename T, bool Small>
        struct call_traits_imp<const T *, Small> {
            typedef const T *param_type;
        };

        template <typename T, bool Small>
        struct call_traits_imp<T &, Small> {
            typedef T &param_type;
        };

        template <typename T, bool Small>
        struct call_traits_imp<const T &, Small> {
            typedef const T &param_type;
        };

    }

    // name known; boost
    template <typename T>
    struct call_traits {
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef typename details::call_traits_imp<T>::param_type param_type;
    };

}

#endif
