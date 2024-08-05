#ifndef _MSL_TYPE_TRAITS_OPERATION
#define _MSL_TYPE_TRAITS_OPERATION

#include "MSL_C++/MSL_Common/type_traits/integral_constant.h"

// clang-format off: conciseness
namespace std {

#pragma region "enable_if: logical if"
    template <bool B, typename T = void>
    struct enable_if {};
    template <typename T>
    struct enable_if<true, T> { typedef T type; };
#pragma endregion

#pragma region "conditional: logical if/else"
    template <bool B, typename T, typename F> struct conditional;
    template <typename T, typename F> struct conditional<true, T, F> { typedef T type; };
    template <typename T, typename F> struct conditional<false, T, F> { typedef F type; };
#pragma endregion

#pragma region "conjunction: logical AND; all"
    // template <typename... B> struct conjunction;
    struct conjunction : public true_type {};

    template <typename B1, typename B2>
    struct conjunction2 : public conditional< !bool(B1::value), B1, B2 >::type {};

    template <typename B1, typename B2, typename B3>
    struct conjunction3 : public conditional< !bool(B1::value), B1, conjunction2<B2, B3> >::type {};

    template <typename B1, typename B2, typename B3, typename B4>
    struct conjunction4 : public conditional< !bool(B1::value), B1, conjunction3<B2, B3, B4> >::type {};
#pragma endregion

#pragma region "disjunction: logical OR; any"
    // template <typename... B> struct disjunction;
    struct disjunction : public false_type {};

    template <typename B1, typename B2>
    struct disjunction2 : public conditional< bool(B1::value), B1, B2>::type {};

    template <typename B1, typename B2, typename B3>
    struct disjunction3 : public conditional< bool(B1::value), B1, disjunction2<B2, B3> >::type {};

    template <typename B1, typename B2, typename B3, typename B4>
    struct disjunction4 : public conditional< bool(B1::value), B1, disjunction3<B2, B3, B4> >::type {};
#pragma endregion

#pragma region "negation: logical NOT"
    template <typename B>
    struct negation : public integral_constant<bool, !bool(B::value)> {};

    // NAND; not all
    struct negative_conjunction  : public negation<conjunction> {};
    template <typename B1, typename B2>
    struct negative_conjunction2 : public negation<conjunction2<B1, B2> > {};
    template <typename B1, typename B2, typename B3>
    struct negative_conjunction3 : public negation<conjunction3<B1, B2, B3> > {};
    template <typename B1, typename B2, typename B3, typename B4>
    struct negative_conjunction4 : public negation<conjunction4<B1, B2, B3, B4> > {};

    // NOR; not any
    struct negative_disjunction  : public negation<disjunction> {};
    template <typename B1, typename B2>
    struct negative_disjunction2 : public negation<disjunction2<B1, B2> > {};
    template <typename B1, typename B2, typename B3>
    struct negative_disjunction3 : public negation<disjunction3<B1, B2, B3> > {};
    template <typename B1, typename B2, typename B3, typename B4>
    struct negative_disjunction4 : public negation<disjunction4<B1, B2, B3, B4> > {};
#pragma endregion

}
// clang-format on

#endif
