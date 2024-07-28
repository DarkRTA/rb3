#ifndef _METROWERKS_TYPE_TRAITS_INTRINSICS
#define _METROWERKS_TYPE_TRAITS_INTRINSICS

#include <MSL_C++/cstddef>

// Builtins reference: https://decomp.me/scratch/k4ZpJ

namespace Metrowerks {

    namespace detail {

        enum trivial_member {
            trivial_dtor = 0x01,
            trivial_copy_assign = 0x02,
            trivial_copy_ctor = 0x04,
            trivial_default_ctor = 0x08,
        };

        enum ntype {
            ntype_void = 0x00,

            ntype_bool = 0x01,

            ntype_char = 0x02,
            ntype_signed_char = 0x03,
            ntype_unsigned_char = 0x04,

            ntype_wchar_t = 0x05,

            ntype_signed_short = 0x06,
            ntype_unsigned_short = 0x07,

            ntype_signed_int = 0x08,
            ntype_unsigned_int = 0x09,

            ntype_signed_long = 0x0A,
            ntype_unsigned_long = 0x0B, // assumed, the actual result is the same as
                                        // ntype_signed_long for some reason

            ntype_signed_long_long = 0x0C,
            ntype_unsigned_long_long = 0x0D,

            ntype_float = 0x0E,
            ntype_short_double = 0x0F,
            ntype_double = 0x10,
            ntype_long_double = 0x11,

            ntype_vec2x32float = 0x22,

            ntype_type_mask = 0xFF,

            ntype_flag_integral = 0x0100,
            ntype_flag_floating = 0x0200,
            ntype_flag_enum = 0x0400,

            ntype_pointer = 0x0800,
            ntype_array = 0x1000,

            ntype_class = 0x2000,
            ntype_union = 0x2001,
            ntype_pointer_to_member = 0x4000,

            ntype_function = 0x8000,

            ntype_flag_0x10000 = 0x10000,
        };

        // clang-format off: conciseness
        template <ntype N>
        struct ntype_to_integral_helper;

        template <> struct ntype_to_integral_helper<ntype_bool> { typedef bool type; };
        template <> struct ntype_to_integral_helper<ntype_char> { typedef char type; };
        template <> struct ntype_to_integral_helper<ntype_signed_char> { typedef signed char type; };
        template <> struct ntype_to_integral_helper<ntype_unsigned_char> { typedef unsigned char type; };
        template <> struct ntype_to_integral_helper<ntype_wchar_t> { typedef wchar_t type; };
        template <> struct ntype_to_integral_helper<ntype_signed_short> { typedef signed short type; };
        template <> struct ntype_to_integral_helper<ntype_unsigned_short> { typedef unsigned short type; };
        template <> struct ntype_to_integral_helper<ntype_signed_int> { typedef signed int type; };
        template <> struct ntype_to_integral_helper<ntype_unsigned_int> { typedef unsigned int type; };
        template <> struct ntype_to_integral_helper<ntype_signed_long> { typedef signed long type; };
        template <> struct ntype_to_integral_helper<ntype_unsigned_long> { typedef unsigned long type; };
        template <> struct ntype_to_integral_helper<ntype_signed_long_long> { typedef signed long long type; };
        template <> struct ntype_to_integral_helper<ntype_unsigned_long_long> { typedef unsigned long long type; };

        template <ntype N>
        struct ntype_to_integral : public ntype_to_integral_helper<ntype(N & ntype_type_mask)> {};

        template <ntype N>
        struct ntype_to_floating_helper;

        template <> struct ntype_to_floating_helper<ntype_float> { typedef float type; };
        template <> struct ntype_to_floating_helper<ntype_short_double> { typedef short double type; };
        template <> struct ntype_to_floating_helper<ntype_double> { typedef double type; };
        template <> struct ntype_to_floating_helper<ntype_long_double> { typedef long double type; };
        template <> struct ntype_to_floating_helper<ntype_vec2x32float> { typedef __vec2x32float__ type; };

        template <ntype N>
        struct ntype_to_floating : public ntype_to_floating_helper<ntype(N & ntype_type_mask)> {};

        template <ntype N, bool integer, bool floating>
        struct ntype_to_type_helper;

        template <ntype N>
        struct ntype_to_type_helper<N, true, false> : public ntype_to_integral<N> {};

