#ifndef _MSL_DETAILS_TYPE_MANIPS
#define _MSL_DETAILS_TYPE_MANIPS

// clang-format off
namespace Metrowerks {

    template <typename T> struct remove_cv { typedef T type; };

    template <typename T> struct remove_cv<const T> { typedef T type; };
    template <typename T> struct remove_cv<volatile T> { typedef T type; };
    template <typename T> struct remove_cv<const volatile T> { typedef T type; };

    template <typename T> struct remove_cv<const T*> { typedef T *type; };
    template <typename T> struct remove_cv<volatile T*> { typedef T *type; };
    template <typename T> struct remove_cv<const volatile T*> { typedef T *type; };

    template <typename T> struct remove_cv<const T&> { typedef T &type; };
    template <typename T> struct remove_cv<volatile T&> { typedef T &type; };
    template <typename T> struct remove_cv<const volatile T&> { typedef T &type; };

    template <typename T> struct remove_cv<const T[]> { typedef T type[]; };
    template <typename T> struct remove_cv<volatile T[]> { typedef T type[]; };
    template <typename T> struct remove_cv<const volatile T[]> { typedef T type[]; };

}
// clang-format on

#endif
