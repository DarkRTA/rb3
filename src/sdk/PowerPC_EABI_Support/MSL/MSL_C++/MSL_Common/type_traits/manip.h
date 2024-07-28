#ifndef _MSL_TYPE_TRAITS_MANIP
#define _MSL_TYPE_TRAITS_MANIP

#include <MSL_C++/cstddef>

#include "MSL_C++/Metrowerks/type_traits.h"

// clang-format off: conciseness
namespace std {

#pragma region "const-volatile modifications"
    template <typename T> struct add_const { typedef const T type; };
    template <typename T> struct add_volatile { typedef volatile T type; };
    template <typename T> struct add_cv { typedef const volatile T type; };

    template <typename T> struct remove_const { typedef T type; };
    template <typename T> struct remove_const<const T> { typedef T type; };
    template <typename T> struct remove_const<const volatile T> { typedef volatile T type; };

    template <typename T> struct remove_volatile { typedef T type; };
    template <typename T> struct remove_volatile<volatile T> { typedef T type; };
    template <typename T> struct remove_volatile<const volatile T> { typedef const T type; };

    template <typename T> struct remove_cv { typedef T type; };
    template <typename T> struct remove_cv<const T> { typedef T type; };
    template <typename T> struct remove_cv<volatile T> { typedef T type; };
    template <typename T> struct remove_cv<const volatile T> { typedef T type; };

    namespace detail {

        template <typename From, typename To> struct copy_const { typedef To type; };
        template <typename From, typename To> struct copy_const<const From, To> { typedef const To type; };

        template <typename From, typename To> struct copy_volatile { typedef To type; };
        template <typename From, typename To> struct copy_volatile<volatile From, To> { typedef volatile To type; };

        template <typename From, typename To> struct copy_cv { typedef From type; };
        template <typename From, typename To> struct copy_cv<const From, To> { typedef const To type; };
        template <typename From, typename To> struct copy_cv<volatile From, To> { typedef volatile To type; };
        template <typename From, typename To> struct copy_cv<const volatile From, To> { typedef const volatile To type; };

    }

#pragma endregion

#pragma region "reference modifications"
    template <typename T> struct add_lvalue_reference { typedef T& type; };
    // template <typename T> struct add_rvalue_reference { typedef T&& type; }; // C++11

    template <> struct add_lvalue_reference<void> { typedef void type; };
    template <> struct add_lvalue_reference<const void> { typedef const void type; };
    template <> struct add_lvalue_reference<volatile void> { typedef volatile void type; };
    template <> struct add_lvalue_reference<const volatile void> { typedef const volatile void type; };

    template <typename T> struct remove_reference { typedef T type; };
    template <typename T> struct remove_reference<T&> { typedef T type; };
    // template <typename T> struct remove_reference<T&&> { typedef T type; }; // C++11
#pragma endregion

#pragma region "pointer modifications"
    template <typename T> struct add_pointer { typedef remove_reference<T>::type* type; };

    template <typename T> struct remove_pointer { typedef T type; };
    template <typename T> struct remove_pointer<T*> { typedef T type; };
    template <typename T> struct remove_pointer<T* const> { typedef T type; };
    template <typename T> struct remove_pointer<T* volatile> { typedef T type; };
    template <typename T> struct remove_pointer<T* const volatile> { typedef T type; };
#pragma endregion

#pragma region "array modifications"
    template <typename T> struct remove_extent { typedef T type; };
    template <typename T> struct remove_extent<T[]> { typedef T type; };
    template <typename T, std::size_t N> struct remove_extent<T[N]> { typedef T type; };

    template <typename T> struct remove_all_extents { typedef T type; };
    template <typename T> struct remove_all_extents<T[]> { typedef remove_all_extents<T>::type type; };
    template <typename T, std::size_t N> struct remove_all_extents<T[N]> { typedef remove_all_extents<T>::type type; };
#pragma endregion

#pragma region "miscellaneous transformations"

    // Not implementable, __attribute__ ((aligned (i))) doesn't work with template args
    // template <std::size_t Len, std::size_t Align = 4> struct aligned_storage;

    // template <std::size_t Len, typename... Types> struct aligned_union

    template <typename T>
    struct remove_cvref {
        typedef remove_cv<remove_reference<T>::value>::value type;
    };

    // template <typename... T> struct common_type;

    template <typename T>
    struct underlying_type {
        typedef Metrowerks::underlying_type<T>::value type;
    };

    // template <typename Fn, typename... ArgTypes> struct result_of;

#pragma endregion

}
// clang-format on

#endif
