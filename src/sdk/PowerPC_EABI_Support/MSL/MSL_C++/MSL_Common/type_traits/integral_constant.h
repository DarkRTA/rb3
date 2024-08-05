#ifndef _MSL_TYPE_TRAITS_INTEGRAL_CONSTANT
#define _MSL_TYPE_TRAITS_INTEGRAL_CONSTANT

namespace std {

    template <typename T, T V>
    struct integral_constant {
        static const T value = V;

        typedef T value_type;
        typedef integral_constant type;

        const operator value_type() const throw() { return value; }
        const value_type operator()() const throw() { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <bool B>
    struct bool_constant : public integral_constant<bool, B> {};

}

#endif
