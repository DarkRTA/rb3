#ifndef _MSL_TYPE_TRAITS_MANIP_2
#define _MSL_TYPE_TRAITS_MANIP_2

// Separate for manip traits that aren't free-standing

#include <MSL_C++/cstddef>

#include "MSL_C++/MSL_Common/type_traits/category.h" /* IWYU pragma: keep */
#include "MSL_C++/MSL_Common/type_traits/manip.h" /* IWYU pragma: keep */

// clang-format off: conciseness
namespace std {

#pragma region "sign modifications"
    namespace detail {

        template <typename T> struct make_signed_helper;

        template <> struct make_signed_helper<signed char> { typedef signed char type; };
        template <> struct make_signed_helper<signed short> { typedef signed short type; };
        template <> struct make_signed_helper<signed int> { typedef signed int type; };
        template <> struct make_signed_helper<signed long> { typedef signed long type; };
        template <> struct make_signed_helper<signed long long> { typedef signed long long type; };

        template <> struct make_signed_helper<unsigned char> { typedef signed char type; };
        template <> struct make_signed_helper<unsigned short> { typedef signed short type; };
        template <> struct make_signed_helper<unsigned int> { typedef signed int type; };
        template <> struct make_signed_helper<unsigned long> { typedef signed long type; };
        template <> struct make_signed_helper<unsigned long long> { typedef signed long long type; };

        template <> struct make_signed_helper<char> { typedef signed char type; };
        template <> struct make_signed_helper<wchar_t> { typedef signed short type; };

        template <typename T, bool IsEnum = is_enum<T>::value>
        struct make_signed : public make_signed_helper<T> {};

        template <typename T>
        struct make_signed<T, true> : public make_signed_helper<typename underlying_type<T>::type> {};

    }

    template <typename T>
    struct make_signed : public detail::copy_cv<T, detail::make_signed<typename remove_cv<T>::type> > {};

    namespace detail {

        template <typename T> struct make_unsigned_helper;

        template <> struct make_unsigned_helper<signed char> { typedef unsigned char type; };
        template <> struct make_unsigned_helper<signed short> { typedef unsigned short type; };
        template <> struct make_unsigned_helper<signed int> { typedef unsigned int type; };
        template <> struct make_unsigned_helper<signed long> { typedef unsigned long type; };
        template <> struct make_unsigned_helper<signed long long> { typedef unsigned long long type; };

        template <> struct make_unsigned_helper<unsigned char> { typedef unsigned char type; };
        template <> struct make_unsigned_helper<unsigned short> { typedef unsigned short type; };
        template <> struct make_unsigned_helper<unsigned int> { typedef unsigned int type; };
        template <> struct make_unsigned_helper<unsigned long> { typedef unsigned long type; };
        template <> struct make_unsigned_helper<unsigned long long> { typedef unsigned long long type; };

        template <> struct make_unsigned_helper<char> { typedef unsigned char type; };
        template <> struct make_unsigned_helper<wchar_t> { typedef unsigned short type; };

        template <typename T, bool IsEnum = is_enum<T>::value>
        struct make_unsigned : public make_unsigned_helper<T> {};

        template <typename T>
        struct make_unsigned<T, true> : public make_unsigned_helper<typename underlying_type<T>::type> {};

    }

    template <typename T>
    struct make_unsigned : public detail::copy_cv<T, detail::make_unsigned<typename remove_cv<T>::type> > {};
#pragma endregion

    template<class T>
    struct decay
    {
    private:
        typedef typename remove_reference<T>::type U;

    public:
        typedef typename conditional<
            is_array<U>::value,
            typename add_pointer<typename remove_extent<U>::type>::type,
            typename conditional<
                is_function<U>::value,
                typename add_pointer<U>::type,
                typename remove_cv<U>::type
            >::type
        >::type type;
    };

}
// clang-format on

#endif
