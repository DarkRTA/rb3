#ifndef _MSL_TYPE_TRAITS
#define _MSL_TYPE_TRAITS

#include <MSL_C++/cstddef>
#include <MSL_C++/cwchar>

namespace std {

    template <class State>
    class fpos;

    typedef mbstate_t __char_state_type;
    typedef mbstate_t __wchar_state_type;

    typedef long __streamoff;

    template <class CharT>
    struct char_traits {};

    template <>
    struct char_traits<char> {
        typedef char char_type;
        typedef int int_type;
        typedef __streamoff off_type;
        typedef fpos<__char_state_type> pos_type;
        typedef __char_state_type state_type;
    };

    template <>
    struct char_traits<wchar_t> {
        typedef wchar_t char_type;
        typedef wint_t int_type;
        typedef __streamoff off_type;
        typedef fpos<__wchar_state_type> pos_type;
        typedef __wchar_state_type state_type;
    };

}

#endif
