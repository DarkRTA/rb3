#ifndef _MSL_DETAILS_TYPE_TRAITS
#define _MSL_DETAILS_TYPE_TRAITS

namespace Metrowerks {

    template <typename T>
    struct is_final {
        static const bool result = false;
    };

    // clang-format off: conciseness
    template <typename T> struct is_final<T *> { static const bool result = true; };
    template <typename T> struct is_final<T &> { static const bool result = true; };
    template <typename T> struct is_final<T[]> { static const bool result = true; };

    template <> struct is_final<bool> { static const bool result = true; };
    template <> struct is_final<char> { static const bool result = true; };
    template <> struct is_final<wchar_t> { static const bool result = true; };
    template <> struct is_final<short> { static const bool result = true; };
    template <> struct is_final<int> { static const bool result = true; };
    template <> struct is_final<long> { static const bool result = true; };
    template <> struct is_final<long long> { static const bool result = true; };
    template <> struct is_final<unsigned char> { static const bool result = true; };
    template <> struct is_final<unsigned short> { static const bool result = true; };
    template <> struct is_final<unsigned int> { static const bool result = true; };
    template <> struct is_final<unsigned long> { static const bool result = true; };
    template <> struct is_final<unsigned long long> { static const bool result = true; };
    // clang-format on

    // Integral types can't be inherited
    template <typename T, bool IsIntegral>
    struct __is_empty {
        static const bool result = false;
    };

    template <typename T>
    struct __is_empty<T, false> {
        struct helper1 : public T {
            int i;
        };

        struct helper2 {
            int i;
        };

        static const bool result = sizeof(helper1) == sizeof(helper2);
    };

    template <typename T>
    struct is_empty {
        static const int result = __is_empty<T, is_final<T>::result>::result;
    };

    template <typename T>
    struct is_value_type {
        static const bool result = true;
    };

    template <typename T>
    struct is_value_type<T *> {
        static const bool result = false;
    };

    template <typename T>
    struct is_value_type<T &> {
        static const bool result = false;
    };

    template <typename T>
    struct is_value_type<T[]> {
        static const bool result = false;
    };

}

#endif
