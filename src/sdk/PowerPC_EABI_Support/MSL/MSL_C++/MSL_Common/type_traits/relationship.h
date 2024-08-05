#ifndef _MSL_TYPE_TRAITS_RELATIONSHIP
#define _MSL_TYPE_TRAITS_RELATIONSHIP

#include "MSL_C++/MSL_Common/type_traits/integral_constant.h"
#include "MSL_C++/MSL_Common/type_traits/utility.h"

// clang-format off: conciseness
namespace std {

    namespace detail {

        template <typename From, typename To>
        struct is_convertible {
            static true_type test(To) { __MWERKS_NOEVAL; }
            static false_type test(...) { __MWERKS_NOEVAL; }

            typedef __decltype__(test(declval<From>())) type;
        };

        template <typename Base, typename Derived>
        struct is_base_of {
            static true_type test(const volatile Base*) { __MWERKS_NOEVAL; }
            static false_type test(const volatile void*) { __MWERKS_NOEVAL; }

            typedef __decltype__(test(declval<Derived*>())) type;
        };

    }

    template <typename T, typename U>
    struct is_same : public false_type {};
    template <typename T>
    struct is_same<T, T> : public true_type {};

    template <typename From, typename To>
    struct is_convertible : public detail::is_convertible<From, To> {};

    template <typename Base, typename Derived>
    struct is_base_of : public detail::is_base_of<Base, Derived> {};

}
// clang-format on

#endif