        template <ntype N>
        struct ntype_to_type_helper<N, false, true> : public ntype_to_floating<N> {};

        template <ntype N>
        struct ntype_to_type : public ntype_to_type_helper<
            ntype(N & ntype_type_mask),
            bool(N & ntype_flag_integral),
            bool(N & ntype_flag_floating)
        > {};

        // __builtin_ntype doesn't respect ref types correctly
        template <typename T, ntype NType>
        struct ntype_ref_helper {
            static const bool value = __builtin_ntype(T) == NType;
        };

        template <typename T, ntype NType>
        struct ntype_ref_helper<T&, NType> {
            static const bool value = false;
        };

        template <typename T, ntype Flag>
        struct ntype_ref_helper_flag {
            static const bool value = (__builtin_ntype(T) & Flag) == Flag;
        };

        template <typename T, ntype Flag>
        struct ntype_ref_helper_flag<T&, Flag> {
            static const bool value = false;
        };

        // clang-format on

    }

    template <class T>
    struct alignment_of {
        static const std::size_t value = __builtin_align(T);
    };

    template <typename T>
    struct is_integral {
        static const bool value =
            detail::ntype_ref_helper_flag<T, detail::ntype_flag_integral>::value;
    };

    template <typename T>
    struct is_floating_point {
        static const bool value =
            detail::ntype_ref_helper_flag<T, detail::ntype_flag_floating>::value;
    };

    template <typename T>
    struct is_enum {
        static const bool value =
            detail::ntype_ref_helper_flag<T, detail::ntype_flag_enum>::value;
    };

    template <typename T>
    struct is_class {
        static const bool value = detail::ntype_ref_helper<T, detail::ntype_class>::value;
    };

    // name known; boost
    template <typename T>
    struct is_union {
        static const bool value = detail::ntype_ref_helper<T, detail::ntype_union>::value;
    };

    // name known; boost/STLport
    template <typename T>
    struct is_POD {
        static const bool value = __builtin_is_pod(T);
    };

    template <typename T>
    struct is_polymorphic {
        static const bool value = __builtin_is_polymorphic(T);
    };

    template <typename T>
    struct is_abstract {
        static const bool value = __builtin_is_abstract(T);
    };

    template <typename T>
    struct is_trivial {
        static const bool value = __builtin_trivial_members(T)
            == (detail::trivial_dtor | detail::trivial_copy_assign
                | detail::trivial_copy_ctor | detail::trivial_default_ctor);
    };

    // name known; boost/STLport
    template <typename T>
    struct has_trivial_default_ctor {
        static const bool value =
            __builtin_trivial_members(T) & detail::trivial_default_ctor;
    };

    // name known; boost/STLport
    template <typename T>
    struct has_trivial_copy_ctor {
        static const bool value =
            __builtin_trivial_members(T) & detail::trivial_copy_ctor;
    };

    // name known; boost/STLport
    template <typename T>
    struct has_trivial_assignment {
        static const bool value =
            __builtin_trivial_members(T) & detail::trivial_copy_assign;
    };

    // name known; boost/STLport
    template <typename T>
    struct has_trivial_dtor {
        static const bool value = __builtin_trivial_members(T) & detail::trivial_dtor;
    };

    template <typename T>
    struct has_nothrow_default_ctor {
        static const bool value = __builtin_has_nothrow_default_constructor(T);
    };

    template <typename T>
    struct has_nothrow_copy_ctor {
        static const bool value = __builtin_has_nothrow_copy(T);
    };

    template <typename T>
    struct has_nothrow_assignment {
        static const bool value = __builtin_has_nothrow_assign(T);
    };

    template <typename T>
    struct has_nothrow_dtor {
        static const bool value = __builtin_has_nothrow_destructor(T);
    };

    template <typename T>
    struct has_virtual_dtor {
        static const bool value = __builtin_has_virtual_destructor(T);
    };

    template <typename T, bool IsEnum>
    struct underlying_type_helper {};

    template <typename T>
    struct underlying_type_helper<T, true>
        : public detail::ntype_to_integral<__builtin_ntype(T)> {};

    template <typename T>
    struct underlying_type : public underlying_type_helper<T, is_enum<T>::value> {};

}

#endif
