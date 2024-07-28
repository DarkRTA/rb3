#ifndef _MSL_TYPE_TRAITS_PROPERTY
#define _MSL_TYPE_TRAITS_PROPERTY

#include "MSL_C++/Metrowerks/type_traits.h"

#include "MSL_C++/MSL_Common/type_traits/integral_constant.h"
#include "MSL_C++/MSL_Common/type_traits/relationship.h"

// clang-format off: conciseness
namespace std {

#pragma region "type properties"
    template <typename T> struct is_const : public false_type {};
    template <typename T> struct is_const<const T> : public true_type {};

    template <typename T> struct is_volatile : public false_type {};
    template <typename T> struct is_volatile<volatile T> : public true_type {};

    template <typename T>
    struct is_trivial : public bool_constant<Metrowerks::is_trivial<T>::value> {};

    template <typename T>
    struct is_trivially_copyable : public bool_constant<
        Metrowerks::has_trivial_copy_ctor<T>::value &&
        Metrowerks::has_trivial_assignment<T>::value
    > {};

    template <typename T> struct is_standard_layout;

    template <typename T>
    struct is_pod : public bool_constant<Metrowerks::is_POD<T>::value> {};

    template <typename T> struct is_literal_type;

    namespace detail {

        template <typename T>
        struct is_empty_helper1 : public T { int i; };
        struct is_empty_helper2 { int i; };

        template <typename T, bool IsInheritable = is_class<T>::value>
        struct is_empty : public bool_constant<sizeof(is_empty_helper1<T>) == sizeof(is_empty_helper2)> {};

        template <typename T>
        struct is_empty<T, false> : public false_type {};

    }

    template <typename T>
    struct is_empty : public detail::is_empty<T> {};

    template <typename T>
    struct is_polymorphic : public bool_constant<Metrowerks::is_polymorphic<T>::value> {};

    template <typename T>
    struct is_abstract : public bool_constant<Metrowerks::is_abstract<T>::value> {};

    namespace detail {

        template <typename T, bool IsArithmetic = is_arithmetic<T>::value>
        struct is_signed : public bool_constant<(T(0) > T(-1))> {};

        template <typename T>
        struct is_signed<T, false> : public false_type {};

    }

    template <typename T>
    struct is_signed : public detail::is_signed<T> {};

    template <typename T>
    struct is_unsigned : public bool_constant<!is_signed<T>::value> {};
#pragma endregion

#pragma region "supported operations"
    // template <typename T, typename... Args> struct is_constructible;
    // template <typename T, typename... Args> struct is_trivially_constructible;
    // template <typename T, typename... Args> struct is_nothrow_constructible;

    template <typename T> struct is_default_constructible;
    template <typename T> struct is_trivially_default_constructible
        : public bool_constant<Metrowerks::has_trivial_default_ctor<T>::value> {};
    template <typename T> struct is_nothrow_default_constructible
        : public bool_constant<Metrowerks::has_nothrow_default_ctor<T>::value> {};

    template <typename T> struct is_copy_constructible;
    template <typename T> struct is_trivially_copy_constructible
        : public bool_constant<Metrowerks::has_trivial_copy_ctor<T>::value> {};
    template <typename T> struct is_nothrow_copy_constructible
        : public bool_constant<Metrowerks::has_nothrow_copy_ctor<T>::value> {};

    template <typename T> struct is_move_constructible : public false_type {}; // C++11
    template <typename T> struct is_trivially_move_constructible : public false_type {}; // C++11
    template <typename T> struct is_nothrow_move_constructible : public false_type {}; // C++11

    template <typename T, typename U> struct is_assignable;
    template <typename T, typename U> struct is_trivially_assignable;
    template <typename T, typename U> struct is_nothrow_assignable;

    template <typename T> struct is_copy_assignable;
    template <typename T> struct is_trivially_copy_assignable
        : public bool_constant<Metrowerks::has_trivial_assignment<T>::value> {};
    template <typename T> struct is_nothrow_copy_assignable
        : public bool_constant<Metrowerks::has_nothrow_assignment<T>::value> {};

    template <typename T> struct is_move_assignable : public false_type {}; // C++11
    template <typename T> struct is_trivially_move_assignable : public false_type {}; // C++11
    template <typename T> struct is_nothrow_move_assignable : public false_type {}; // C++11

    template <typename T> struct is_destructible;
    template <typename T> struct is_trivially_destructible
        : public bool_constant<Metrowerks::has_trivial_dtor<T>::value> {};
    template <typename T> struct is_nothrow_destructible
        : public bool_constant<Metrowerks::has_nothrow_dtor<T>::value> {};

    template <typename T> struct has_virtual_destructor
        : public bool_constant<Metrowerks::has_virtual_dtor<T>::value> {};
#pragma endregion

#pragma region "type property queries"
    template <typename T>
    struct alignment_of : public integral_constant<size_t, Metrowerks::alignment_of<T>::value> {};

    template <typename T>
    struct rank : public integral_constant<size_t, 0> {};
    template <typename T>
    struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1> {};
    template <typename T, size_t N>
    struct rank<T[N]> : public integral_constant<size_t, rank<T>::value + 1> {};

    template <typename T, unsigned N = 0>
    struct extent : public integral_constant<size_t, 0> {};
    template <typename T>
    struct extent<T[], 0> : public integral_constant<size_t, 0> {};
    template <typename T, unsigned N>
    struct extent<T[], N> : public extent<T, N - 1> {};
    template <typename T, size_t I>
    struct extent<T[I], 0> : public integral_constant<size_t, I> {};
    template <typename T, size_t I, unsigned N>
    struct extent<T[I], N> : public extent<T, N - 1> {};
#pragma endregion

}
// clang-format on

#endif
