#ifndef _MSL_TYPE_TRAITS_CATEGORY
#define _MSL_TYPE_TRAITS_CATEGORY

#include <MSL_C++/cstddef>

#include "MSL_C++/Metrowerks/type_traits.h"

#include "MSL_C++/MSL_Common/type_traits/integral_constant.h"
#include "MSL_C++/MSL_Common/type_traits/manip.h"
#include "MSL_C++/MSL_Common/type_traits/operation.h"
#include "MSL_C++/MSL_Common/type_traits/relationship.h"

// clang-format off: conciseness
namespace std {

    template <typename T>
    struct is_void : public is_same<remove_cv<T>::type, void> {};

    template <typename T>
    struct is_integral : public bool_constant<Metrowerks::is_integral<T>::value> {};

    template <typename T>
    struct is_floating_point : public bool_constant<Metrowerks::is_floating_point<T>::value> {};

    template <typename T> struct is_array : public false_type {};
    template <typename T> struct is_array<T[]> : public true_type {};
    template <typename T, std::size_t N> struct is_array<T[N]> : public true_type {};

    template <typename T>
    struct is_enum : public bool_constant<Metrowerks::is_enum<T>::value> {};

    template <typename T>
    struct is_union : public bool_constant<Metrowerks::is_union<T>::value> {};

    template <typename T>
    struct is_class : public bool_constant<Metrowerks::is_class<T>::value> {};

    // C++11: needs variadic template args to implement properly
    // As a stopgap, variants for up to 16 parameters are generated
    #include "MSL_C++/MSL_Common/type_traits/_category_function.h"

    template <typename T> struct is_pointer : public false_type {};
    template <typename T> struct is_pointer<T*> : public true_type {};
    template <typename T> struct is_pointer<T* const> : public true_type {};
    template <typename T> struct is_pointer<T* volatile> : public true_type {};
    template <typename T> struct is_pointer<T* const volatile> : public true_type {};

    template <typename T> struct is_lvalue_reference : public false_type {};
    template <typename T> struct is_lvalue_reference<T&> : public true_type {};

    template <typename T> struct is_rvalue_reference : public false_type {};
    // template <typename T> struct is_rvalue_reference<T&&> : public true_type {}; // C++11

    namespace detail {

        template <typename T>
        struct is_member_pointer : public false_type {};

        template <typename T, typename U>
        struct is_member_pointer<T U::*> : public true_type {};

    }

    template <typename T>
    struct is_member_pointer
        : public detail::is_member_pointer<remove_cv<T>::type> {};

    template <typename T>
    struct is_member_object_pointer : public bool_constant<
        is_member_pointer<T>::value &&
        !is_function<T>::value
    > {};

    template <typename T>
    struct is_member_function_pointer : public bool_constant<
        is_member_pointer<T>::value &&
        is_function<T>::value
    > {};

    template <typename T>
    struct is_arithmetic : public bool_constant<
        is_integral<T>::value ||
        is_floating_point<T>::value
    > {};

    template <typename T>
    struct is_fundamental : public bool_constant<
        is_arithmetic<T>::value ||
        is_void<T>::value
    > {};

    template <typename T>
    struct is_scalar : public bool_constant<
        is_arithmetic<T>::value ||
        is_enum<T>::value ||
        is_pointer<T>::value ||
        is_member_pointer<T>::value
    > {};

    template <typename T>
    struct is_object : public bool_constant<
        is_scalar<T>::value ||
        is_array<T>::value ||
        is_union<T>::value ||
        is_class<T>::value
    > {};

    template <typename T>
    struct is_compound : public negation<is_fundamental<T> > {};

    template <typename T>
    struct is_reference : public bool_constant<
        is_lvalue_reference<T>::value ||
        is_rvalue_reference<T>::value
    > {};

}
// clang-format on

#endif
